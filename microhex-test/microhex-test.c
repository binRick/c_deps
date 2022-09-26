
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "microhex-test/microhex-test.h"
#include "microhex/microhex.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

TEST t_microhex_test2(){
  unsigned char *p = fsio_read_binary_file("/tmp/a.png");

  uhex_print_dump(p, fsio_file_size("/tmp/a.png"), 10);
  PASS();
}

TEST t_microhex_test1(){
  unsigned char *p = fsio_read_binary_file("/tmp/a.png");

  uhex_print_raw(p, fsio_file_size("/tmp/a.png"));
  PASS();
}

SUITE(s_microhex_test) {
  RUN_TEST(t_microhex_test1);
  RUN_TEST(t_microhex_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_microhex_test);
  GREATEST_MAIN_END();
}
