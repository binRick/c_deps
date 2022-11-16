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
#include "reproc-test/reproc-test-fzf.h"
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
#include "ansi-utils/ansi-utils.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "reproc-test.h"
#include "submodules/log/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
//////////////////////////////////////////////
#define NUM_CHILDREN    10
//////////////////////////////////////////////
static int execute_processes();

static void __attribute__((destructor)) __test_subprocess_destructor();
static void __attribute__((constructor)) __test_subprocess_constructor();

//////////////////////////////////////////////
extern struct fzf_exec_t *fzf_exec;

TEST t_reproc_fzf_process(void){
  int res = execute_fzf_process();

  ASSERT_EQm("fzf process OK", res, 0);
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
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_reproc_fzf_process);
  GREATEST_MAIN_END();
  return(0);
}

static int execute_processes(){
  reproc_event_source children[NUM_CHILDREN] = { { 0 } };
  int                 r                      = -1;

  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[] = { "date", NULL };

    r = reproc_start(process, date_args, (reproc_options){ .nonblocking = true });
    if (r < 0)
      goto finish;

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
      if (children[i].process == NULL || !children[i].events)
        continue;
      uint8_t output[4096];
      r = reproc_read(children[i].process, REPROC_STREAM_OUT, output, sizeof(output));
      if (r == REPROC_EPIPE) {
        children[i].process = reproc_destroy(children[i].process);
        continue;
      }

      if (r < 0)
        goto finish;
      output[r] = '\0';

      char msg[1024];
      sprintf(&msg, "<%d> " AC_RESETALL AC_YELLOW_BLACK AC_REVERSED AC_ITALIC "%s" AC_RESETALL, getpid(), stringfn_trim(output));
      log_debug("%s", msg);
    }
  }

finish:
  for (int i = 0; i < NUM_CHILDREN; i++)
    reproc_destroy(children[i].process);

  if (r < 0)
    log_error("%s", reproc_strerror(r));

  return(abs(r));
} /* execute_processes */

static void __attribute__((constructor)) __test_subprocess_constructor(){
}
static void __attribute__((destructor)) __test_subprocess_destructor(){
  if (fzf_exec)
    free(fzf_exec);

#ifdef DEBUG_MEMORY
  fprintf(stderr, "<%d> [%s] Checking for memory leaks\n", getpid(), __FUNCTION__);
  print_allocated_memory();
#endif
}
