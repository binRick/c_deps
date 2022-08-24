#include <stdbool.h>
#define DEBUG_MEMORY_ENABLED
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
extern char *execute_processes();

const size_t  MESON_PROJECTS_LIMIT = 100;
struct Vector *MESON_PATHS;
struct Vector *INTROSPECTED_PATHS;
const char    *BASE_PATH   = "../",
              *PATH_FILTER = "^c_\\w+$|^c_deps$";

//////////////////////////////////////////////
void on_shared_library_target_json_value(void *arg) {
  JSON_Value  *V    = (JSON_Value *)arg;
  JSON_Object *O    = json_value_get_object(V);
  char        *name = json_object_get_string(O, "name");
  char        *type = json_object_get_string(O, "type");

  printf("%s/%s\n", name, type);
}

void on_static_library_target_json_value(void *arg) {
  JSON_Value  *V    = (JSON_Value *)arg;
  JSON_Object *O    = json_value_get_object(V);
  char        *name = json_object_get_string(O, "name");
  char        *type = json_object_get_string(O, "type");

  printf("%s/%s\n", name, type);
}

void on_executable_target_json_value(void *arg) {
  JSON_Value  *V    = (JSON_Value *)arg;
  JSON_Object *O    = json_value_get_object(V);
  char        *name = json_object_get_string(O, "name");
  char        *type = json_object_get_string(O, "type");

  printf("%s/%s\n", name, type);
}

__attribute__((unused)) TEST t_introspect_iterate(void *MESON_FILE_PATH){
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

TEST t_parse_results(){
  iterate_parse_results(INTROSPECTED_PATHS);
  ASSERT_GTE(vector_size(INTROSPECTED_PATHS), 0);
  PASS();
}

TEST t_introspect_paths(){
  INTROSPECTED_PATHS = execute_meson_introspects(MESON_PATHS);
  PASS();
}

TEST t_get_paths(){
  MESON_PATHS = get_meson_paths(BASE_PATH, PATH_FILTER, MESON_PROJECTS_LIMIT);
  ASSERT_GTE(vector_size(MESON_PATHS), 0);
  //dbg(vector_size(MESON_PATHS), %lu);
  for (size_t i = 0; i < vector_size(MESON_PATHS); i++) {
    //dbg((char *)vector_get(MESON_PATHS, i), %s);
  }
  PASS();
}

SUITE(s_free_vectors){
  if (MESON_PATHS) {
    vector_release(MESON_PATHS);
  }
  if (INTROSPECTED_PATHS) {
    iterate_free(INTROSPECTED_PATHS);
  }
}

SUITE(s_paths){
  RUN_TEST(t_get_paths);
  RUN_TEST(t_introspect_paths);
  RUN_TEST(t_parse_results);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_paths);
#ifdef DEBUG_MEMORY_ENABLED
  print_allocated_memory();
#endif
  GREATEST_MAIN_END();
}
