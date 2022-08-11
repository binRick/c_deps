////////////////////////////////////////////////////////
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
////////////////////////////////////////////////////////
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "submodules/log.h/log.h"
#include <assert.h>
////////////////////////////////////////////////////////
#include "subprocess-test-main.c"
#include "subprocess-test.h"
#define FIND_PATH                      "."
#define FZF_STDOUT_READ_BUFFER_SIZE    1024 * 16
//////////////////////////////////////////////


char *subprocess_fzf_test_0(void){
  char                *READ_STDOUT;
  int                 exited, result;
  struct subprocess_s subprocess;
  char                *CMD;

  asprintf(&CMD,
           "");

  const char           *exec_cmd[] = {
    "/usr/bin/env",                           "sh", "--norc", "--noprofile", "-c",
    "fzf -m --reverse --header='header 123'",
    NULL
  };
  char                 stdout_buffer[STDOUT_READ_BUFFER_SIZE] = { 0 };
  struct  StringBuffer *SB                                    = stringbuffer_new_with_options(STDOUT_READ_BUFFER_SIZE, true);
  size_t               bytes_read                             = 0,
                       index                                  = 0;

  result = subprocess_create(exec_cmd, 0, &subprocess);
  assert_eq(result, 0, %d);

  FILE *p_stdin = subprocess_stdin(&subprocess);

  fputs("a\nb\nc\nWOW", p_stdin);

  do {
    bytes_read = subprocess_read_stdout(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
    index += bytes_read;
  } while (bytes_read != 0);

  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  dbg(exited, %d);
  assert_eq(exited, 0, %d);

  READ_STDOUT = stringbuffer_to_string(SB);

  stringbuffer_release(SB);
  dbg(exec_cmd[5], %s);
  dbg(strlen(READ_STDOUT), %u);
  if (DEBUG_STDOUT) {
    fprintf(stderr, "%s", READ_STDOUT);
  }

  return(0);
} /* subprocess_fzf_test_0 */


TEST t_subprocess_0(void *CMD){
  subprocess_test_main((char *)CMD);
  PASS();
}

GREATEST_MAIN_DEFS();

SUITE(s_subprocess_find){
  RUN_TESTp(t_subprocess_0, "find " FIND_PATH " -type d");
  RUN_TESTp(t_subprocess_0, "find " FIND_PATH " -type f");
  PASS();
}

SUITE(s_subprocess_fzf){
  // char *output = subprocess_fzf_test_0();
  // log_info("output:%s\n",output);
  PASSm("FZF Tests OK");
}


SUITE(s_subprocess_basic){
  RUN_TESTp(t_subprocess_0, "ls");
  RUN_TESTp(t_subprocess_0, "pwd");
  PASS();
}


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_subprocess_basic);
  RUN_SUITE(s_subprocess_find);
  if (isatty(STDOUT_FILENO)) {
    RUN_SUITE(s_subprocess_fzf);
  }


  GREATEST_MAIN_END();
  return(0);
}

