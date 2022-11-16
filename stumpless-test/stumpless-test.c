#define STUMPLESS_ENABLE_UPTO_TRACE

#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "stumpless-test/stumpless-test.h"
#include "stumpless/include/stumpless.h"
#include "timestamp/timestamp.h"

TEST t_stumpless_test2(){
  PASS();
}

TEST t_stumpless_test1(){
  int  count    = 123;
  char username = "richard";

  stumplog(LOG_INFO | LOG_USER, "My message #%d", count);
  /*
     stump( "My message #%d", count );
     stump( "Login attempt failure #%d for user %s", count, username );
     stump_str( "Login failure! See structured data for info." );
     struct stumpless_target *target = stumpless_open_file_target( "example.log" );
     //  log_result = stumpless_add_entry( target, entry );

     stump( "Login attempt failure #%d for user %s", count, username );
     stump_i( "this gets logged as an info message" );
     stump_t( "this is easy to trace to the source" );
   */

  PASS();
}

SUITE(s_stumpless_test) {
  RUN_TEST(t_stumpless_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_stumpless_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  int  count    = 123;
  char username = "richard";

  stumplog(LOG_INFO | LOG_USER, "My message #%d", count);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_stumpless_test);
  GREATEST_MAIN_END();
}
