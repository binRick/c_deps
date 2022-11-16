////////////////////////////////////////////
#include <iowow/iwkv.h>
#include <stdlib.h>
#include <string.h>

int test_iowow() {
  IWKV_OPTS opts = {
    .path   = ".iowow.db",
    .oflags = IWKV_TRUNC // Cleanup database before open
  };
  IWKV      iwkv;
  IWDB      mydb;
  iwrc      rc = iwkv_open(&opts, &iwkv);

  if (rc) {
    iwlog_ecode_error3(rc);
    return(1);
  }
  // Now open mydb
  // - Database id: 1
  rc = iwkv_db(iwkv, 1, 0, &mydb);
  if (rc) {
    iwlog_ecode_error2(rc, "Failed to open mydb");
    return(1);
  }
  // Work with db: put/get value
  IWKV_val key, val;

  key.data = "foo";
  key.size = strlen(key.data);
  val.data = "bar";
  val.size = strlen(val.data);

  fprintf(stdout, "put: %.*s => %.*s\n",
          (int)key.size, (char *)key.data,
          (int)val.size, (char *)val.data);

  rc = iwkv_put(mydb, &key, &val, 0);
  if (rc) {
    iwlog_ecode_error3(rc);
    return(rc);
  }
  // Retrieve value associated with `foo` key
  val.data = 0;
  val.size = 0;
  rc       = iwkv_get(mydb, &key, &val);
  if (rc) {
    iwlog_ecode_error3(rc);
    return(rc);
  }

  fprintf(stdout, "get: %.*s => %.*s\n",
          (int)key.size, (char *)key.data,
          (int)val.size, (char *)val.data);

  iwkv_val_dispose(&val);
  iwkv_close(&iwkv);
  return(0);
} /* test_iowow */

#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////
#include "iowow-test/iowow-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"

////////////////////////////////////////////
static char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };
static char *EXECUTABLE;
static char *EXECUTABLE_PATH_DIRNAME;
static bool DEBUG_MODE_ENABLED = false;
void __attribute__((constructor)) __constructor__iowow_test();
void __attribute__((destructor)) __destructor__iowow_test();
void __iowow_test__setup_executable_path(const char **argv);

TEST t_iowow_test(void *PARAMETER){
  test_iowow();
  PASS();
}

SUITE(s_iowow_test) {
  void *TEST_PARAM = 0;

  RUN_TESTp(t_iowow_test, (void *)TEST_PARAM);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  __iowow_test__setup_executable_path(argv);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
  }
  RUN_SUITE(s_iowow_test);
  GREATEST_MAIN_END();
}

void __iowow_test__setup_executable_path(const char **argv){
  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE              = basename(EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  if (DEBUG_MODE_ENABLED)
    fprintf(stderr, "iowow-test Initialized @ %s/%s\n", EXECUTABLE_PATH_DIRNAME, EXECUTABLE_PATH);
}

void __attribute__((constructor)) __constructor__iowow_test(){
  DEBUG_MODE_ENABLED = (getenv("DEBUG")) ? true
      : (getenv("DEBUG_MODE")) ? true
        : (getenv("DEBUGMODE")) ? true
          : false;
}

void __attribute__((destructor)) __destructor__iowow_test(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "\nChecking iowow-test memory leaks\n");
  print_allocated_memory();
#endif
}
