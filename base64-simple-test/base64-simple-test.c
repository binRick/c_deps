////////////////////////////////////////////

////////////////////////////////////////////
#include "base64-simple-test/base64-simple-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "base64_simple/src/base64simple.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
const char *STRING = "This is a decoded string.";

////////////////////////////////////////////
TEST t_base64_simple_test(){
  size_t r_size;
  char   *ENCODED_STRING = base64simple_encode(STRING, strlen(STRING));
  char   *DECODED_STRING = base64simple_decode(ENCODED_STRING, strlen(ENCODED_STRING), &r_size);

  log_info("String:         %s", STRING);
  log_info("Encoded String: %s", ENCODED_STRING);
  log_info("Decoded String: %s", DECODED_STRING);

/*
 * decoded = "This is a decoded string.";
 * size    = strlen(decoded);
 * encoded = base64simple_encode(decoded, size);
 * if (encoded == NULL) {
 *  printf("Insufficient Memory!\n");
 * } else {
 *  printf("Encoded: %s\n", encoded);
 * }
 *
 * size    = strlen(encoded);
 * decoded = base64simple_decode(encoded, size, &r_size);
 * if (decoded == NULL) {
 *  printf("Improperly Encoded String or Insufficient Memory!\n");
 * } else {
 *  for (i = 0; i < r_size; ++i) {
 *    // Do something with decoded[i] here
 *  }
 * }
 *
 * // Freeing
 *
 * free(encoded);
 * free(decoded);
 */
  PASS();
}

SUITE(s_base64_simple_test) {
  RUN_TEST(t_base64_simple_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_base64_simple_test);
  GREATEST_MAIN_END();
}
