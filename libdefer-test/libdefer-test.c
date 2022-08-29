////////////////////////////////////////////

////////////////////////////////////////////
#include "libdefer-test/libdefer-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libdefer/include/defer.h"
#include "log.h/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
DEFER_SCOPED(int64_t, copy_file_deferred, (const char *, dst_name, const char *, src_name)) {
  FILE *dst = fopen(dst_name, "w");

  if (!dst) {
    return(-1);
  }
  defer(fclose, dst);
  FILE *src = fopen(src_name, "r");

  if (!src) {
    return(-1);
  }
  defer(fclose, src);

  return(0);
}

int copy_file(const char *dst_name, const char *src_name) {
  FILE *dst = fopen(dst_name, "w");

  if (!dst) {
    return(-1);
  }
  FILE *src = fopen(src_name, "r");

  if (!src) {
    fclose(dst);     // cleanup #1
    return(-1);
  }

  // cleanup #2
  fclose(dst);
  fclose(src);
  return(0);
}

TEST t_libdefer_test(){
  copy_file("/tmp/passwd0", "/etc/passwd");
  copy_file_deferred("/tmp/passwd1", "/etc/passwd");

  PASS();
}

SUITE(s_libdefer_test) {
  RUN_TEST(t_libdefer_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_libdefer_test);
  GREATEST_MAIN_END();
}
