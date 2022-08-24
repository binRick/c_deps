////////////////////////////////////////////

#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////
#include "filecopy-test/filecopy-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "filecopy/filecopy.h"

////////////////////////////////////////////
static char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };
static char *EXECUTABLE;
static char *EXECUTABLE_PATH_DIRNAME;
static bool DEBUG_MODE_ENABLED = false;
void __attribute__((constructor)) __constructor__filecopy_test();
void __attribute__((destructor)) __destructor__filecopy_test();
void __filecopy_test__setup_executable_path(const char **argv);

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
  char            *src = "/etc/passwd";
  char            *dst = "/tmp/passwd";
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

TEST t_filecopy_test(void *PARAMETER){
  fc();
  PASS();
}

SUITE(s_filecopy_test) {
  void *TEST_PARAM = 0;

  RUN_TESTp(t_filecopy_test, (void *)TEST_PARAM);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  __filecopy_test__setup_executable_path(argv);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
  }
  RUN_SUITE(s_filecopy_test);
  GREATEST_MAIN_END();
}

void __filecopy_test__setup_executable_path(const char **argv){
  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE              = basename(EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  if (DEBUG_MODE_ENABLED) {
    fprintf(stderr, "filecopy-test Initialized @ %s/%s\n", EXECUTABLE_PATH_DIRNAME, EXECUTABLE_PATH);
  }
}

void __attribute__((constructor)) __constructor__filecopy_test(){
  DEBUG_MODE_ENABLED = (getenv("DEBUG")) ? true
      : (getenv("DEBUG_MODE")) ? true
        : (getenv("DEBUGMODE")) ? true
          : false;
}

void __attribute__((destructor)) __destructor__filecopy_test(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "\nChecking filecopy-test memory leaks\n");
  print_allocated_memory();
#endif
}
