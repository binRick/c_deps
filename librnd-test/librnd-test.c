////////////////////////////////////////////

////////////////////////////////////////////
#include "librnd-test/librnd-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "librnd/rnd.h"
#include "log/log.h"

////////////////////////////////////////////
TEST t_librnd_test(){
  struct rnd *rnd   = rnd_alloc();
  uint32_t   number = rnd_next_uniform_value_in_range(rnd, 1, 100);

  log_info("%u", number);

  rnd_free(rnd);

  PASS();
}

SUITE(s_librnd_test) {
  RUN_TEST(t_librnd_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_librnd_test);
  GREATEST_MAIN_END();
}
