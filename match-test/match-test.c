
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "match-test/match-test.h"
#include "match/match.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
TEST t_match_test2(){
  int png_files_qty=0,qoir_files_qty=0;
  char *path="/tmp/png";
  char **qoir_files = __MATCH__GET_FILES_FROM_PATH(path,"*.qoir",&qoir_files_qty);
  char **png_files = __MATCH__GET_FILES_FROM_PATH(path,"*.png",&png_files_qty);
  Dbg(png_files_qty,%d);
  Dbg(qoir_files_qty,%d);
  for(int i=0;i<png_files_qty;i++)
    Ds(png_files[i]);
  PASS();
}

TEST t_match_test1(){
  PASS();
}

SUITE(s_match_test) {
  RUN_TEST(t_match_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_match_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_match_test);
  GREATEST_MAIN_END();
}
