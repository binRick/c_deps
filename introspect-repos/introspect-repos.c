#include <stdbool.h>
#define DEBUG_STDOUT                   false
#define DEBUG_RECEIVE_MESON_RESULTS    false
#define DEBUG_EXECUTE_MESON_JOB        false
#define DEBUG_PATHS                    false
#define STDOUT_READ_BUFFER_SIZE        1024 * 16
#define PREVIEW_LIMIT                  25
#define WORKERS_QTY                    20
#define DEBUG_MEMORY_ENABLED           false
#define NUM_CHILDREN                   1
#define MAX_OUTPUT_BYTES               1024 * 1024
#define CACHE_DIRECTORY                "./.cache"
//////////////////////////////////////////////
#include "introspect-repos.h"
#include "submodules/log.h/log.h"
#define D    log_debug
#define E    log_error
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY_ENABLED
#include "submodules/debug-memory/debug_memory.h"
#endif

char * get_cached_key_file_name(const char *KEY);
char * get_cached_key_file(const char *KEY);
bool cached_key_file_exists(const char *KEY);

////////////////////////////////////////////////
typedef struct WORKER_T {
  int delay_ms;
  int thread_index;
} worker_t;
////////////////////////////////////////////////
chan_t        *JOBS_CHANNEL, *RESULTS_CHANNEL, *DONE_CHANNEL;
struct Vector *meson_results;


////////////////////////////////////////////////


void write_cached_key_file_content(const char *KEY, const char *KEY_CONTENT){
  if (KEY_CONTENT == NULL) {
    return;
  }
  return(fsio_write_text_file(get_cached_key_file(KEY), KEY_CONTENT));
}


char * cached_key_file_content(const char *KEY){
  return(fsio_read_text_file(get_cached_key_file(KEY)));
}


bool cached_key_file_exists(const char *KEY){
  return(fsio_file_exists(get_cached_key_file(KEY)));
}


char * get_cached_key_file(const char *KEY){
  char *FN = get_cached_key_file_name(KEY);
  char *p  = malloc(strlen(FN) + strlen(CACHE_DIRECTORY) + 32);

  sprintf(p, "%s/%s", CACHE_DIRECTORY, FN);
  free(FN);
  if (!fsio_dir_exists(CACHE_DIRECTORY)) {
    fsio_mkdirs(CACHE_DIRECTORY, 0700);
  }
  return(strdup(p));
}


char * get_cached_key_file_name(const char *KEY){
  char          *p         = malloc(1024);
  time_t        now        = time(NULL);
  struct tm     *tm_struct = localtime(&now);
  unsigned char hash[16];
  md5_ctx       ctx;

  rhash_md5_init(&ctx);
  rhash_md5_update(&ctx, (const unsigned char *)KEY, strlen(KEY));
  rhash_md5_final(&ctx, hash);
  char *K = stringfn_replace(stringfn_trim(stringfn_replace(stringfn_replace(b64_encode(hash, 16), '/', '_'), '=', ' ')), ' ', '_');

  sprintf(p, "%s_%d-%d.txt",
          K,
          tm_struct->tm_yday,
          tm_struct->tm_hour
          );
  return(p);
}

struct Vector *get_meson_paths(char *BASE_PATH, char *PATH_FILTER, size_t PATH_LIMIT){
  list_t        *meson_paths = list_new();
  tinydir_dir   dir;
  struct Vector *vector = vector_new();
  char          cwd[1024];

  getcwd(cwd, sizeof(cwd));

  if (tinydir_open(&dir, BASE_PATH) == -1) {
    perror("Error opening base path");
    goto bail;
  }

