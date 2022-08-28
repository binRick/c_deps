////////////////////////////////////////////

////////////////////////////////////////////
#include "md5-test/md5-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "b64.c/b64.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "rhash_md5.c/md5.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_md5_test(){
  md5_ctx       ctx;
  const char    *IN = "hello world!";
  unsigned char hash[16];

  rhash_md5_init(&ctx);
  rhash_md5_update(&ctx, (const unsigned char *)IN, strlen(IN));
  rhash_md5_final(&ctx, hash);

  printf("MD5 of '%s' is '%s'\n",
         IN, stringfn_replace(stringfn_trim(stringfn_replace(stringfn_replace(b64_encode(hash, 16), '/', '_'), '=', ' ')), ' ', '_')
         );
  PASS();
}

SUITE(s_md5_test) {
  RUN_TEST(t_md5_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_md5_test);
  GREATEST_MAIN_END();
}
