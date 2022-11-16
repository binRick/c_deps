////////////////////////////////////////////

////////////////////////////////////////////
#include "semver-test/semver-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "semver.c/semver.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_semver_test(){
  char     current[] = "1.5.10";
  char     compare[] = "2.3.0";

  semver_t current_version = {};
  semver_t compare_version = {};

  if (semver_parse(current, &current_version)
      || semver_parse(compare, &compare_version)) {
    fprintf(stderr, "Invalid semver string\n");
    return(-1);
  }

  int resolution = semver_compare(compare_version, current_version);

  if (resolution == 0)
    printf("Versions %s is equal to: %s\n", compare, current);
  else if (resolution == -1)
    printf("Version %s is lower than: %s\n", compare, current);
  else
    printf("Version %s is higher than: %s\n", compare, current);

  // Free allocated memory when we're done
  semver_free(&current_version);
  semver_free(&compare_version);
  PASS();
}

SUITE(s_semver_test) {
  RUN_TEST(t_semver_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_semver_test);
  GREATEST_MAIN_END();
}
