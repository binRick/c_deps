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
#include "log.h/log.h"

const char *STRING = "This is a decoded string.";

////////////////////////////////////////////
TEST t_base64_test(){
  char *ENCODED_STRING = base64_encode(STRING);
  char *DECODED_STRING = base64_decode(ENCODED_STRING);

  log_info("String:         %s", STRING);
  log_info("Encoded String: %s", ENCODED_STRING);
  log_info("Decoded String: %s", DECODED_STRING);

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
