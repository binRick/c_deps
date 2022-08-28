////////////////////////////////////////////

////////////////////////////////////////////
#include "occurrences-test/occurrences-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "occurences.c/occurrences.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_occurrences_test(){
  int qty;

  qty = occurrences("l", "hello");
  ASSERT_EQ(2, qty);
  qty = occurrences("L", "hello");
  ASSERT_EQ(0, qty);
  qty = occurrences(NULL, "hello");
  ASSERT_EQ(-1, qty);
  qty = occurrences("hello", NULL);
  ASSERT_EQ(-1, qty);
  PASS();
}

SUITE(s_occurrences_test) {
  RUN_TEST(t_occurrences_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_occurrences_test);
  GREATEST_MAIN_END();
}
