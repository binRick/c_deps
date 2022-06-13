#include "introspect-test.h"
#include "submodules/log.h/log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#define NUM_CHILDREN        1
#define MAX_OUTPUT_BYTES    1024 * 1024
//////////////////////////////////////////////
extern int execute_processes();

//////////////////////////////////////////////

TEST t_introspect_ansi(void){
  char meson_build_file[] = "../c_ansi/meson.build";
  execute_processes(meson_build_file);
  PASS();
}

TEST t_introspect_db(void){
  char meson_build_file[] = "../c_db/meson.build";
  execute_processes(meson_build_file);
  PASS();
}

TEST t_introspect_palettes(void){
  char meson_build_file[] = "./../c_palettes/meson.build";
  execute_processes(meson_build_file);
  PASS();
}

TEST t_introspect_meson_deps(void){
  char meson_build_file[] = "./meson.build";
  execute_processes(meson_build_file);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_TEST(t_introspect_meson_deps);
  RUN_TEST(t_introspect_ansi);
  RUN_TEST(t_introspect_db);
  RUN_TEST(t_introspect_palettes);

  GREATEST_MAIN_END();
  return(0);
}

