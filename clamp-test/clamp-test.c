////////////////////////////////////////////

////////////////////////////////////////////
#include "clamp-test/clamp-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "clamp/clamp.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_clamp_test(){
  int value = 5;

  value = clamp(value, 0, 4);
  ASSERT_EQ(value, 4);
  PASS();
}

SUITE(s_clamp_test) {
  RUN_TEST(t_clamp_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_clamp_test);
  GREATEST_MAIN_END();
}
