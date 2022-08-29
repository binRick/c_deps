////////////////////////////////////////////

////////////////////////////////////////////
#include "is-number-test/is-number-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "is_number.c/is_number.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_is_number_test(){
  const char *str = "1.0";
  int        is_num;

  is_num = is_number("1.0", 3);
  assert(is_num);

  is_num = is_number_with("1.", 2, ALLOW_EMPTY_POST_DOT);
  assert(is_num);

  is_num = is_number("1.", 2);
  assert(!is_num);
  PASS();
}

SUITE(s_is_number_test) {
  RUN_TEST(t_is_number_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_is_number_test);
  GREATEST_MAIN_END();
}
