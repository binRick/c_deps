////////////////////////////////////////////

////////////////////////////////////////////
#include "bitfield-test/bitfield-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bitfield/bitfield.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_bitfield_test(){
  bitfield_t *bf = bitfield_new(100);

  bitfield_mark(bf, 77);
  bitfield_unmark(bf, 50);
  bool im = bitfield_is_marked(bf, 77);

  ASSERT_EQ(im, true);
  im = bitfield_is_marked(bf, 78);
  ASSERT_EQ(im, false);
  printf("77th bit is marked\n");
  printf("78th bit is not marked\n");
  PASS();
}

SUITE(s_bitfield_test) {
  RUN_TEST(t_bitfield_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_bitfield_test);
  GREATEST_MAIN_END();
}
