////////////////////////////////////////////

////////////////////////////////////////////
#include "minmax-test/minmax-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "minmax/include/minmax.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_minmax_test(){
  int val;

  val = max(2, 5);
  ASSERT_EQ(val, 5);
  PASS();
}

SUITE(s_minmax_test) {
  RUN_TEST(t_minmax_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_minmax_test);
  GREATEST_MAIN_END();
}
