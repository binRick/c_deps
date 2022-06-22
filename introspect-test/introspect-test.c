#include <stdbool.h>
#define DEBUG_MEMORY_ENABLED    true
#include "introspect-test.h"
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

  //ASSERT_GTE(strlen(OUTPUT), 1);
  if (strlen(OUTPUT) > 0) {
    JSON_Array *A = parse_execution_result(OUTPUT);
    //     ASSERT_NEQ(A, NULL);
    if (A != NULL) {
      ee_t *ee = ee_new();
      ee_on(ee, "executable", on_executable_target_json_value);
      ee_on(ee, "shared library", on_shared_library_target_json_value);
      ee_on(ee, "static library", on_static_library_target_json_value);
      fprintf(stderr, "\n" AC_RESETALL AC_BOLD AC_RED_BLACK "%s" AC_RESETALL ">\t", (char *)MESON_FILE_PATH);
      iterate_targets(ee, A);
      fprintf(stderr, "\n");
    }
  }
  free(OUTPUT);
  PASS();
}


TEST t_introspect_parse_execution(void *MESON_FILE_PATH){
  char *OUTPUT = execute_processes((char *)MESON_FILE_PATH);

  //ASSERT_GTE(strlen(OUTPUT), 1);
  if (strlen(OUTPUT) > 0) {
    JSON_Array *A = parse_execution_result(OUTPUT);
    ASSERT_NEQ(A, NULL);
  }
  free(OUTPUT);
  PASS();
}


TEST t_introspect_ansi(void){
  char meson_build_file[] = "../c_ansi/meson.build";

  char *OUTPUT = execute_processes(meson_build_file);

  free(OUTPUT);
  PASS();
}


TEST t_introspect_db(void){
  char meson_build_file[] = "../c_db/meson.build";

  char *OUTPUT = execute_processes(meson_build_file);

  free(OUTPUT);
  PASS();
}


TEST t_introspect_palettes(void){
  char meson_build_file[] = "./../c_palettes/meson.build";

  char *OUTPUT = execute_processes(meson_build_file);

  free(OUTPUT);
  PASS();
}


TEST t_introspect_meson_deps(void){
  char meson_build_file[] = "./meson.build";

  char *OUTPUT = execute_processes(meson_build_file);

  free(OUTPUT);
  PASS();
}

SUITE(s_introspect_base){
  RUN_TEST(t_introspect_meson_deps);
  RUN_TEST(t_introspect_ansi);
  RUN_TEST(t_introspect_db);
  RUN_TEST(t_introspect_palettes);
  RUN_TESTp(t_introspect_parse_execution, "../c_colors/meson.build");
}

SUITE(s_iterate){
  RUN_TESTp(t_introspect_iterate, "../c_colors/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_ansi/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_db/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_colors/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_palettes/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_kat/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_embed/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_mui/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_sdl/meson.build");
  RUN_TESTp(t_introspect_iterate, "../c_hl/meson.build");
//  RUN_TESTp(t_introspect_iterate, "../meson_deps/meson.build");
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_introspect_base);
  RUN_SUITE(s_iterate);
#ifdef DEBUG_MEMORY_ENABLED
  print_allocated_memory();
#endif
  GREATEST_MAIN_END();
  return(0);
}

