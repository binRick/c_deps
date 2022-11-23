////////////////////////////////////////////

////////////////////////////////////////////
#include "generic-print-test/generic-print-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "generic-print/print.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_generic_print_test_number(){
  int i = 100;

  PRINT("some number", i);
  PASS();
}

TEST t_generic_print_test_string(){
  char *s = "xxxxxxxxxxxX";

  PRINT("string", s);
  PASS();
}

TEST t_generic_print_test_array(){
  int  x[]     = { 1, 2, 3 };
  char *args[] = { "gcc", "hello.c", "-o", "hello" };

  PRINT(x, args);
  PASS();
}

SUITE(s_generic_print_test) {
  RUN_TEST(t_generic_print_test_array);
  RUN_TEST(t_generic_print_test_string);
  RUN_TEST(t_generic_print_test_number);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_generic_print_test);
  GREATEST_MAIN_END();
}
