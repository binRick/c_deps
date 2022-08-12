////////////////////////////////////////////
#define DEBUG_MEMORY
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
////////////////////////////////////////////
#include "blocks-test/blocks-test.h"
////////////////////////////////////////////
static char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };
static char *EXECUTABLE;
static char *EXECUTABLE_PATH_DIRNAME;
static bool DEBUG_MODE_ENABLED = false;
////////////////////////////////////////////
void __attribute__((constructor)) __constructor__blocks_test();
void __attribute__((destructor)) __destructor__blocks_test();
void __blocks_test__setup_executable_path(const char **argv);
////////////////////////////////////////////
#define RUN_TESTS() { do  { \
  RUN_TEST(t_blocks_test_basic);\
  RUN_TEST(t_blocks_test_args);\
  RUN_TEST(t_blocks_test_callback);\
  RUN_TEST(t_blocks_test_callback_creator);\
  RUN_TEST(t_blocks_test_callback_struct);\
  RUN_TEST(t_blocks_test_callback_struct_created);\
  RUN_TEST(t_blocks_test_op_type);\
  RUN_TEST(t_blocks_test_parser_ops);\
} while(0); }

//////////////////////////////////////////////////////////////////////////////////////////////////////
enum PARSER_TYPE_e {
  PARSER_TYPE_1,
  PARSER_TYPE_2,
 PARSER_TYPES_QTY,
};
struct PARSER_OP_s;
typedef int (^PARSER_OP_b)(int, int);
struct PARSER_OP_s {
  PARSER_OP_b op;
};
struct PARSER_OP_s parser_ops[] = {
  [PARSER_TYPE_1] = { 
    .op = ^int(int a, int b){ return(a + b); },
  },
  [PARSER_TYPE_2] = { 
    .op = ^int(int a, int b){ return(a - b); },
  },
  [PARSER_TYPES_QTY] = { 0 },
};

