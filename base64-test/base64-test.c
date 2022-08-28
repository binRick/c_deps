////////////////////////////////////////////

////////////////////////////////////////////
#include "base64-test/base64-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "base64/base64.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"

////////////////////////////////////////////
TEST t_base64_test(){
  printf("===============================================================\n");
  printf("%s", base64_decode("SGF2ZSB0byBkZWFsIHdpdGggQmFzZTY0IGZvcm1hdD8gV2VsY29tZSE="));
  printf("\n===============================================================\n\n");

  printf("===============================================================\n");
  printf("%s", base64_encode(base64_decode("SGF2ZSB0byBkZWFsIHdpdGggQmFzZTY0IGZvcm1hdD8gV2VsY29tZSE=")));
  printf("\n===============================================================\n\n");

  PASS();
}

SUITE(s_base64_test) {
  RUN_TEST(t_base64_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_base64_test);
  GREATEST_MAIN_END();
}
