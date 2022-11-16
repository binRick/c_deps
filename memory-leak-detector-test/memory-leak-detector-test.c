
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "memory-leak-detector-test/memory-leak-detector-test.h"
#include "memory_leak_detector/leak.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

TEST t_memory_leak_detector_test2(){
  PASS();
}

TEST t_memory_leak_detector_test1(){
  char *a = malloc(100);

  free(a);

  char *b = malloc(120);
  // forget to free         //--> LEAK (120)

  char *c = calloc(10, 8);

  // refrence to memory lost
  c = malloc(10);             //--> LEAK (10 * 8)

  char *d = realloc(c, 15);   // Here memory will be free first

  free(d);
  PASS();
}

SUITE(s_memory_leak_detector_test) {
  RUN_TEST(t_memory_leak_detector_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_memory_leak_detector_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_memory_leak_detector_test);
  GREATEST_MAIN_END();
}
