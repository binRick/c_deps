////////////////////////////////////////////

////////////////////////////////////////////
#include "uuid4-test/uuid4-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
#include "uuid4/src/uuid4.h"

////////////////////////////////////////////
TEST t_uuid4_test(){
  char buf[UUID4_LEN];

  uuid4_init();
  uuid4_generate(buf);
  printf("%s\n", buf);
  PASS();
}

SUITE(s_uuid4_test) {
  RUN_TEST(t_uuid4_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_uuid4_test);
  GREATEST_MAIN_END();
}
