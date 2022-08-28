////////////////////////////////////////////

////////////////////////////////////////////
#include "str-replace-test/str-replace-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "str-replace.c/src/str-replace.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_str_replace_test(){
  char *replaced = str_replace("hello world", "hello", "goodbye");

  printf("%s\n", replaced);
  free(replaced);
  PASS();
}

SUITE(s_str_replace_test) {
  RUN_TEST(t_str_replace_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_str_replace_test);
  GREATEST_MAIN_END();
}
