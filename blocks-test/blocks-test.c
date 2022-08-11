////////////////////////////////////////////
#define DEBUG_MEMORY
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////
#include "blocks-test/blocks-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"

////////////////////////////////////////////
static char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };
static char *EXECUTABLE;
static char *EXECUTABLE_PATH_DIRNAME;
static bool DEBUG_MODE_ENABLED = false;
void __attribute__((constructor)) __constructor__blocks_test();

void __attribute__((destructor)) __destructor__blocks_test();
void __blocks_test__setup_executable_path(const char **argv);

typedef int (^summer_t)(int, int);
typedef int (^cb_int_t)(int, int);
typedef void (^void_cb_t)(void);
typedef summer_t (^summer_creator_t)(summer_t cb, int, int);


int callback(summer_t cb, int a, int b) {
  return(cb(a, b));
}


summer_t callback_creator(int a, int b) {
  summer_t summer = ^ int (int a, int b){
    return(a + b);
  };

  return(summer);
}

struct callback_summer_s {
  summer_t cb; int y; int x;
};


TEST t_blocks_test_callback_struct1(void){
  struct callback_summer_s callbacks[] = {
    {
      .cb = callback_creator(0, 0),
      .x  = 200, .y = 100,
    },
    { .cb = callback_creator(0, 0), .x = 20, .y = 100, },
    { 0 },
  };

  struct callback_summer_s *tmp = callbacks;

  for (size_t i = 0; tmp->cb != NULL; tmp++, i++) {
    printf("calling callback #%lu\n", i);
    int val = tmp->cb(tmp->x, tmp->y);
    printf("      callback val: %d\n", val);
  }

  PASS();
}

struct callback_t {
  cb_int_t cb;
  int      x; int y;
};


TEST t_blocks_test_callback_struct(void){
  struct callback_t callbacks[] = {
    { .cb = callback_creator(0, 0),
      .x  = 5, .y = 10, },
    { .cb = callback_creator(0, 0),
      .x  = 50, .y = 100, },
    { .cb = callback_creator(0, 0),
      .x  = 50, .y = 100, },
    { 0 },
  };

  struct callback_t *tmp = callbacks;

  for (size_t i = 0; tmp->cb != NULL; tmp++, i++) {
    printf("calling callback #%lu\n", i);
    int val = tmp->cb(tmp->x, tmp->y);
    printf("      callback val: %d\n", val);
  }

  PASS();
}


TEST t_blocks_test_callback_creator(void){
  int      y = 2, z = 5;
  summer_t created = callback_creator(y, z);
  int      sum     = created(y, z);

  printf("sum is %d\n", sum);
  PASS();
}


TEST t_blocks_test_callback(void){
  int x = 1000;

  int (^summer)(int, int) = ^ int (int a, int b){
    return(a + b + x);
  };

  int y = 25, z = 50;
  int sum = callback(summer, y, z);


  printf("sum of x, y is %d\n", sum);

  PASS();
}


TEST t_blocks_test_args(void){
  typedef int (^summer_b)(int, int);
  int      x = 1000;

  summer_b summer = ^ int (int a, int b){
    return(a + b + x);
  };

  int y = 25, z = 50;
  int sum = summer(y, z);
  printf("sum of x, y, and z is %d\n", sum);

  PASS();
}


TEST t_blocks_test_basic(void){
  int  x = 10;

  void (^vv)(void) = ^ { printf("x is %d\n", x); };
  x = 11;
  vv();

  PASS();
}
SUITE(s_blocks_test) {
  void *TEST_PARAM = 0;

  RUN_TEST(t_blocks_test_basic);
  RUN_TEST(t_blocks_test_args);
  RUN_TEST(t_blocks_test_callback);
  RUN_TEST(t_blocks_test_callback_creator);
  RUN_TEST(t_blocks_test_callback_struct);
  RUN_TEST(t_blocks_test_callback_struct1);
}

GREATEST_MAIN_DEFS();


int main(const int argc, const char **argv) {
  __blocks_test__setup_executable_path(argv);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
  }
  RUN_SUITE(s_blocks_test);
  GREATEST_MAIN_END();
}


void __blocks_test__setup_executable_path(const char **argv){
  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE              = basename(EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  if (DEBUG_MODE_ENABLED) {
    fprintf(stderr, "blocks-test Initialized @ %s/%s\n", EXECUTABLE_PATH_DIRNAME, EXECUTABLE_PATH);
  }
}

void __attribute__((constructor)) __constructor__blocks_test(){
  DEBUG_MODE_ENABLED = (getenv("DEBUG")) ? true
      : (getenv("DEBUG_MODE")) ? true
        : (getenv("DEBUGMODE")) ? true
          : false;
}

void __attribute__((destructor)) __destructor__blocks_test(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "\nChecking blocks-test memory leaks\n");
  print_allocated_memory();
#endif
}
