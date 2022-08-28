////////////////////////////////////////////
#include "filecopy-test/filecopy-test.h"
////////////////////////////////////////////
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "filecopy/filecopy.h"

////////////////////////////////////////////

static void print_progress(uint_least8_t percentage){
  printf("%03u%%\r", percentage);
  fflush(stdout);
}

typedef struct { long double nunits; char suffix; } bytes_fmt_result;

static inline bytes_fmt_result bytes_fmt(uintmax_t bytes){
  static const char suffix[] = { 'K', 'M', 'G', 'T' };
  bytes_fmt_result  res      = { bytes, 'B' };

  for (
    uint_least8_t i = 0;
    i < sizeof(suffix) && res.nunits / 1024 >= 1;
    res.nunits /= 1024, res.suffix = suffix[i++]
    ) {
  }
  return(res);
}

int fc(){
  fsio_write_text_file("/tmp/t1", "xxxxxxxxxxxxxxxx");
  char            *src = "/tmp/t1";
  char            *dst = "/tmp/t2";
  filecopy_result res  = filecopy(dst, src, 1024, print_progress);

  switch (res.err) {
  case filecopy_error_none: {
    bytes_fmt_result bfmt = bytes_fmt(res.bytes_copied);
    fprintf(
      stderr, "%.2Lf%c (%ju bytes) copied.\n",
      bfmt.nunits, bfmt.suffix, res.bytes_copied
      ); return(EXIT_SUCCESS);
  }
  case filecopy_error_src:
    fprintf(
      stderr, "Error : Unknown fatal error reading \"%s\" %s%s\n",
      src, errno? " : " : ".",
      errno? strerror(errno) : ""
      ); return(EXIT_FAILURE);

  case filecopy_error_dst:
    fprintf(
      stderr, "Error : Unknown fatal error writing to \"%s\" %s%s\n",
      dst? dst : "stdout", errno? " : " : ".",
      errno? strerror(errno) : ""
      ); return(EXIT_FAILURE);
  }
}

TEST t_filecopy_test(void){
//#fc();
  PASS();
}

SUITE(s_filecopy_test) {
  RUN_TEST(t_filecopy_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_filecopy_test);
  GREATEST_MAIN_END();
}
