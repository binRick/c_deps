////////////////////////////////////////////

////////////////////////////////////////////
#include "str-flatten-test/str-flatten-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "str-flatten.c/src/str-flatten.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_str_flatten_test(){
  char *arr[] = {
    "this",
    "was",
    "ripped",
    "from",
    "sphia"
  };

  char *s = str_flatten(arr, 0, 5);

  puts(s);
  int r = strcmp("this was ripped from sphia", s);

  ASSERT_EQ(r, 0);
  PASS();
}

SUITE(s_str_flatten_test) {
  RUN_TEST(t_str_flatten_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_str_flatten_test);
  GREATEST_MAIN_END();
}
