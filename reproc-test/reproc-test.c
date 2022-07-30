//////////////////////////////////////////////
#define DEBUG_MEMORY
//////////////////////////////////////////////
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
#include "ansi-utils/ansi-utils.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "reproc-test.h"
#include "submodules/log.h/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
//////////////////////////////////////////////
#define NUM_CHILDREN    10
//////////////////////////////////////////////
static int execute_processes();
static int execute_fwded_process();
static inline void millisleep(long ms);

static struct fzf_exec_t *fzf_exec;
static void __attribute__((destructor)) __test_subprocess_destructor();

static void __attribute__((constructor)) __test_subprocess_constructor();


//////////////////////////////////////////////
TEST t_reproc_fwded_process(void){
  int res = execute_fwded_process();

  ASSERT_EQm("fwd process OK", res, 0);
  PASS();
}


TEST t_reproc_0(void){
  int res = execute_processes();

  ASSERT_EQm("reproc0 OK", res, 0);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_TEST(t_reproc_0);
  if (isatty(STDOUT_FILENO)) {
    RUN_TEST(t_reproc_fwded_process);
  }
  GREATEST_MAIN_END();
  return(0);
}

struct fzf_exec_t {
  struct Vector          *input_options;
  struct Vector          *selected_options;
  char                   **input_array;
  char                   *input_s;
  char                   *output_file;
  char                   *tempdir;
  struct StringFNStrings output_lines;
  char                   *header;
  char                   *fzf_cmd;
  char                   *fzf_path;
  char                   **subprocess_cmd;
  int                    proc_result;
  int                    proc_exit_code;
  reproc_t               *proc;
  reproc_options         reproc_options;
};


void setup_fzf_exec(void){
  fzf_exec                = malloc(sizeof(struct fzf_exec_t));
  fzf_exec->header        = "my header 123";
  fzf_exec->input_options = vector_new();
  vector_push(fzf_exec->input_options, "option 1");
  vector_push(fzf_exec->input_options, "option 2");
  vector_push(fzf_exec->input_options, "option 3");
  vector_push(fzf_exec->input_options, "option 4");
}


static int execute_fwded_process(){
  if (fzf_exec->selected_options == NULL) {
    fzf_exec->selected_options = vector_new();
  }
  fzf_exec->reproc_options = (reproc_options) { .redirect.parent = true, };
  fzf_exec->tempdir        = gettempdir();
  fzf_exec->fzf_path       = (char *)which_path("fzf", getenv("PATH")),
  fzf_exec->input_array    = vector_to_array(fzf_exec->input_options);
  fzf_exec->input_s        = stringfn_join(fzf_exec->input_array, "\\n", 0, vector_size(fzf_exec->input_options));
  log_info("%lu in:'%s'\n", vector_size(fzf_exec->input_options), fzf_exec->input_s);
  asprintf(&fzf_exec->output_file, "%s.output-file-%lld.txt",
           fzf_exec->tempdir,
           timestamp()
           );
  log_info("%s", fzf_exec->output_file);
  asprintf(&fzf_exec->fzf_cmd,
           "printf '%s' | %s -m --reverse --header='%s' > '%s'",
           fzf_exec->input_s,
           fzf_exec->fzf_path,
           fzf_exec->header,
           fzf_exec->output_file
           );

  const char *exec_cmd[] = {
    "/usr/bin/env",    "sh", "--norc", "--noprofile", "-c",
    fzf_exec->fzf_cmd,
    NULL
  };

  fzf_exec->proc_result = REPROC_ENOMEM;

  fzf_exec->proc = reproc_new();
  if (fzf_exec->proc == NULL) {
    goto finish;
  }

  if (fsio_file_exists(fzf_exec->output_file)) {
    fsio_remove(fzf_exec->output_file);
  }

  log_info("%s", fzf_exec->fzf_cmd);
  fzf_exec->proc_result = reproc_start(fzf_exec->proc, exec_cmd, (reproc_options){
    .redirect.parent = true
  });

  log_info("%d", fzf_exec->proc_result);

  if (fzf_exec->proc_result < 0) {
    goto finish;
  }

  fzf_exec->proc_exit_code = reproc_wait(fzf_exec->proc, REPROC_INFINITE);
  log_info("%d", fzf_exec->proc_exit_code);

finish:
  log_info("finished");
  reproc_destroy(fzf_exec->proc);
  log_info("destroyed");


  if (fzf_exec->proc_result < 0) {
    fprintf(stderr, "Error: %s\n", reproc_strerror(fzf_exec->proc_result));
  }else{
    if (fsio_file_exists(fzf_exec->output_file)) {
      char *output = stringfn_mut_trim(fsio_read_text_file(fzf_exec->output_file));
      log_info("out file: %s", fzf_exec->output_file);
      fzf_exec->output_lines = stringfn_split_lines_and_trim(output);
      log_info("out file lines: %d", fzf_exec->output_lines.count);
      fsio_remove(fzf_exec->output_file);
      for (size_t i = 0; i < fzf_exec->output_lines.count; i++) {
        log_info("line #%lu- %s", i, fzf_exec->output_lines.strings[i]);
        vector_push(fzf_exec->selected_options, fzf_exec->output_lines.strings[i]);
      }
    }
  }
  log_info("OK, %lu options selected", vector_size(fzf_exec->selected_options));

  log_info("Selected %lu/%lu Options",
           vector_size(fzf_exec->selected_options),
           vector_size(fzf_exec->input_options)
           );

  for (size_t i = 0; i < vector_size(fzf_exec->selected_options); i++) {
    log_info("Selected Option #%lu:  '%s'",
             i,
             (char *)vector_get(fzf_exec->selected_options, i)
             );
  }
  return(EXIT_SUCCESS);
} /* execute_fwded_process */


static int execute_processes(){
  reproc_event_source children[NUM_CHILDREN] = { { 0 } };
  int                 r                      = -1;

  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[] = { "date", NULL };

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
      uint8_t output[4096];
      r = reproc_read(children[i].process, REPROC_STREAM_OUT, output, sizeof(output));
      if (r == REPROC_EPIPE) {
        children[i].process = reproc_destroy(children[i].process);
        continue;
      }

      if (r < 0) {
        goto finish;
      }
      output[r] = '\0';

      char msg[1024];
      sprintf(&msg, "<%d> " AC_RESETALL AC_YELLOW_BLACK AC_REVERSED AC_ITALIC "%s" AC_RESETALL, getpid(), stringfn_trim(output));
      log_debug("%s", msg);
    }
  }

finish:
  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_destroy(children[i].process);
  }

  if (r < 0) {
    log_error("%s", reproc_strerror(r));
  }


  return(abs(r));
} /* execute_processes */


static inline void millisleep(long ms){
  struct timespec ts = {
    .tv_sec  = (ms) / 1000,
    .tv_nsec = ((ms) % 1000L) * 1000000,
  };

  nanosleep(&ts, NULL);
}
static void __attribute__((constructor)) __test_subprocess_constructor(){
  setup_fzf_exec();
}
static void __attribute__((destructor)) __test_subprocess_destructor(){
  if (fzf_exec) {
    free(fzf_exec);
  }
#ifdef DEBUG_MEMORY
  fprintf(stderr, "<%d> [%s] Checking for memory leaks\n", getpid(), __FUNCTION__);
  print_allocated_memory();
#endif
}
