////////////////////////////////////////////

////////////////////////////////////////////
#include "expboff-test/expboff-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "expboff/expboff.h"
#include "log.h/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
int MAX_BACKOFF_MS = 1500;

////////////////////////////////////////////
TEST t_expboff_test(){
  int max = 55, cur = 0, boff = 0;

  while (cur < max) {
    boff = expboff(cur, 0, MAX_BACKOFF_MS);
    log_info("cur:%d|boff:%d", cur, boff);
    usleep(10 * boff);
    cur++;
  }
  PASS();
}

SUITE(s_expboff_test) {
  RUN_TEST(t_expboff_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  if (!isatty(STDOUT_FILENO)) {
    MAX_BACKOFF_MS = 5;
  }
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_expboff_test);
  GREATEST_MAIN_END();
}