  while (dir.has_next) {
    tinydir_file file;
    if (tinydir_readfile(&dir, &file) == -1) {
      perror("Error getting file");
      goto bail;
    }
    if ((file.is_dir) && (wildcardcmp(PATH_FILTER, file.name) == 1) && strlen(file.name) > 1 && (list_find(meson_paths, file.name) == NULL)) {
      char mbp[128];
      sprintf(mbp, "%s/%s/%s/meson.build", cwd, BASE_PATH, file.name);
      bool meson_build_exists = fsio_file_exists(mbp);
      if (meson_build_exists) {
        if (DEBUG_PATHS) {
          fprintf(stdout,
                  AC_YELLOW AC_ITALIC "\t(%s)\t\t(meson.build [%s] exists:%d)\n" AC_RESETALL,
                  file.name,
                  mbp,
                  meson_build_exists
                  );
        }
        if (vector_size(vector) < PATH_LIMIT) {
          vector_push(vector, path_normalize(mbp));
        }
      }
    }
    if (tinydir_next(&dir) == -1) {
      perror("Error getting next file");
      goto bail;
    }
  }
  tinydir_close(&dir);
bail:
  tinydir_close(&dir);
  return(vector);
} /* get_meson_paths */


void iterate_free(struct Vector *VECTOR){
  for (size_t i = 0; i < vector_size(VECTOR); i++) {
    free(vector_get(VECTOR, i));
  }
}


size_t iterate_get_total_size(struct Vector *VECTOR){
  size_t total_size = 0;

  for (size_t i = 0; i < vector_size(VECTOR); i++) {
    total_size += strlen((char *)vector_get(VECTOR, i));
  }
  return(total_size);
}


void iterate_parse_results(struct Vector *MESON_RESULTS){
  for (size_t i = 0; i < vector_size(MESON_RESULTS); i++) {
    JSON_Array *A      = NULL;
    char       *OUTPUT = (char *)vector_get(MESON_RESULTS, i);
    assert(strlen(OUTPUT) > 0);
    JSON_Value *V = json_parse_string(OUTPUT);

    assert(V != NULL);
    assert(json_value_get_type(V) == JSONArray);

    A = json_value_get_array(V);
    assert(A != NULL);
    size_t qty = json_array_get_count(A);
    log_debug("qty:%lu", qty);
    log_debug("output:%s\n%lub output\n\n", OUTPUT, strlen(OUTPUT));
  }
}


void iterate_print(struct Vector *MESON_PATHS){
  printf(">Current size: %zu capacity: %zu\n", vector_size(MESON_PATHS), vector_capacity(MESON_PATHS));
  for (size_t i = 0; i < vector_size(MESON_PATHS); i++) {
    printf("Value at index #%lu: %s\n",
           i,
           (char *)vector_get(MESON_PATHS, i)
           );
  }
}


void iterate_targets(ee_t *ee, JSON_Array *A){
  JSON_Value  *V = json_value_init_object();
  JSON_Object *O = json_value_init_object();
  char        *type;

  for (size_t i = 0; i < json_array_get_count(A); i++) {
    V = json_array_get_value(A, i);
    O = json_array_get_object(A, i);
    size_t props_qty = json_object_get_count(O);
    assert(json_value_get_type(V) == JSONObject);
    assert(props_qty > 0);
    type = json_object_get_string(O, "type");
    if (ee_listener_count(ee, type) > 0) {
      ee_emit(ee, type, V);
    }else{
      E("NOT HANDLED> type: '%s' qty:%d", type, ee_listener_count(ee, type));
    }
  }
  json_value_free(V);
}


JSON_Array *parse_execution_result(char *OUTPUT){
  JSON_Array *A = NULL;

  assert(strlen(OUTPUT) > 0);
  JSON_Value *V = json_parse_string(OUTPUT);

  assert(V != NULL);
  assert(json_value_get_type(V) == JSONArray);

  A = json_value_get_array(V);
  assert(A != NULL);
  size_t qty = json_array_get_count(A);

  assert(qty > 0);
  //log_debug("output is %lub and %lu properties", strlen(OUTPUT), json_array_get_count(A));
  //D("parse........%lu", json_array_get_count(A));
  return(A);
}


