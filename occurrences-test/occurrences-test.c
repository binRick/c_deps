////////////////////////////////////////////
#define GREATEST_USE_LONGJMP    0
////////////////////////////////////////////
#include "occurrences-test/occurrences-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "occurences.c/occurrences.h"
#include "timestamp/timestamp.h"

struct occurrences_test_t {
  char *string;
  char *search;
  int  qty;
};

static struct occurrences_test_t *occurrences_tests[] = {
  &(struct occurrences_test_t){ .string = "hello", .search = "l",     .qty = 2  },
  &(struct occurrences_test_t){ .string = "hello", .search = "L",     .qty = 0  },
  &(struct occurrences_test_t){ .string = "hello", .search = NULL,    .qty = -1 },
  &(struct occurrences_test_t){ .string = NULL,    .search = "hello", .qty = -1 },
};

////////////////////////////////////////////
TEST t_occurrences_test(){
  char   *msg, *okmsg;
  size_t occurrences_tests_qty = sizeof(occurrences_tests) / sizeof(occurrences_tests[0]);

  log_info("Testing %lu cases", occurrences_tests_qty);
  int                       qty;
  struct occurrences_test_t *tmp;

  for (size_t i = 0; i < occurrences_tests_qty; i++) {
    tmp = occurrences_tests[i];
    log_debug("\tTesting case #%lu :: %s %s => %d", i, tmp->string, tmp->search, tmp->qty);
    qty = occurrences(tmp->search, tmp->string);
    asprintf(&okmsg, "Found %d occurrences of %s in %s", qty, tmp->search, tmp->string);
    asprintf(&msg, "Expected quantity to be %d but it is %d", tmp->qty, qty);
    ASSERT_EQ_FMTm(msg, tmp->qty, qty, "%d");
    log_info("\t%s", okmsg);
  }
  asprintf(&msg, "Tested %lu Occurences", occurrences_tests_qty);
  PASSm(msg);
}

SUITE(s_occurrences_test) {
  RUN_TEST(t_occurrences_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_occurrences_test);
  GREATEST_MAIN_END();
}
