////////////////////////////////////////////

////////////////////////////////////////////
#include "path-module-test/path-module-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "path_module/src/path.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_path_module_test(){
  char        *pathname = "/projects/path_module/path.c";
  struct Path path      = path_parse(pathname);

  printf("dirname: %.*s\n", (int)path.dirname_len, path.dirname);
  printf("basename: %s\n", path.basename);

  // copy to another buffer
  char dirname[path.dirname_len + 1];

  memset(dirname, 0, sizeof(dirname));

  memcpy(dirname, path.dirname, path.dirname_len);
  printf("your dirname: %s\n", dirname);
  PASS();
}

SUITE(s_path_module_test) {
  RUN_TEST(t_path_module_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_path_module_test);
  GREATEST_MAIN_END();
}
