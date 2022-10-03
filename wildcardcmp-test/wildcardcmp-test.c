////////////////////////////////////////////

////////////////////////////////////////////
#include "wildcardcmp-test/wildcardcmp-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
#include "wildcardcmp/wildcardcmp.h"
#include <assert.h>

////////////////////////////////////////////
TEST t_wildcardcmp_test(){
  assert(1 == wildcardcmp("foo*", "foo"));
  assert(1 == wildcardcmp("foobar", "foobar"));
  assert(1 == wildcardcmp("*", "foobar"));
  assert(1 == wildcardcmp("foo*", "foobar"));
  assert(1 == wildcardcmp("fo*bar", "foobar"));
  assert(1 == wildcardcmp("*bar", "foobar"));
  assert(1 == wildcardcmp("f*b*r", "foobar"));
  assert(1 == wildcardcmp("f**b*r", "foobar"));
  assert(1 == wildcardcmp("f*", "foobar"));
  // negative
  assert(0 == wildcardcmp("FOOBAR", "foobar"));
  assert(0 == wildcardcmp("foo", "foobar"));
  assert(0 == wildcardcmp("bar*", "foobar"));
  assert(0 == wildcardcmp("f*R", "foobar"));
  // malformed
  assert(0 == wildcardcmp(NULL, "foobar"));
  assert(0 == wildcardcmp("foobar", NULL));
  // the whole point of this lib
  char *DEBUG = "clib:*";
  assert(1 == wildcardcmp(DEBUG, "clib:package"));
  assert(1 == wildcardcmp(DEBUG, "clib:install"));
  assert(1 == wildcardcmp(DEBUG, "clib:search"));
  assert(1 == wildcardcmp(DEBUG, "clib:help"));
  return(0);

  PASS();
}

SUITE(s_wildcardcmp_test) {
  RUN_TEST(t_wildcardcmp_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_wildcardcmp_test);
  GREATEST_MAIN_END();
}
