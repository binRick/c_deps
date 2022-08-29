////////////////////////////////////////////
#include <stdio.h>
////////////////////////////////////////////
#include "chfreq-test/chfreq-test.h"
////////////////////////////////////////////
#include "c_greatest/greatest/greatest.h"
#include "chfreq.c/chfreq.h"

////////////////////////////////////////////
TEST t_chfreq_test(){
  /*
   * sleep(1);
   * char     *str = "110aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz102";
   * uint32_t **f  = chfreq(str);
   * uint32_t *cur = NULL;
   *
   * printf("str: %s\n", str);
   * for (int i = 0; NULL != (cur = f[i]); ++i) {
   * char c  = cur[0];
   * int  cf = cur[1];
   * printf("#%d> char: %c | qty: %d |\n", i, c, cf);
   * }
   */
  PASS();
}

SUITE(s_chfreq_test) {
  RUN_TEST(t_chfreq_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_chfreq_test);
  GREATEST_MAIN_END();
}
