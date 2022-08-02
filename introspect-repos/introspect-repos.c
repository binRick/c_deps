//#define DEBUG_MEMORY_ENABLED
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#include "generic-print/print.h"
#include "introspect-repos.h"
#include "log.h/log.h"
#include "submodules/occurences.c/occurrences.h"
//////////////////////////////////////////////
#define PROGRESS_BAR_WIDTH             60
#define BG_PROGRESS_BAR_CHAR           "."
#define PROGRESS_BAR_CHAR              "="
#define CACHE_ENABLED                  true
#define DEBUG_CHANNELS                 false
#define DEBUG_STDOUT                   false
#define DEBUG_REGEX                    false
#define DEBUG_RECEIVE_MESON_RESULTS    false
#define DEBUG_EXECUTE_MESON_JOB        false
#define DEBUG_PATHS                    false
#define STDOUT_READ_BUFFER_SIZE        1024 * 2
#define PREVIEW_LIMIT                  25
#define WORKERS_QTY                    3
#define MAX_OUTPUT_BYTES               1024 * 150
#define CACHE_DIRECTORY                "./.cache"
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY_ENABLED
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////////
Table table = { 0 };
chan_t        *JOBS_CHANNEL, *RESULTS_CHANNEL, *DONE_CHANNEL;
struct Vector *meson_results;
char * get_cached_key_file_name(const char *KEY);
char * get_cached_key_file(const char *KEY);
bool cached_key_file_exists(const char *KEY);

struct Vector     *TEST_EXECUTABLES_v;

static progress_t *progress;

typedef struct TEST_EXECUTABLE_LIST_RESULT {
  char *executable;
  char *list_output;
} test_executable_list_result;

