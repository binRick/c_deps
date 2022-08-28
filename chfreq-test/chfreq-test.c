////////////////////////////////////////////

////////////////////////////////////////////
#include "chfreq-test/chfreq-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chfreq.c/chfreq.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_chfreq_test(){
  char     *str = "110aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz102";
  uint32_t **f  = chfreq(str);
  uint32_t *cur = NULL;

  printf("str: %s\n", str);
  for (int i = 0; NULL != (cur = f[i]); ++i) {
    char c  = cur[0];
    int  cf = cur[1];
    printf("#%d> char: %c | qty: %d |\n", i, c, cf);
  }
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
