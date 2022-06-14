#include "submodules/log.h/log.h"
#include "subprocess-test-main.c"
#include "subprocess-test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FIND_PATH    "."

//////////////////////////////////////////////


TEST t_subprocess_0(void *CMD){
  subprocess_test_main((char *)CMD);
  PASS();
}

GREATEST_MAIN_DEFS();

SUITE(t_subprocess_find){
  RUN_TESTp(t_subprocess_0, "find " FIND_PATH " -type d");
  RUN_TESTp(t_subprocess_0, "find " FIND_PATH " -type f");
  PASS();
}

SUITE(t_subprocess_basic){
  RUN_TESTp(t_subprocess_0, "ls");
  RUN_TESTp(t_subprocess_0, "pwd");
  PASS();
}


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(t_subprocess_basic);
  RUN_SUITE(t_subprocess_find);

  GREATEST_MAIN_END();
  return(0);
}