TEST t_blocks_test_parser_ops(void){
  int x = 10, y = 5;

  int sum = parser_ops[PARSER_TYPE_1].op(x,y);
  int diff = parser_ops[PARSER_TYPE_2].op(x,y);
  ASSERT_EQm("The sum should be 15", sum, 15);
  ASSERT_EQm("The difference should be 5", diff, 5);

  printf("\n\tThe sum is %d\n", sum);
  printf("\tThe diff is %d\n", diff);
  PASS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
enum OPTYPE {
  OPTYPE_ADD,
  OPTYPE_SUBTRACT,
  OPTYPES_QTY,
} OPTYPE;
struct CHANGEOP_t;
typedef int (^CHANGEOP_b)(int, int);
struct CHANGEOP_t {
  CHANGEOP_b op;
};
struct CHANGEOP_t ops[] = {
  [OPTYPE_ADD] = { 
    .op = ^int(int a, int b){ return(a + b); },
  },
  [OPTYPE_SUBTRACT] = { 
    .op = ^int(int a, int b){ return(a - b); },
  },
  [OPTYPES_QTY] = { 0 },
};

TEST t_blocks_test_op_type(void){
  int x = 10, y = 5;

  int sum = ops[OPTYPE_ADD].op(x,y);
  int diff = ops[OPTYPE_SUBTRACT].op(x,y);
  ASSERT_EQm("The sum should be 15", sum, 15);
  ASSERT_EQm("The difference should be 5", diff, 5);

  printf("\n\tThe sum is %d\n", sum);
  printf("\tThe diff is %d\n", diff);
  PASS();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (^void_cb_t)(void);
typedef int (^summer_t)(int, int);
struct callback_summer_s {
  summer_t cb; int y; int x;
};
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

TEST t_blocks_test_callback_struct_created(void){
  struct callback_summer_s callbacks[] = {
    { .cb = callback_creator(0, 0), .x = 200, .y = 1000, },
    { .cb = callback_creator(0, 0), .x = 20,  .y = 100,  },
    { 0 },
  };

  struct callback_summer_s *tmp = callbacks;

  for (size_t i = 0; tmp->cb != NULL; tmp++, i++) {
    summer_t created = ^ int (int a, int b){
      return(tmp->cb(tmp->x, tmp->y) + a + b);
    };
    printf("calling created callback #%lu\n", i);
    int val = created(5, 100);
    printf("      created val: %d\n", val);
  }

  PASS();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
struct callback_t {
  summer_t cb;
  int      x; int y;
};

TEST t_blocks_test_callback_struct(void){
  struct callback_t callbacks[] = {
    { .cb = callback_creator(0, 0), .x = 5, .y = 10, },
    { .cb = callback_creator(0, 0), .x = 5, .y = 10, },
    { .cb = callback_creator(0, 0), .x = 5, .y = 10, },
    { .cb = callback_creator(0, 0), .x = 5, .y = 10, },
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
TEST t_blocks_test_callback_creator(void){
  int      y = 2, z = 5;
  summer_t created = callback_creator(y, z);
  int      sum     = created(y, z);

  printf("sum is %d\n", sum);
  PASS();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
TEST t_blocks_test_basic(void){
  int  x = 10;

  void (^vv)(void) = ^ { printf("x is %d\n", x); };
  x = 11;
  vv();

  PASS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
SUITE(s_blocks_test) {
  void *TEST_PARAM = 0;
  RUN_TESTS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  __blocks_test__setup_executable_path(argv);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
  }
  RUN_SUITE(s_blocks_test);
  GREATEST_MAIN_END();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void __blocks_test__setup_executable_path(const char **argv){
  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE              = basename(EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  if (DEBUG_MODE_ENABLED) {
    fprintf(stderr, "blocks-test Initialized @ %s/%s\n", EXECUTABLE_PATH_DIRNAME, EXECUTABLE_PATH);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void __attribute__((constructor)) __constructor__blocks_test(){
  DEBUG_MODE_ENABLED = (getenv("DEBUG")) ? true
      : (getenv("DEBUG_MODE")) ? true
        : (getenv("DEBUGMODE")) ? true
          : false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void __attribute__((destructor)) __destructor__blocks_test(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "\nChecking blocks-test memory leaks\n");
  print_allocated_memory();
#endif
}
/*
 * https://stackoverflow.com/questions/1579494/is-this-the-right-way-for-a-block-inside-a-struct-to-access-a-member-variable-in
 * typedef enum
 * {
 * opTypeAdd = 0,
 * opTypeSubtract = 1,
 * opTypeTotal
 * } opType;
 *
 * struct someMathStruct; // Forward declare this as a type so we can use it in the
 *                     // changeBlock typedef
 *
 * typedef void (^changeBlock) (opType,struct someMathStruct*);
 * typedef void (^mathBlock) (int,int,int*);
 *
 * //hold two blocks, to be defined later at runtime
 * typedef struct someMathStruct{
 * mathBlock doMath;
 * changeBlock changeOperation;
 * } SomeMath;
 * int main()
 * {
 *
 *  //i want to declare an array of blocks of type mathBlock
 *  //the intent is to have the array index to correspond with the opTypes
 *  // enumerated above
 *  mathBlock *m = calloc(opTypeTotal, sizeof(mathBlock *));
 *
 *  //just two simple math operations as blocks
 *  m[opTypeAdd] = ^(int a,int b,int *result){*result = a+b;};
 *  m[opTypeSubtract] = ^(int a,int b,int *result){*result = a-b;};
 *
 *  changeBlock changeMe = ^(opType a, SomeMath *b) {
 *    //should make adding operations as easy as just adding cases
 *   switch (a)
 *   {
 *    case opTypeAdd: b->doMath = m[a]; break;
 *    case opTypeSubtract:
 *    default:  b->doMath = m[a];  //catch-all goes to subtracting
 *   }
 *  };
 *
 *  SomeMath mathFun;
 *  int theTotal = 0;  //a test int to work with
 *
 *  mathFun.changeOperation = changeMe;
 *
 *  mathFun.changeOperation(opTypeAdd, &mathFun);
 *  mathFun.doMath(theTotal,11,&theTotal); //result should be 11
 *
 *  mathFun.changeOperation(opTypeSubtract, &mathFun);
 *  mathFun.doMath(theTotal,3,&theTotal); //result should be 8
 *
 *  NSLog(@"the result: %d",theTotal); //should output "the result: 8"
 * }
 *
 */
/*
 * https://stackoverflow.com/questions/43133611/how-to-save-obj-c-block-in-a-c-struct
 * typedef struct {
 * char *json;
 * __unsafe_unretained NSString *name;
 * __unsafe_unretained CompletionBlock block;
 * } SampleStruct;
 */
/*
 * https://stackoverflow.com/questions/27162567/syntax-to-define-a-block-that-takes-a-block-and-returns-a-block-in-objective-c
 * //setup
 * typedef void (^ReturnedBlock)(void);
 * ReturnedBlock retBlock = ^void(void){};
 *
 * typedef void (^ParamBlock)(void);
 * ParamBlock paramBlock = ^void(void){};
 *
 * //the thing you want to do
 * ReturnedBlock (^someBlock)(ParamBlock) = ^ReturnedBlock(ParamBlock param){
 *
 *  return retBlock;
 * };
 *
 * //perform the block
 * ReturnedBlock r = someBlock(paramBlock);
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////
