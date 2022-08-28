////////////////////////////////////////////

////////////////////////////////////////////
#include "murmurhash-test/murmurhash-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "murmurhash.c/murmurhash.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_murmurhash_test(){
  uint32_t   seed = 666;
  const char *key = "hello123";
  uint32_t   hash = murmurhash(key, (uint32_t)strlen(key), seed);

  printf("key: %s", key);
  printf("seed: %d", seed);
  printf("hash: %" PRIu32 "", hash);
  PASS();
}

SUITE(s_murmurhash_test) {
  RUN_TEST(t_murmurhash_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_murmurhash_test);
  GREATEST_MAIN_END();
}
