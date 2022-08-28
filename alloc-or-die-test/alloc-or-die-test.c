////////////////////////////////////////////

////////////////////////////////////////////
#include "alloc-or-die-test/alloc-or-die-test.h"
////////////////////////////////////////////
#include "alloc_or_die/alloc_or_die.h"
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"

////////////////////////////////////////////
TEST t_alloc_or_die_test_bad(){
  char *name;

  name = strdup_or_die("world");

  char *message;

  asprintf_or_die(&message, "Goodbye %s!", name);

  printf("%s\n", message);
  free_or_die(message);

  PASS();
}

TEST t_alloc_or_die_test_good(){
  char *name;

  name = strdup_or_die("world");

  char *message;

  asprintf_or_die(&message, "Hello %s!", name);
  free_or_die(name);

  printf("%s\n", message);
  free_or_die(message);

  alloc_count_is_zero_or_die();

  PASS();
}

SUITE(s_alloc_or_die_test) {
  RUN_TEST(t_alloc_or_die_test_good);
  RUN_TEST(t_alloc_or_die_test_bad);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_alloc_or_die_test);
  GREATEST_MAIN_END();
}