typedef struct  MESON_JOB_RESULT_T {
  char
  *name, *version, *dir, *subprojects_dir, *styled_name,
  *json, *git_config, *dur_s, *json_bytes_s
  ;
  unsigned long
    dur
  ;
  size_t
    json_bytes
  ;
  JSON_Value
    *Root_v,
  *ProjectInfo_v,
  *Ast_v
  ;
  JSON_Value
  *Targets_v,
  *BuildOptions_v,
  *Dependencies_v,
  *ScanDependencies_v,
  *ProjectDependences_v
  ;
  JSON_Value
  *AstLines_v,
  *TargetExecutables_v,
  *TargetExecutableFiles_v,
  *TargetSharedLibraries_v,
  *TargetStaticLibraries_v,
  *TargetSources_v,
  *TargetSourceFilenames_v,
  *TargetFilenames_v,
  *SubprojectBuildSystemFiles_v,
  *BuildSystemFiles_v,
  *Subprojects_v,
  *SubprojectNames_v
  ;
  JSON_Object
  *Root_o,
  *ProjectInfo_o,
  *Ast_o
  ;
  JSON_Array
  *Targets_a,
  *BuildOptions_a,
  *Dependencies_a,
  *ScanDependencies_a,
  *ProjectDependences_a,
  *AstLines_a
  ;
} meson_job_result_t;
////////////////////////////////////////////////////////////////////////////////////////////////////
////             HANDLE REPOSITORY EXECUTABLES                                                  ////
////////////////////////////////////////////////////////////////////////////////////////////////////
#define HANDLE_TEST_EXECUTABLES(TEST_EXECUTABLES_v) \
  { do{                                             \
      char *TEST_EXECUTABLE;                        \
      //dbg(vector_size(TEST_EXECUTABLES_v), %lu);                    \
      //       for (size_t i = 0; i < vector_size(TEST_EXECUTABLES_v); i++) { \
      //         TEST_EXECUTABLE = (char *)vector_get(TEST_EXECUTABLES_v, i); \
      //dbg(TEST_EXECUTABLE, %s);                                   \
      //       }                                                              \
      //       free(TEST_EXECUTABLE);                                         \
      //     }while (0); }

////////////////////////////////////////////////////////////////////////////////////////////////////
////             PARSE MESON JOB RESULT                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////
#define PARSE_MESON_JOB_RESULT(JR)                                                        \
  { do{                                                                                   \
/*         Basic Properties */                                                            \
      r->json_bytes   = strlen(r->json);                                                  \
      r->styled_name  = style_name(r->name);                                              \
      r->dur_s        = milliseconds_to_string(r->dur);                                   \
      r->json_bytes_s = bytes_to_string(r->json_bytes);                                   \
                                                                                          \
/*         Parse JSON */                                                                  \
      JR->Root_v = json_parse_string(JR->json);                                           \
      JR->Root_o = json_value_get_object(JR->Root_v);                                     \
                                                                                          \
/*         JSON Values           */                                                       \
      JR->ProjectInfo_v      = json_object_dotget_value(JR->Root_o, "projectinfo");       \
      JR->Targets_v          = json_object_dotget_value(JR->Root_o, "targets");           \
      JR->Dependencies_v     = json_object_dotget_value(JR->Root_o, "dependencies");      \
      JR->BuildOptions_v     = json_object_dotget_value(JR->Root_o, "buildoptions");      \
      JR->ScanDependencies_v = json_object_dotget_value(JR->Root_o, "scan_dependencies"); \
      JR->Ast_v              = json_object_dotget_value(JR->Root_o, "ast");               \
                                                                                          \
/*         JSON Value -> Object           */                                              \
      JR->ProjectInfo_o = json_value_get_object(JR->ProjectInfo_v);                       \
      JR->Ast_o         = json_value_get_object(JR->Ast_v);                               \
                                                                                          \
/*         JSON Value -> Array           */                                               \
      JR->ScanDependencies_a = json_value_get_array(JR->ScanDependencies_v);              \
      JR->Dependencies_a     = json_value_get_array(JR->Dependencies_v);                  \
      JR->BuildOptions_a     = json_value_get_array(JR->BuildOptions_v);                  \
      JR->Targets_a          = json_value_get_array(JR->Targets_v);                       \
                                                                                          \
    }while (0); }
////////////////////////////////////////////////////////////////////////////////////////////////////
////             VALIDATE MESON JOB RESULT                                                      ////
////////////////////////////////////////////////////////////////////////////////////////////////////
#define VALIDATE_MESON_JOB_RESULT(JR)                                   \
  { do{                                                                 \
/*         JSON Values           */                                     \
      assert(JR->Root_v != NULL);                                       \
      assert(JR->ProjectInfo_v != NULL);                                \
      assert(JR->Ast_v != NULL);                                        \
      assert(JR->BuildOptions_v != NULL);                               \
      assert(JR->ScanDependencies_v != NULL);                           \
      assert(JR->Targets_v != NULL);                                    \
                                                                        \
/*         JSON Value -> Object           */                            \
      assert(json_value_get_type(JR->Root_v) == JSONObject);            \
      assert(json_value_get_type(JR->ProjectInfo_v) == JSONObject);     \
      assert(json_value_get_type(JR->Ast_v) == JSONObject);             \
                                                                        \
/*         JSON Value -> Array           */                             \
      assert(json_value_get_type(JR->ScanDependencies_v) == JSONArray); \
      assert(json_value_get_type(JR->Dependencies_v) == JSONArray);     \
      assert(json_value_get_type(JR->BuildOptions_v) == JSONArray);     \
      assert(json_value_get_type(JR->Targets_v) == JSONArray);          \
/*         JSON Objects           */                                    \
      assert(JR->Root_o != NULL);                                       \
      assert(JR->ProjectInfo_o != NULL);                                \
      assert(JR->Ast_o != NULL);                                        \
                                                                        \
/*         JSON Arrays           */                                     \
      assert(JR->Targets_a != NULL);                                    \
      assert(JR->BuildOptions_a != NULL);                               \
      assert(JR->Dependencies_a != NULL);                               \
      assert(JR->ScanDependencies_a != NULL);                           \
                                                                        \
    }while (0); }
////////////////////////////////////////////////////////////////////////////////////////////////////


static char *style_name(const char *name){
  char *s = calloc(1, strlen(name) + 128);

  sprintf(s, " %s%s%s ", F_GREEN, name, COL_RESET);
  return(s);
}


static char *number_to_string(size_t number){
  char *s = calloc(1, number / 10 + 1);

  sprintf(s, "%lu", number);
  return(s);
}


static void introspection_progress_start(progress_data_t *data) {
  assert(data);
  fprintf(stdout,
          AC_HIDE_CURSOR
          AC_RESETALL AC_GREEN AC_ITALIC "Introspecting" AC_RESETALL
          AC_RESETALL " "
          AC_RESETALL AC_BLUE AC_REVERSED AC_BOLD "%d"
          AC_RESETALL " "
          AC_RESETALL AC_GREEN AC_ITALIC "Meson Repositories" AC_RESETALL
          "\n",
          data->holder->total
          );
  progress_write(data->holder);
}


static void introspection_progress(progress_data_t *data) {
  progress_write(data->holder);
}


static void introspection_progress_end(progress_data_t *data) {
  fprintf(stdout,
          AC_SHOW_CURSOR
          AC_RESETALL "\n"
          AC_GREEN AC_REVERSED AC_BOLD "Complete" AC_RESETALL
          "\n"
          );
}


////////////////////////////////////////////////
struct Vector *extract_repository_executables(char *REPOSITORY_NAME, struct Vector *MESON_RESULTS){
  struct Vector *REPOSITORY_EXECUTABLES_v = vector_new();

  for (size_t i = 0; i < vector_size(MESON_RESULTS); i++) {
    meson_job_result_t *r = (meson_job_result_t *)vector_get(MESON_RESULTS, i);
    if (strcmp(REPOSITORY_NAME, r->name) != 0) {
      continue;
    }
    for (size_t ii = 0; ii < json_array_get_count(r->Targets_a); ii++) {
      if (strcmp(json_object_dotget_string(json_array_get_object(r->Targets_a, ii), "type"), "executable") == 0) {
        char *target_name = json_object_dotget_string(json_array_get_object(r->Targets_a, ii), "name");
        char *defined_id  = json_object_dotget_string(json_array_get_object(r->Targets_a, ii), "defined_in");
        for (size_t iii = 0; iii < json_array_get_count(json_object_dotget_array(json_array_get_object(r->Targets_a, ii), "filename")); iii++) {
          char *fn = json_array_get_string(json_object_dotget_array(json_array_get_object(r->Targets_a, ii), "filename"), iii);
          if ((fn != NULL) && (strlen(fn) > 0)) {
            vector_push(REPOSITORY_EXECUTABLES_v, fn);
          }
        }
      }
    }
  }
  return(REPOSITORY_EXECUTABLES_v);
}


static void generate_results_table(struct Vector *MESON_RESULTS){
  table = get_empty_table();

  override_alignment_of_row(&table, ALIGN_CENTER);
  override_alignment(&table, ALIGN_LEFT);
  add_cell(&table, " " F_YELLOW "Project" COL_RESET " ");
  add_cell(&table, " Size ");
  add_cell(&table, " Dur ");
  add_cell(&table, " Targets ");
  add_cell(&table, " Deps ");
  add_cell(&table, " Scan Deps ");
  add_cell(&table, " Build Opts ");
  set_hline(&table, BORDER_DOUBLE);
  next_row(&table);

  for (size_t i = 0; i < vector_size(MESON_RESULTS); i++) {
    meson_job_result_t *r = (meson_job_result_t *)vector_get(MESON_RESULTS, i);
    if (i == 0) {
      set_hline(&table, BORDER_DOUBLE);
    }else{
      set_hline(&table, BORDER_SINGLE);
    }
    override_alignment_of_row(&table, ALIGN_CENTER);
    override_alignment(&table, ALIGN_LEFT);
    add_cell(&table, r->styled_name);
    add_cell(&table, r->json_bytes_s);
    add_cell(&table, r->dur_s);
    add_cell(&table, number_to_string(json_array_get_count(r->Targets_a)));
    add_cell(&table, number_to_string(json_array_get_count(r->Dependencies_a)));
    add_cell(&table, number_to_string(json_array_get_count(r->ScanDependencies_a)));
    add_cell(&table, number_to_string(json_array_get_count(r->BuildOptions_a)));
    next_row(&table);
  }

  set_all_vlines(&table, BORDER_SINGLE);
  make_boxed(&table, BORDER_DOUBLE);
  print_table(&table);
  free_table(&table);
} /* gen_table */


static void write_cached_key_file_content(const char *KEY, const char *KEY_CONTENT){
  if (KEY_CONTENT == NULL) {
    return;
  }
  char *K  = get_cached_key_file(KEY);
  int  res = fsio_write_text_file(K, KEY_CONTENT);
  if (K) {
    free(K);
  }
  return(res);
}


static char * cached_key_file_content(const char *KEY){
  char *K   = get_cached_key_file(KEY);
  char *res = fsio_read_text_file(K);

  if (K) {
    free(K);
  }
  return(res);
}


bool cached_key_file_exists(const char *KEY){
  char *K  = get_cached_key_file(KEY);
  bool res = fsio_file_exists(K);

  if (K) {
    free(K);
  }
  return((res) && (fsio_file_size(K) > 1024));
}


char * get_cached_key_file(const char *KEY){
  char *FN = get_cached_key_file_name(KEY);
  char *p  = calloc(1, strlen(FN) + strlen(CACHE_DIRECTORY) + 32);

  sprintf(p, "%s/%s", CACHE_DIRECTORY, FN);
  if (FN) {
    free(FN);
  }
  if (!fsio_dir_exists(CACHE_DIRECTORY)) {
    fsio_mkdirs(CACHE_DIRECTORY, 0700);
  }
  return(p);
}


char * get_cached_key_file_name(const char *KEY){
  char          *p         = calloc(1, 1024);
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

    int  match_length = 0, match_idx = -1;
    bool IS_MATCH = false;
    re_t pattern;


    struct StringFNStrings regexes     = stringfn_split(PATH_FILTER, '|');
    bool                   found_match = false;
    for (int i = 0; (i < regexes.count) && (found_match == false); i++) {
      pattern   = re_compile(regexes.strings[i]);
      match_idx = re_matchp(pattern, file.name, &match_length);
      IS_MATCH  = (match_length > 0);
      if (IS_MATCH) {
        found_match = true;
      }
      if (DEBUG_REGEX) {
        /*
         * dbg(regexes.strings[i], %s);
         * dbg((char *)file.name, %s);
         * dbg(match_length, %d);
         * dbg(IS_MATCH ? "Yes" : "No", %s);
         * dbg(match_idx, %d);
         */
      }
    }

    if ((file.is_dir) && (found_match) && strlen(file.name) > 1 && (list_find(meson_paths, file.name) == NULL)) {
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
    meson_job_result_t *j = (meson_job_result_t *)vector_get(VECTOR, i);
    if (j != NULL) {
      if (j->name != NULL) {
        free(j->name);
      }
      free(j);
    }
  }
  vector_release(VECTOR);
}


size_t iterate_get_total_size(struct Vector *VECTOR){
  size_t total_size = 0;

  for (size_t i = 0; i < vector_size(VECTOR); i++) {
    total_size += strlen((char *)vector_get(VECTOR, i));
  }
  return(total_size);
}


void iterate_parse_results(struct Vector *MESON_RESULTS){
  char   REPOSITORY_NAME[]         = "c_deps";
  Vector *REPOSITORY_EXECUTABLES_v = vector_new();

  for (int i = 0; i < vector_size(MESON_RESULTS); i++) {
    meson_job_result_t *r = (meson_job_result_t *)vector_get(MESON_RESULTS, i);
    if (r == NULL) {
      continue;
    }
    if (r->json == NULL) {
      continue;
    }
    if (strlen(r->json) < 2) {
      continue;
    }
    PARSE_MESON_JOB_RESULT(r);
    VALIDATE_MESON_JOB_RESULT(r);
  }
  REPOSITORY_EXECUTABLES_v = extract_repository_executables(REPOSITORY_NAME, MESON_RESULTS);
  re_t TEST_EXECUTABLE_REGEX = re_compile("-test$");

  TEST_EXECUTABLES_v = vector_new();
  char *TEST_EXECUTABLE;

  for (int i = 0; i < vector_size(REPOSITORY_EXECUTABLES_v); i++) {
    TEST_EXECUTABLE = (char *)vector_get(REPOSITORY_EXECUTABLES_v, i);
    //dbg(i, %d);
    //dbg(TEST_EXECUTABLE, %s);
    int match_length          = 0;
    int TEST_EXECUTABLE_MATCH = re_matchp(TEST_EXECUTABLE_REGEX, TEST_EXECUTABLE, &match_length);
    int IS_TEST_EXECUTABLE    = (match_length > 0);
    if (IS_TEST_EXECUTABLE) {
      vector_push(TEST_EXECUTABLES_v, (char *)strdup(TEST_EXECUTABLE));
    }
  }
  char *REPOSITORY_EXECUTABLE;

  for (int i = 0; i < vector_size(REPOSITORY_EXECUTABLES_v); i++) {
    REPOSITORY_EXECUTABLE = (char *)vector_get(REPOSITORY_EXECUTABLES_v, i);
    //dbg(REPOSITORY_EXECUTABLE, %s);
  }
  //dbg(vector_size(TEST_EXECUTABLES_v), %d);
  for (int i = 0; i < vector_size(TEST_EXECUTABLES_v); i++) {
    TEST_EXECUTABLE = (char *)vector_get(TEST_EXECUTABLES_v, i);
    char   *src_file = malloc(strlen(TEST_EXECUTABLE) + 1024);
    sprintf(src_file, "%s.c", TEST_EXECUTABLE);
    char   *src_file_contents = fsio_read_text_file(src_file);
    size_t qty                = occurrences("GREATEST_MAIN_DEFS", src_file_contents);
    if (qty < 1) {
      continue;
    }
    struct StringFNStrings src_file_lines = stringfn_split_lines_and_trim(src_file_contents);
    for (int ii = 0; ii < src_file_lines.count; ii++) {
      qty = occurrences("RUN_SUITE(", src_file_lines.strings[ii]);
      if (qty == 1) {
        struct StringFNStrings s01 = stringfn_split(src_file_lines.strings[ii], ')');
        if (s01.count == 2) {
          struct StringFNStrings s02         = stringfn_split(s01.strings[0], '(');
          char                   *SUITE_NAME = s02.strings[1];
          //dbg(SUITE_NAME, %s);
        }
      }
    }
    free(src_file);
    free(src_file_contents);
  }
  generate_results_table(MESON_RESULTS);
} /* iterate_parse_results */


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
      log_error("NOT HANDLED> type: '%s' qty:%d", type, ee_listener_count(ee, type));
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
    // usleep(1000 * 10);
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
  char *MESON_PATH = strdup((char *)_MESON_PATH);

  if (CACHE_ENABLED && cached_key_file_exists(MESON_PATH)) {
    //usleep(1000 * 10);
    char *c = cached_key_file_content(MESON_PATH);
    free(MESON_PATH);
    return(c);
  }
  const char           *command_line[] = {
    "/usr/local/bin/meson",
    "introspect",
    "--all",
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
  assert(result == 0);
  do {
    bytes_read = subprocess_read_stdout(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
    index += bytes_read;
  } while (bytes_read != 0);

  result = subprocess_join(&subprocess, &exited);
  assert(result == 0);
  assert(exited == 0);

  READ_STDOUT = stringbuffer_to_string(SB);
  stringbuffer_release(SB);

  if (DEBUG_STDOUT) {
    /*
     * dbg(exited, %d);
     * dbg(command_line[2], %s);
     * dbg(strlen(READ_STDOUT), %lu);
     */
    fprintf(stderr, "%s", READ_STDOUT);
  }
  write_cached_key_file_content(MESON_PATH, READ_STDOUT);
  return(READ_STDOUT);
} /* execute_meson_introspect */


void *execute_meson_job(void *_WORKER_ID){
  size_t                 WORKER_ID = (size_t)_WORKER_ID;
  void                   *_job;
  size_t                 qty = 0;

  struct StringFNStrings items;

  while (chan_recv(JOBS_CHANNEL, &_job) == 0) {
    char               *job = (char *)_job;
    items = stringfn_split(job, '/');
    meson_job_result_t *job_result = calloc(1, sizeof(meson_job_result_t));
    job_result->name = calloc(1, strlen(items.strings[items.count - 2]) + 1);
    sprintf(job_result->name, "%s", items.strings[items.count - 2]);

    if (DEBUG_EXECUTE_MESON_JOB) {
      fprintf(stderr,
              AC_RESETALL AC_REVERSED AC_YELLOW "%lu> Worker processing job #%lu of %lu bytes:     '%s'\n" AC_RESETALL,
              WORKER_ID, qty, strlen(job), job);
    }
    unsigned long started = timestamp();
    job_result->json = execute_meson_introspect(job);
    job_result->dur  = timestamp() - started;
    job_result->dur  = timestamp() - started;
    progress_tick(progress, 1);
    chan_send(RESULTS_CHANNEL, (void *)job_result);
    qty++;
  }
  if (DEBUG_EXECUTE_MESON_JOB) {
    fprintf(stderr, "Worker #%lu finished\n", WORKER_ID);
  }
  stringfn_release_strings_struct(items);
}


struct Vector * execute_meson_introspects(struct Vector *MESON_PATHS){
  unsigned long prog_qty = vector_size(MESON_PATHS);

  progress           = progress_new(prog_qty, PROGRESS_BAR_WIDTH);
  progress->fmt      = "    Progress (:percent) => {:bar} [:elapsed]";    progress->bg_bar_char = BG_PROGRESS_BAR_CHAR;
  progress->bar_char = PROGRESS_BAR_CHAR;    progress_on(progress, PROGRESS_EVENT_START, introspection_progress_start);
  progress_on(progress, PROGRESS_EVENT_PROGRESS, introspection_progress);    progress_on(progress, PROGRESS_EVENT_END, introspection_progress_end);

  pthread_t worker_threads[WORKERS_QTY];
  pthread_t waiter_thread;
  size_t    workers_qty = 0;

  meson_results   = vector_new();
  DONE_CHANNEL    = chan_init(0);
  JOBS_CHANNEL    = chan_init(WORKERS_QTY);
  RESULTS_CHANNEL = chan_init(WORKERS_QTY);
  ct_start(NULL);

  int res = pthread_create(&waiter_thread, NULL, receive_meson_results, (void *)vector_size(MESON_PATHS));

  assert(0 == res);

  for (size_t i = 0; (i < WORKERS_QTY) && (i < vector_size(MESON_PATHS)); i++) {
    int res = pthread_create(&worker_threads[i], NULL, execute_meson_job, (void *)i);
    assert(0 == res);
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

  if (DEBUG_CHANNELS) {
    fprintf(stdout,
            AC_RESETALL AC_GREEN AC_REVERSED "done channel recvd %lu results of %lub using %lu workers in %s\n" AC_RESETALL,
            (size_t)vector_size(meson_results),
            iterate_get_total_size(meson_results),
            workers_qty,
            dur
            );
  }
  //usleep(1000*10);
  progress_value(progress, prog_qty);
  usleep(1000 * 10);
  progress_free(progress);

  return(meson_results);
} /* execute_meson_introspects */


char *execute_processes(char *MESON_BUILD_FILE){
  uint8_t             output[MAX_OUTPUT_BYTES];
  reproc_event_source children[1] = { { 0 } };
  int                 r           = -1;

  for (int i = 0; i < 1; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[] = {
      which("meson"),
      "introspect",
      "--all",
      "--backend",
      "ninja",
      "--force-object-output",
      MESON_BUILD_FILE,
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
    r = reproc_poll(children, 1, REPROC_INFINITE);
    if (r < 0) {
      r = r == REPROC_EPIPE ? 0 : r;
      goto finish;
    }

    for (int i = 0; i < 1; i++) {
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
  for (int i = 0; i < 1; i++) {
    reproc_destroy(children[i].process);
  }

  if (r < 0) {
    log_error("%s", reproc_strerror(r));
  }

  char *o = calloc(1, strlen(output) + 1);

  sprintf(o, "%s", stringfn_trim(output));
  return(o);
} /* execute_processes */
