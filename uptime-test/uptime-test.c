////////////////////////////////////////////

////////////////////////////////////////////
#include "uptime-test/uptime-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "timestamp/timestamp.h"
#include "uptime/include/uptime/uptime.h"

////////////////////////////////////////////
TEST t_uptime_test(){
  printf("Uptime: %lu\n", getUptime());
  PASS();
}

SUITE(s_uptime_test) {
  RUN_TEST(t_uptime_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_uptime_test);
  GREATEST_MAIN_END();
}
