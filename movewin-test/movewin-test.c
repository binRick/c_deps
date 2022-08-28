////////////////////////////////////////////

////////////////////////////////////////////
#include "movewin-test/movewin-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_movewin_test(){
  PASS();
}

SUITE(s_movewin_test) {
  RUN_TEST(t_movewin_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_movewin_test);
  GREATEST_MAIN_END();
}
