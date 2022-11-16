
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "extname-test/extname-test.h"
#include "extname.c/src/extname.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

TEST t_extname_test2(){
  PASS();
}

TEST t_extname_test1(){
  char *ext, *str;

  str = "some/extension.zip";

  ext = extname(str);
  ASSERT_STR_EQ(".zip", ext);
  log_info("The extension of %s is %s", str, ext);
  PASS();
}

SUITE(s_extname_test) {
  RUN_TEST(t_extname_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_extname_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_extname_test);
  GREATEST_MAIN_END();
}
