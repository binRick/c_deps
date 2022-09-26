
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "hashmap-test/hashmap-test.h"
#include "hashmap.h/hashmap.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

static int iterate(void * const context, void * const value) {
  // If the value is 42...
  if (42 == *(int *)value) {
    // Store into our user-provided context the value.
    *(void **)context = value;

    // Return 0 to tell the iteration to stop here.
    return(0);
  }

  // Otherwise tell the iteration to keep going.
  return(1);
}

TEST t_hashmap_test2(){
  PASS();
}

TEST t_hashmap_test1(){
  const unsigned   initial_size = 2;
  struct hashmap_s hashmap;

  if (0 != hashmap_create(initial_size, &hashmap)) {
    FAIL();
  }
  int  meaning_of_life = 42;
  char question        = 6 * 8;

  if (0 != hashmap_put(&hashmap, "life", strlen("life"), &meaning_of_life)) {
    FAIL();
  }

  if (0 != hashmap_put(&hashmap, "?", strlen("?"), &question)) {
    FAIL();
  }
  void * const element = hashmap_get(&hashmap, "life", strlen("life"));

  if (NULL == element) {
    FAIL();
  }

  int *value;

  if (0 != hashmap_iterate(&hashmap, iterate, &value)) {
    if (*value != 42) {
      FAIL();
    }
    log_info("value:%d", *value);
  } else {
  }
  unsigned num_entries = hashmap_num_entries(&hashmap);

  log_info("num entries:%d", num_entries);

  PASS();
}

SUITE(s_hashmap_test) {
  RUN_TEST(t_hashmap_test1);
  if (isatty(STDOUT_FILENO)) {
    RUN_TEST(t_hashmap_test2);
  }
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_hashmap_test);
  GREATEST_MAIN_END();
}
