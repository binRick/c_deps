////////////////////////////////////////////

////////////////////////////////////////////
#include "libspinner-test/libspinner-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libspinner/spinner.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"
int SLEEP_DUR_MS = 5000;

////////////////////////////////////////////
TEST t_libspinner_test(){
  spinner_t *s = spinner_new(32);

  s->delay     = 100000;
  s->prefix    = "Running ";
  s->suffix    = " I'm a suffix";
  s->final_msg = "Complete!\n";
  spinner_start(s);
  usleep(1000 * SLEEP_DUR_MS);
  spinner_stop(s);
  spinner_free(s);
  PASS();
}

SUITE(s_libspinner_test) {
  RUN_TEST(t_libspinner_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  if (!isatty(STDOUT_FILENO)) {
    SLEEP_DUR_MS = 10;
  }
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_libspinner_test);
  GREATEST_MAIN_END();
}
