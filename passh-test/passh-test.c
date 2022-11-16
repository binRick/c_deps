////////////////////////////////////////////
#ifndef PASSH_LIB
#define PASSH_LIB
#endif
#define DEBUG_MEMORY
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////
#include "passh-test/passh-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
////////////////////////////////////////////
#include "c_passh/passh.h"

////////////////////////////////////////////
static char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };
static char *EXECUTABLE;
static char *EXECUTABLE_PATH_DIRNAME;
static bool DEBUG_MODE_ENABLED = false;
void __attribute__((constructor)) __constructor__passh_test();
void __attribute__((destructor)) __destructor__passh_test();
void __passh_test__setup_executable_path(const char **argv);

struct passh_args_t {
  const int  argc;
  const char *argv[];
};

#define OUT_FILE    "/tmp/passh.log"
struct passh_args_t test_cfg = {
  .argc = 4,
  .argv = { "passh","-L",    OUT_FILE, "id", NULL },
};

TEST t_passh_test(){
  if (fsio_path_exists(OUT_FILE))
    fsio_remove(OUT_FILE);

  int  res = passh(test_cfg.argc, test_cfg.argv);
  ASSERT_EQ(res, 0);
  bool ok = fsio_path_exists(OUT_FILE);
  ASSERT_EQ(ok, true);
  char *dat = fsio_read_text_file(OUT_FILE);
  ASSERT_GTE(strlen(dat), 10);
  PASS();
}

SUITE(s_passh_test) {
  RUN_TEST(t_passh_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  __passh_test__setup_executable_path(argv);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
  }
  RUN_SUITE(s_passh_test);
  GREATEST_MAIN_END();
}

void __passh_test__setup_executable_path(const char **argv){
  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE              = basename(EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  if (DEBUG_MODE_ENABLED)
    fprintf(stderr, "passh-test Initialized @ %s/%s\n", EXECUTABLE_PATH_DIRNAME, EXECUTABLE_PATH);
}

void __attribute__((constructor)) __constructor__passh_test(){
  DEBUG_MODE_ENABLED = (getenv("DEBUG")) ? true
      : (getenv("DEBUG_MODE")) ? true
        : (getenv("DEBUGMODE")) ? true
          : false;
}

void __attribute__((destructor)) __destructor__passh_test(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "\nChecking passh-test memory leaks\n");
  print_allocated_memory();
#endif
}
