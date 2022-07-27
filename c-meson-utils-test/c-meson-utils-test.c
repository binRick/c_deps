#include "c-meson-utils-test/c-meson-utils-test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

//////////////////////////////////////////////


TEST t_c_meson_utils_test0(){
  PASS();
}


SUITE(s_c_meson_utils_test0){
  RUN_TEST(t_c_meson_utils_test0);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_c_meson_utils_test0);

  GREATEST_MAIN_END();
  return(0);
}

