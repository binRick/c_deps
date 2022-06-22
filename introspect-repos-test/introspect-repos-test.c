#include <stdbool.h>
#define DEBUG_MEMORY_ENABLED    false
#include "introspect-repos-test.h"
#include "parson.h"
#include "submodules/log.h/log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#ifdef DEBUG_MEMORY_ENABLED
#include "submodules/debug-memory/debug_memory.h"
#endif
//////////////////////////////////////////////
#define NUM_CHILDREN        1
#define MAX_OUTPUT_BYTES    1024 * 1024
#define D                   log_debug
//////////////////////////////////////////////
extern char *execute_processes();

const size_t PATH_LIMIT = 20;

//////////////////////////////////////////////


void on_shared_library_target_json_value(void *arg) {
  JSON_Value  *V    = (JSON_Value *)arg;
  JSON_Object *O    = json_value_get_object(V);
  char        *name = json_object_get_string(O, "name");
  char        *type = json_object_get_string(O, "type");

  fprintf(stderr, "%s%s" AC_RESETALL ", ", AC_YELLOW, name);
}


void on_static_library_target_json_value(void *arg) {
  JSON_Value  *V    = (JSON_Value *)arg;
  JSON_Object *O    = json_value_get_object(V);
  char        *name = json_object_get_string(O, "name");
  char        *type = json_object_get_string(O, "type");

  fprintf(stderr, "%s%s" AC_RESETALL ", ", AC_BLUE, name);
}


void on_executable_target_json_value(void *arg) {
  JSON_Value  *V    = (JSON_Value *)arg;
  JSON_Object *O    = json_value_get_object(V);
  char        *name = json_object_get_string(O, "name");
  char        *type = json_object_get_string(O, "type");

  fprintf(stderr, "%s%s" AC_RESETALL ", ", AC_GREEN AC_UNDERLINE, name);
}


TEST t_introspect_iterate(void *MESON_FILE_PATH){
  char *OUTPUT = execute_processes((char *)MESON_FILE_PATH);

  ASSERT_GTE(strlen(OUTPUT), 1);

  JSON_Array *A = parse_execution_result(OUTPUT);

  ASSERT_NEQ(A, NULL);

  ee_t *ee = ee_new();

  ee_on(ee, "executable", on_executable_target_json_value);
  ee_on(ee, "shared library", on_shared_library_target_json_value);
  ee_on(ee, "static library", on_static_library_target_json_value);
  fprintf(stderr, "\n" AC_RESETALL AC_ITALIC AC_GREEN "%s" AC_RESETALL ">\t", (char *)MESON_FILE_PATH);

  iterate_targets(ee, A);

  free(OUTPUT);
  fprintf(stderr, "\n");
  PASS();
}


TEST t_paths(){
  char          *BASE_PATH   = "../";
  char          *PATH_FILTER = "c_*";
  struct Vector *MESON_PATHS = get_meson_paths(BASE_PATH, PATH_FILTER, PATH_LIMIT);

  iterate_print(MESON_PATHS);
  struct Vector *introspected_paths = execute_meson_introspects(MESON_PATHS);

  iterate_parse_results(introspected_paths);
  PASS();
}

SUITE(s_paths){
  RUN_TESTp(t_paths);
  PASS();
}


GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_paths);
#ifdef DEBUG_MEMORY_ENABLED
//  print_allocated_memory();
#endif
  GREATEST_MAIN_END();
  return(0);
}

