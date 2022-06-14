#include "submodules/log.h/log.h"
#include "tmt-test-main.c"
#include "tmt-test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>


//////////////////////////////////////////////


TEST t_tmt_0(void *CMD){
  tmt_test_main();
}

GREATEST_MAIN_DEFS();

SUITE(t_tmt){
  RUN_TESTp(t_tmt_0, "ls");
  PASS();
}


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(t_tmt);
  GREATEST_MAIN_END();
  return(0);
}

