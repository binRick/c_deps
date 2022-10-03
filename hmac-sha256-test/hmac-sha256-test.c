////////////////////////////////////////////
#define HMAC_SHA256_DIGEST_SIZE    32
////////////////////////////////////////////
#include "hmac-sha256-test/hmac-sha256-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "hmac_sha256/hmac-sha256.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_hmac_sha256_test(){
  PASS();
}

SUITE(s_hmac_sha256_test) {
  RUN_TEST(t_hmac_sha256_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_hmac_sha256_test);
  GREATEST_MAIN_END();
}
