////////////////////////////////////////////

////////////////////////////////////////////
#include "tiny-regex-test/tiny-regex-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
#include "tiny-regex-c/re.h"

////////////////////////////////////////////
TEST t_tiny_regex_test(){
  int        match_length;
  const char *string_to_search = "ahem.. 'hello world !' ..";
  re_t       pattern           = re_compile("[Hh]ello [Ww]orld\\s*[!]?");
  int        match_idx         = re_matchp(pattern, string_to_search, &match_length);

  ASSERT_GTE(match_idx, 0);
  if (match_idx >= 0)
    printf("match at idx %i, %i chars long.\n", match_idx, match_length);
  PASS();
}

SUITE(s_tiny_regex_test) {
  RUN_TEST(t_tiny_regex_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_tiny_regex_test);
  GREATEST_MAIN_END();
}
