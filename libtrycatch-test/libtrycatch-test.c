////////////////////////////////////////////

////////////////////////////////////////////
#include "libtrycatch-test/libtrycatch-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libtrycatch/trycatch.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_libtrycatch_test(){
  try {
    puts("try1");
    try {
      puts("try2");
    } catch(ex) {
      puts("this should not be called");
    }

    try {
      throw(7);
    } catch(ex) {
      rethrow;
    }
    throw(5);
  } catch(ex) {
    printf("caught %d (should be 7)\n", ex);
  }
  PASS();
}

SUITE(s_libtrycatch_test) {
  RUN_TEST(t_libtrycatch_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_libtrycatch_test);
  GREATEST_MAIN_END();
}
