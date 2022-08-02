#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define DEBUG_MODE    true
//////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c-meson-utils-test/c-meson-utils-test.h"
#include "c-meson-utils/c-meson-utils.h"
#include "c_fsio/include/fsio.h"
#include "jinja2-cli/jinja2-cli.h"
#include "tempdir.c/tempdir.h"


char *RENDER_TEMPLATE_VARS(char *TEMPLATE_s, char *VARS_s, char *COLOR){
  struct jinja2_render_template_t *c = jinja2_init_config();

  c->template_s        = TEMPLATE_s;
  c->input_json_string = VARS_s;
  c->template_file     = NULL;
  c->output_file       = NULL;
  c->debug_mode        = DEBUG_MODE;
  assert(jinja2_render_template(c) == 0);
  assert(c->success == true);
  fprintf(stderr, AC_RESETALL "<%d>   \n%s%s\n" AC_RESETALL, getpid(), COLOR, c->output_s);
  return(c->output_s);
}

#define RENDER_TEST_CASE(TEST_CASE_NAME, TEST_CASE_TEMPLATE, TEST_CASE_VARS, COLOR) \
  TEST TEST_CASE_NAME(void){                                                        \
    RENDER_TEMPLATE_VARS(TEST_CASE_TEMPLATE, TEST_CASE_VARS, COLOR);                \
    PASS();                                                                         \
  }


RENDER_TEST_CASE(t_meson_jinja2_render_module_h, c_meson_module_h_template, "{\"MODULE_NAME\":\"world\"}", AC_BLUE);
RENDER_TEST_CASE(t_meson_jinja2_render_module_c, c_meson_module_c_template, "{\"MODULE_NAME\":\"world\"}", AC_RED);
RENDER_TEST_CASE(
  t_meson_jinja2_render_dep,
  c_meson_module_dep_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_CYAN
  );
RENDER_TEST_CASE(
  t_meson_jinja2_render_test_c,
  c_meson_module_test_c_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_BLUE
  );
RENDER_TEST_CASE(
  t_meson_jinja2_render_test_h,
  c_meson_module_test_h_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_BLUE
  );

RENDER_TEST_CASE(
  t_meson_jinja2_render_module_test_h,
  c_meson_module_test_h_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_BLUE
  );
RENDER_TEST_CASE(
  t_meson_jinja2_render_module_test_c,
  c_meson_module_test_c_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_BLUE
  );
RENDER_TEST_CASE(
  t_meson_jinja2_render_test_case,
  c_meson_module_test_case_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_RED
  );
RENDER_TEST_CASE(
  t_meson_jinja2_render_test_suite,
  c_meson_module_test_suite_template,
  "{\"MODULE_NAME\":\"world\"}",
  AC_YELLOW
  );


TEST t_meson_jinja2_render_basic(void){
  char *o = RENDER_TEMPLATE_VARS("hello {{abc}}", "{\"abc\":\"world\"}", AC_YELLOW);

  ASSERT_EQ(strcmp(o, "hello world"), 0);
  o = RENDER_TEMPLATE_VARS("hello {{name}}", "{\"name\":\"bob\"}", AC_GREEN);
  ASSERT_EQ(strcmp(o, "hello bob"), 0);
  PASS();
}

SUITE(s_c_meson_utils_jinja2_basic){
  RUN_TEST(t_meson_jinja2_render_basic);
}
SUITE(s_c_meson_utils_jinja2_module_test){
  RUN_TEST(t_meson_jinja2_render_module_test_c);
  RUN_TEST(t_meson_jinja2_render_module_test_h);
}
SUITE(s_c_meson_utils_jinja2_tests){
  RUN_TEST(t_meson_jinja2_render_test_suite);
  RUN_TEST(t_meson_jinja2_render_test_case);
}
SUITE(s_c_meson_utils_jinja2_module){
  RUN_TEST(t_meson_jinja2_render_module_c);
  RUN_TEST(t_meson_jinja2_render_module_h);
}
SUITE(s_c_meson_utils_jinja2_dep){
  RUN_TEST(t_meson_jinja2_render_dep);
}
SUITE(s_c_meson_utils_jinja2_test){
  RUN_TEST(t_meson_jinja2_render_test_h);
  RUN_TEST(t_meson_jinja2_render_test_c);
}


GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_c_meson_utils_jinja2_test);
  RUN_SUITE(s_c_meson_utils_jinja2_test);
  RUN_SUITE(s_c_meson_utils_jinja2_tests);
  RUN_SUITE(s_c_meson_utils_jinja2_module);
  RUN_SUITE(s_c_meson_utils_jinja2_module_test);
  RUN_SUITE(s_c_meson_utils_jinja2_dep);

  GREATEST_MAIN_END();
  return(0);
}