repos_t init_repos(){
  repos_t REPOS = {
  };

  return(REPOS);
}


repo_t init_repo(){
  repo_t REPO = {
  };

  return(REPO);
}


repo_t parse_repo_type(JSON_Object *O){
  repo_t REPO = {
  };

  return(REPO);
}


void *receive_meson_results(void *_RESULTS_QTY){
  void   *_result;
  size_t qty = 0, RESULTS_QTY = (size_t)_RESULTS_QTY;

  if (DEBUG_RECEIVE_MESON_RESULTS) {
    fprintf(stderr, ">Waiting for %lu results\n", RESULTS_QTY);
  }
  while ((qty < RESULTS_QTY) && chan_recv(RESULTS_CHANNEL, &_result) == 0) {
    char *result = (char *)_result;
    if (DEBUG_RECEIVE_MESON_RESULTS) {
      fprintf(stderr, AC_RESETALL AC_GREEN_BLACK AC_REVERSED "> received result of %lu bytes\n" AC_REVERSED,
              strlen(result));
    }
    vector_push(meson_results, (void *)result);
    qty++;
  }
  if (DEBUG_RECEIVE_MESON_RESULTS) {
    fprintf(stderr,
            "\n"
            AC_GREEN AC_REVERSED "Waiter finished %lu jobs" AC_RESETALL
            "\n",
            RESULTS_QTY);
  }
  chan_send(DONE_CHANNEL, NULL);
}


