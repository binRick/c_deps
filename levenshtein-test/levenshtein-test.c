////////////////////////////////////////////

////////////////////////////////////////////
#include "levenshtein-test/levenshtein-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "levenshtein/deps/levenshtein.c/levenshtein.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_levenshtein_test(){
  char *w1 = "aaaaaaaaaa";
  char *w2 = "aaaaaaaaaa";

  printf("%s:%s -> %zu\n", w1, w2, levenshtein(w1, w2));
  w1 = "bbbbbbbbb";
  w2 = "aaaaaaaaaa";
  printf("%s:%s -> %zu\n", w1, w2, levenshtein(w1, w2));
  PASS();
}

SUITE(s_levenshtein_test) {
  RUN_TEST(t_levenshtein_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_levenshtein_test);
  GREATEST_MAIN_END();
}
