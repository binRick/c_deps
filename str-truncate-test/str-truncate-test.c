////////////////////////////////////////////

////////////////////////////////////////////
#include "str-truncate-test/str-truncate-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "str-truncate.c/src/str-truncate.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_str_truncate_test(){
  char *str = str_truncate("really long sentence", 2);

  printf("this should only be two characters: %s\n", str);
  PASS();
}

SUITE(s_str_truncate_test) {
  RUN_TEST(t_str_truncate_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_str_truncate_test);
  GREATEST_MAIN_END();
}
