////////////////////////////////////////////

////////////////////////////////////////////
#include "path-normalize-test/path-normalize-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "path-normalize.c/src/path-normalize.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_path_normalize_test(){
  char *path = NULL;

  assert(NULL == path_normalize(NULL));

  path = path_normalize("/home//stephen//");
  assert(0 == strcmp("/home/stephen/", path));
  free(path);

  path = path_normalize("home//stephen//");
  assert(0 == strcmp("home/stephen/", path));
  free(path);

  path = path_normalize("/home//stephen//");
  assert(0 == strcmp("/home/stephen/", path));
  free(path);

  path = path_normalize("////home//stephen");
  assert(0 == strcmp("/home/stephen", path));
  free(path);
  PASS();
}

SUITE(s_path_normalize_test) {
  RUN_TEST(t_path_normalize_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_path_normalize_test);
  GREATEST_MAIN_END();
}
