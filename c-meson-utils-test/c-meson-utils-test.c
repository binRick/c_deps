#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#define DEBUG_MODE    false
//////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c-meson-utils-test/c-meson-utils-test.h"
#include "c-meson-utils/c-meson-utils.h"
#include "c_fsio/include/fsio.h"
#include "tempdir.c/tempdir.h"

//////////////////////////////////////////////
#define RENDER_TEST_CASE(TEST_CASE_NAME, TEST_CASE_TEMPLATE, TEST_CASE_VARS, COLOR) \
  TEST TEST_CASE_NAME(void){                                                        \
    RENDER_TEMPLATE_VARS(TEST_CASE_TEMPLATE, TEST_CASE_VARS, COLOR);                \
    PASS();                                                                         \
  }
//////////////////////////////////////////////
#define COLOR_EXECUTABLE                            AC_RED
#define ENCODED_VARS_EXECUTABLE_MESON_BUILD         "{\"MODULE_NAME\":\"world\"}"
#define ENCODED_VARS_EXECUTABLE_C                   "{\"MODULE_NAME\":\"world\"}"
#define ENCODED_VARS_EXECUTABLE_H                   "{\"MODULE_NAME\":\"world\"}"
//////////////////////////////////////////////
#define COLOR_LIBRARY                               AC_GREEN
#define ENCODED_VARS_LIBRARY_MESON_BUILD            "{\"MODULE_NAME\":\"world\"}"
#define ENCODED_VARS_LIBRARY_C                      "{\"MODULE_NAME\":\"world\"}"
#define ENCODED_VARS_LIBRARY_H                      "{\"MODULE_NAME\":\"world\"}"
//////////////////////////////////////////////
#define COLOR_TEST_EXECUTABLE                       AC_MAGENTA
#define ENCODED_VARS_TEST_EXECUTABLE_MESON_BUILD    "{\"MODULE_NAME\":\"world\"}"
#define ENCODED_VARS_TEST_EXECUTABLE_C              "{\"MODULE_NAME\":\"world\"}"
#define ENCODED_VARS_TEST_EXECUTABLE_H              "{\"MODULE_NAME\":\"world\"}"
//////////////////////////////////////////////
#define COLOR_TEST_BASH_SCRIPT                      AC_BLUE
#define ENCODED_VARS_BASH_SCRIPT                    "{\"x\":123}"
//////////////////////////////////////////////
#define COLOR_TEST_INCBIN_PYTHON_BINARIES           AC_YELLOW
#define ENCODED_VARS_TEST_INCBIN_PYTHON_BINARIES       \
  "{\"binaries\":["                                    \
  "{\"name\":\"meson\",\"dir\":\"submodules/c_ansi\"}" \
  ",{\"name\":\"\",\"dir\":\"submodules/c_ansi\"}"     \
  "],\"inc_embedded_python_binaries_struct\":\"struct python_binary_t { char *name, char *dir, };\"}"

//////////////////////////////////////////////

//////////////////////////////////////////////
RENDER_TEST_CASE(
  t_meson_utils_render_bash_script,
  c_meson_bash_script_template,
  ENCODED_VARS_BASH_SCRIPT,
  COLOR_TEST_BASH_SCRIPT);
RENDER_TEST_CASE(
  t_meson_utils_render_incbin_python_binaries,
  c_meson_embedded_incbin_python_binaries,
  ENCODED_VARS_TEST_INCBIN_PYTHON_BINARIES,
  COLOR_TEST_INCBIN_PYTHON_BINARIES);
RENDER_TEST_CASE(
  t_meson_utils_render_test_executable_meson_build,
  c_meson_jinja2_template_test_executable_meson_build,
  ENCODED_VARS_TEST_EXECUTABLE_MESON_BUILD,
  COLOR_TEST_EXECUTABLE);
RENDER_TEST_CASE(
  t_meson_utils_render_test_executable_c,
  c_meson_jinja2_template_test_executable_c,
  ENCODED_VARS_TEST_EXECUTABLE_C,
  COLOR_TEST_EXECUTABLE);
RENDER_TEST_CASE(
  t_meson_utils_render_test_executable_h,
  c_meson_jinja2_template_test_executable_h,
  ENCODED_VARS_TEST_EXECUTABLE_H,
  COLOR_TEST_EXECUTABLE);
//////////////////////////////////////////////
RENDER_TEST_CASE(
  t_meson_utils_render_executable_meson_build,
  c_meson_jinja2_template_executable_meson_build,
  ENCODED_VARS_EXECUTABLE_MESON_BUILD,
  COLOR_EXECUTABLE);
RENDER_TEST_CASE(
  t_meson_utils_render_executable_c,
  c_meson_jinja2_template_executable_c,
  ENCODED_VARS_EXECUTABLE_C,
  COLOR_EXECUTABLE);
RENDER_TEST_CASE(
  t_meson_utils_render_executable_h,
  c_meson_jinja2_template_executable_h,
  ENCODED_VARS_EXECUTABLE_H,
  COLOR_EXECUTABLE);
//////////////////////////////////////////////
RENDER_TEST_CASE(
  t_meson_utils_render_library_meson_build,
  c_meson_jinja2_template_library_meson_build,
  ENCODED_VARS_LIBRARY_MESON_BUILD,
  COLOR_LIBRARY);
RENDER_TEST_CASE(
  t_meson_utils_render_library_c,
  c_meson_jinja2_template_library_c,
  ENCODED_VARS_LIBRARY_C,
  COLOR_LIBRARY);
RENDER_TEST_CASE(
  t_meson_utils_render_library_h,
  c_meson_jinja2_template_library_h,
  ENCODED_VARS_LIBRARY_H,
  COLOR_LIBRARY);
//////////////////////////////////////////////
SUITE(s_c_meson_utils_render_library){
  RUN_TEST(t_meson_utils_render_library_h);
  RUN_TEST(t_meson_utils_render_library_c);
  RUN_TEST(t_meson_utils_render_library_meson_build);
}
//////////////////////////////////////////////
SUITE(s_c_meson_utils_render_executable){
  RUN_TEST(t_meson_utils_render_executable_h);
  RUN_TEST(t_meson_utils_render_executable_c);
  RUN_TEST(t_meson_utils_render_executable_meson_build);
}
//////////////////////////////////////////////
SUITE(s_meson_utils_render_incbin_python_binaries){
  RUN_TEST(t_meson_utils_render_incbin_python_binaries);
}
//////////////////////////////////////////////
SUITE(s_meson_utils_render_bash_script){
  RUN_TEST(t_meson_utils_render_bash_script);
}
//////////////////////////////////////////////
SUITE(s_c_meson_utils_render_test_executable){
  RUN_TEST(t_meson_utils_render_test_executable_h);
  RUN_TEST(t_meson_utils_render_test_executable_c);
  RUN_TEST(t_meson_utils_render_test_executable_meson_build);
}
//////////////////////////////////////////////

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_c_meson_utils_render_library);
  RUN_SUITE(s_c_meson_utils_render_executable);
  RUN_SUITE(s_c_meson_utils_render_test_executable);
  RUN_SUITE(s_meson_utils_render_incbin_python_binaries);
  RUN_SUITE(s_meson_utils_render_bash_script);

  GREATEST_MAIN_END();
  return(0);
}
