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
#include "exec-fzf-test/exec-fzf-test.h"
#include "exec-fzf/exec-fzf.h"
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
#include "ansi-utils/ansi-utils.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "exec-fzf-test/exec-fzf-test.h"
#include "submodules/log.h/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
//////////////////////////////////////////////
static void __attribute__((destructor)) __exec_fzf_test_destructor();

static void __attribute__((constructor)) __exec_fzf_test_constructor();


//////////////////////////////////////////////


TEST t_reproc_fzf_process(void){
  int               res = -1;

  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  fe->header     = "my header 123444";
  fe->debug_mode = false;
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  res = exec_fzf(fe);
  ASSERT_EQm("fzf process OK", res, 0);
  exec_fzf_release(fe);

  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));


  PASS();
}


GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
    RUN_TEST(t_reproc_fzf_process);
  }
  GREATEST_MAIN_END();
  return(0);
}


static void __attribute__((constructor)) __exec_fzf_test_constructor(){
}
static void __attribute__((destructor)) __exec_fzf_test_destructor(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "<%d> [%s] Checking for memory leaks\n", getpid(), __FUNCTION__);
  print_allocated_memory();
#endif
}
