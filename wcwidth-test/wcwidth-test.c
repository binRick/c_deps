////////////////////////////////////////////

////////////////////////////////////////////
#include "wcwidth-test/wcwidth-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "wcwidth/wcwidth.h"

////////////////////////////////////////////
TEST t_wcwidth_test(){
  int len;

  len = string_width("こんにちわ世界");
  log_info("len: %d", len);
  ASSERT_EQ(len, 14);
  PASS();
}

SUITE(s_wcwidth_test) {
  RUN_TEST(t_wcwidth_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_wcwidth_test);
  GREATEST_MAIN_END();
}