char *execute_meson_introspect(void *_MESON_PATH){
  char *MESON_PATH = (char *)_MESON_PATH;

  if (cached_key_file_exists(MESON_PATH)) {
    return(cached_key_file_content(MESON_PATH));
  }
  const char           *command_line[] = {
    "/usr/local/bin/meson",
    "introspect",
    "--targets",
    MESON_PATH,
    NULL,
  };
  char                 *READ_STDOUT;
  int                  exited, result;
  struct subprocess_s  subprocess;
  char                 stdout_buffer[STDOUT_READ_BUFFER_SIZE] = { 0 };
  struct  StringBuffer *SB                                    = stringbuffer_new_with_options(STDOUT_READ_BUFFER_SIZE, true);
  size_t               bytes_read                             = 0,
                       index                                  = 0;

  result = subprocess_create(command_line, 0, &subprocess);
  assert_eq(result, 0, %d);
  do {
    bytes_read = subprocess_read_stdout(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
    index += bytes_read;
  } while (bytes_read != 0);

  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  assert_eq(exited, 0, %d);

  READ_STDOUT = stringbuffer_to_string(SB);
  stringbuffer_release(SB);

  if (DEBUG_STDOUT) {
    dbg(exited, %d);
    dbg(command_line[2], %s);
    dbg(strlen(READ_STDOUT), %lu);
    fprintf(stderr, "%s", READ_STDOUT);
  }
  write_cached_key_file_content(MESON_PATH, READ_STDOUT);
  return(READ_STDOUT);
} /* execute_meson_introspect */


void *execute_meson_job(void *_WORKER_ID){
  size_t WORKER_ID = (size_t)_WORKER_ID;
  void   *_job;
  size_t qty = 0;

  while (chan_recv(JOBS_CHANNEL, &_job) == 0) {
    char *job = (char *)_job;
    if (DEBUG_EXECUTE_MESON_JOB) {
      fprintf(stderr,
              AC_RESETALL AC_REVERSED AC_YELLOW "%lu> Worker processing job #%lu of %lu bytes:     '%s'\n" AC_RESETALL,
              WORKER_ID, qty, strlen(job), job);
    }
    char *JSON_OUTPUT = execute_meson_introspect(job);
    chan_send(RESULTS_CHANNEL, (void *)JSON_OUTPUT);
    qty++;
  }
  if (DEBUG_EXECUTE_MESON_JOB) {
    fprintf(stderr, "Worker #%lu finished\n", WORKER_ID);
  }
}


struct Vector * execute_meson_introspects(struct Vector *MESON_PATHS){
  pthread_t worker_threads[WORKERS_QTY];
  pthread_t waiter_thread;
  size_t    workers_qty = 0;

  meson_results   = vector_new();
  DONE_CHANNEL    = chan_init(0);
  JOBS_CHANNEL    = chan_init(WORKERS_QTY);
  RESULTS_CHANNEL = chan_init(WORKERS_QTY);
  ct_start(NULL);

  int res = pthread_create(&waiter_thread, NULL, receive_meson_results, (void *)vector_size(MESON_PATHS));

  assert_eq(0, res, %d);

  for (size_t i = 0; (i < WORKERS_QTY) && (i < vector_size(MESON_PATHS)); i++) {
    int res = pthread_create(&worker_threads[i], NULL, execute_meson_job, (void *)i);
    assert_eq(0, res, %d);
    workers_qty++;
  }
  for (size_t i = 0; i < vector_size(MESON_PATHS); i++) {
    chan_send(JOBS_CHANNEL, (void *)((char *)vector_get(MESON_PATHS, i)));
  }
  chan_close(JOBS_CHANNEL);
  chan_recv(DONE_CHANNEL, NULL);

  chan_close(RESULTS_CHANNEL);
  chan_close(RESULTS_CHANNEL);
  chan_close(DONE_CHANNEL);

  chan_dispose(JOBS_CHANNEL);
  chan_dispose(RESULTS_CHANNEL);
  chan_dispose(DONE_CHANNEL);
  for (size_t i = 0; i < workers_qty; i++) {
    pthread_join(&worker_threads[i], NULL);
  }
  pthread_join(&waiter_thread, NULL);
  char *dur = ct_stop("");

  fprintf(stdout,
          AC_RESETALL AC_GREEN AC_REVERSED "done channel recvd %lu results of %lub using %lu workers in %s\n" AC_RESETALL,
          (size_t)vector_size(meson_results),
          iterate_get_total_size(meson_results),
          workers_qty,
          dur
          );

  return(meson_results);
} /* execute_meson_introspects */


char *execute_processes(char *MESON_BUILD_FILE){
  uint8_t             output[MAX_OUTPUT_BYTES];
  reproc_event_source children[NUM_CHILDREN] = { { 0 } };
  int                 r                      = -1;

  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[] = {
      "meson", "introspect", "--targets", MESON_BUILD_FILE,
      NULL
    };

    r = reproc_start(process, date_args, (reproc_options){ .nonblocking = true });
    if (r < 0) {
      goto finish;
    }

    children[i].process   = process;
    children[i].interests = REPROC_EVENT_OUT;
  }

  for ( ;;) {
    r = reproc_poll(children, NUM_CHILDREN, REPROC_INFINITE);
    if (r < 0) {
      r = r == REPROC_EPIPE ? 0 : r;
      goto finish;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
      if (children[i].process == NULL || !children[i].events) {
        continue;
      }
      r = reproc_read(children[i].process, REPROC_STREAM_OUT, output, sizeof(output));
      if (r == REPROC_EPIPE) {
        children[i].process = reproc_destroy(children[i].process);
        continue;
      }

      if (r < 0) {
        goto finish;
      }
      output[r] = '\0';

      if (false) {
        char msg[strlen(output) + 1024];
        sprintf(&msg, "<%d> " AC_RESETALL AC_YELLOW_BLACK AC_REVERSED AC_ITALIC "%s" AC_RESETALL, getpid(), stringfn_trim(output));
        log_debug("%s", msg);
      }
    }
  }

finish:
  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_destroy(children[i].process);
  }

  if (r < 0) {
    log_error("%s", reproc_strerror(r));
  }

  char *o = malloc(strlen(output));

  sprintf(o, "%s", stringfn_trim(output));
  //free(o);
  return(o);
} /* execute_processes */
