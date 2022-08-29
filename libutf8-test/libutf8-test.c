////////////////////////////////////////////

////////////////////////////////////////////
#include "libutf8-test/libutf8-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libutf8/utf8.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_libutf8_test(){
  char str[] = "Foo © bar 𝌆 baz ☃ qux";
  char *enc  = NULL;
  char *dec  = NULL;

  enc = utf8_encode(str);

  if (NULL == enc) {
    utf8_perror("encode");
    return(1);
  }

  dec = utf8_decode(enc);

  if (NULL == dec) {
    utf8_perror("decode");
    return(1);
  }

  ASSERT_EQ(strcmp(str, dec), 0);
  PASS();
}

SUITE(s_libutf8_test) {
  RUN_TEST(t_libutf8_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_libutf8_test);
  GREATEST_MAIN_END();
}
