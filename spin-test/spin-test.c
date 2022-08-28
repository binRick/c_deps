////////////////////////////////////////////

////////////////////////////////////////////
#include "spin-test/spin-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "spin/spin.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_spin_test(){
  const int big_number = 1000000000;
  spinner   *s         = spin_new(utf8_pat1, "Working", UTF8_CHAR_WIDTH);
  int       x          = 0;
  int       working    = 1;

  while (working) {
    if (x == (big_number * .25)) {
      spin_upd_msg(s, "Part way through");       // update the status message
      spin_drw(s);
    }
    if (x == (big_number * .75)) {
      spin_upd_msg(s, "Getting close now");
      spin_drw(s);
    }
    if (x % 9999999 == 0) {  // this is just to throttle it a bit
      spin_drw(s);
    }
    if (x++ > big_number) {
      working = 0;
    }
  }
  spin_del(s);   // cleanup
  printf("Done!\n");
  PASS();
}

SUITE(s_spin_test) {
  RUN_TEST(t_spin_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_spin_test);
  GREATEST_MAIN_END();
}
