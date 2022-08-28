////////////////////////////////////////////

////////////////////////////////////////////
#include "slug-test/slug-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "slug.c/src/slug.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_slug_test(){
  char *s0 = "foo b ar@-";
  char s01[32];

  sprintf(s01, "%s", s0);
  char *s1 = slug(s01);

  fprintf(stdout, "\nSLUG: '%s'->'%s'\n", s01, s1);
  PASS();
}

SUITE(s_slug_test) {
  RUN_TEST(t_slug_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_slug_test);
  GREATEST_MAIN_END();
}
