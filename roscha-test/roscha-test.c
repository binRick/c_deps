////////////////////////////////////////////

#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////
#include "roscha-test/roscha-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
//#include "c_vector/include/vector.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
////////////////////////////////////////////
#include "roscha/include/hmap.h"
#include "roscha/include/object.h"
#include "roscha/include/parser.h"
#include "roscha/include/roscha.h"
#include "roscha/include/sds/sds.h"
#include "roscha/include/token.h"
#include "roscha/include/vector.h"
////////////////////////////////////////////
static char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };
static char *EXECUTABLE;
static char *EXECUTABLE_PATH_DIRNAME;
static bool DEBUG_MODE_ENABLED = false;
void __attribute__((constructor)) __constructor__roscha_test();
void __attribute__((destructor)) __destructor__roscha_test();
void __roscha_test__setup_executable_path(const char **argv);

char *input = "name={{name}}\n"
              "var1={{var1}}\n"
              "item.name={{item.name}}, item.age={{item.age}}\n"
              "items list=\n"
              "{\%for i in items\%}"
              " \t#{{loop.index}}> item={{i}}\n"
              "{\%endfor\%}\n"
              "items obj list=\n"
              ""
              "{\%for i in item_objects\%}"
              " \t#{{loop.index}}> name={{i.name}}\n"
              "{\%endfor\%}\n"
              "";

static void test_eval_variable(void){
  roscha_init();
  struct roscha_env *env = roscha_env_new();
  env->vars = roscha_object_new(hmap_new());

  roscha_hmap_set_new(env->vars, "name", "world");
  roscha_hmap_set_new(env->vars, "var1", 1);

  struct roscha_object *item = roscha_object_new(hmap_new());
  roscha_hmap_set_new(item, "name", "i");
  roscha_hmap_set_new(item, "age", 123);
  roscha_hmap_set(env->vars, "item", item);

  struct roscha_object *item_objects = roscha_object_new_vector(roscha_vector_new());

  struct roscha_object *i0 = roscha_object_new(hmap_new());
  roscha_hmap_set_new(i0, "name", "i0");
  roscha_vector_push(item_objects, i0);

  struct roscha_object *i1 = roscha_object_new(hmap_new());
  roscha_hmap_set_new(i1, "name", "i1");
  roscha_vector_push(item_objects, i1);

  roscha_hmap_set(env->vars, "item_objects", item_objects);

  struct roscha_object *items = roscha_object_new(roscha_vector_new());
  roscha_vector_push_new(items, (slice_whole("item0")));
  roscha_vector_push_new(items, (slice_whole("item1")));
  roscha_hmap_set(env->vars, "items", items);

  roscha_env_add_template(env, strdup("test"), input);

  sds got = roscha_env_render(env, "test");
  printf("==============================\n");
  printf("%s", input);
  printf("==============================\n");
  printf("%s", got);
  printf("==============================\n");
  roscha_deinit();
}

TEST t_roscha_test(void *PARAMETER){
  test_eval_variable();
  PASS();
}

SUITE(s_roscha_test) {
  void *TEST_PARAM = 0;

  RUN_TESTp(t_roscha_test, (void *)TEST_PARAM);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  __roscha_test__setup_executable_path(argv);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
  }
  RUN_SUITE(s_roscha_test);
  GREATEST_MAIN_END();
}

void __roscha_test__setup_executable_path(const char **argv){
  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE              = basename(EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  if (DEBUG_MODE_ENABLED) {
    fprintf(stderr, "roscha-test Initialized @ %s/%s\n", EXECUTABLE_PATH_DIRNAME, EXECUTABLE_PATH);
  }
}

void __attribute__((constructor)) __constructor__roscha_test(){
  DEBUG_MODE_ENABLED = (getenv("DEBUG")) ? true
      : (getenv("DEBUG_MODE")) ? true
        : (getenv("DEBUGMODE")) ? true
          : false;
}

void __attribute__((destructor)) __destructor__roscha_test(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "\nChecking roscha-test memory leaks\n");
  print_allocated_memory();
#endif
}
