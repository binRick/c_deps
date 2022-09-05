////////////////////////////////////////////

////////////////////////////////////////////
#include "c_greatest/greatest/greatest.h"
#include "log-test/log-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_log_test(){
  log_info("info");
  log_error("error");
  char *s = "str";
//  log_print(s);
  PASS();
}

SUITE(s_log_test) {
  RUN_TEST(t_log_test);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_log_test);
  GREATEST_MAIN_END();
}
