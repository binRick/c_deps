////////////////////////////////////////////

////////////////////////////////////////////
#include "genpassword-test/genpassword-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "genpassword.c/src/genpassword.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_genpassword_test(){
  int passed = true;

  srand(time(NULL));

  int  length    = 10;
  char *password = generate_password(length);

  if (strlen(password) == (size_t)length) {
  } else {
    passed = false;
    printf("\x1B[31mFirst test failed. \n");       // Print in red
    printf("Generated password: %s, at length: %i\n", password, length);
  }
  printf("\x1B[32mFirst test passed.:      '%s' \n", password);        // Print in green

  // free memory
  free(password);

  // Second test
  length   = 15;
  password = generate_password(length);
  if (strlen(password) == (size_t)length) {
    printf("\x1B[32mSecond test passed. \n");       // Print in green
  } else {
    passed = false;
    printf("\x1B[31mSecond test failed. \n");       // Print in red
    printf("Generated password: %s, at length: %i\n", password, length);
  }

  printf("\x1B[32msecond test passed.:      '%s' \n", password);        // Print in green
  // Return to normal color.
  printf("\x1B[0m");

  // free memory
  free(password);
  PASS();
}

SUITE(s_genpassword_test) {
  RUN_TEST(t_genpassword_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_genpassword_test);
  GREATEST_MAIN_END();
}
