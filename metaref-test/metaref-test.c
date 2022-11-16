
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libmetaref/include/exotic/metaref.h"
#include "log/log.h"
#include "metaref-test/metaref-test.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

#define __STRUCT_NAME__    Friend

TEST t_metaref_test2(){
  PASS();
}

TEST t_metaref_test1(){
  PASS();
}

SUITE(s_metaref_test) {
  RUN_TEST(t_metaref_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_metaref_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_metaref_test);
  GREATEST_MAIN_END();
}
