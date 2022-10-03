////////////////////////////////////////////

////////////////////////////////////////////
#include "sha256-test/sha256-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "sha256.c/sha256.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_sha256_test(){
  char          *input = "hello123";
  unsigned char buf[32];
  sha256_t      hash;

  sha256_init(&hash);
  sha256_update(&hash, (unsigned char *)input, strlen(input));
  sha256_final(&hash, buf);

  log_info("hash:%s", buf);
  PASS();
}

SUITE(s_sha256_test) {
  RUN_TEST(t_sha256_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_sha256_test);
  GREATEST_MAIN_END();
}
