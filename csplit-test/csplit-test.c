////////////////////////////////////////////

////////////////////////////////////////////
#include "csplit-test/csplit-test.h"
////////////////////////////////////////////
#include "c_greatest/greatest/greatest.h"
#include "submodules/csplit/csplit.h"

////////////////////////////////////////////
TEST t_csplit_test(){
  // our test string
  char *test_string = "Hello how are you doing?";

  printf("Our demo string is: %s\n", test_string);

  // initialize our output list.
  CSplitList_t *list = csplit_init_list();

  // split on the " " (space) character
  CSplitError_t err = csplit(list, test_string, " ");

  // print the list of split fragments to stdout
  csplit_print_list_info(list, stdout);

  // print a separator
  printf("----------------------------\n");

  // demo of getting fragment string at an index, 3 index will give us "you"
  char *test_get_index = get_fragment_at_index(list, 3);

  // demo of getting fragment string using reverse index, -1 will give us the last
  // fragment, in this case "doing?"
  char *test_get_r_index = get_fragment_at_index(list, -1);

  // print results
  printf("Get index: %s\n", test_get_index);
  printf("Get reverse index: %s\n", test_get_r_index);

  // free memory
  csplit_clear_list(list);
  PASS();
}

SUITE(s_csplit_test) {
  RUN_TEST(t_csplit_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_csplit_test);
  GREATEST_MAIN_END();
}
