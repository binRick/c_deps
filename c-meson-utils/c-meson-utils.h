#pragma once
/////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/////////////////////////////////////
#include "c_vector/include/vector.h"
#include "c_stringfn/include/stringfn.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_fsio/include/fsio.h"
#include "c_unja/src/unja_template.h"
/////////////////////////////////////
struct c_meson_module_dep_t {        //    meson/deps/xxxxx/meson.build
    char *dep_name;
    char *rendered_template_meson_build;
};
struct c_meson_test_suite_t {     //     test suite
    char *test_suite_name;
    char *rendered_test_suite;
};
struct c_meson_test_case_t {    //       test case
    char *test_case_name;
    char *rendered_test_case;
};
struct c_meson_module_t {              // ./xxxxx/xxxxx.c,  ./xxxxx/xxxxx.h, xxxxx/meson.build
    char *name, *path;
    char *rendered_c, *rendered_h, *rendered_meson_build;
};
struct c_meson_module_test_t {        //    xxxxx-test/xxxxx-test.h, xxxx-test/xxxx-test.c, xxxxxx-test/meson.build
    char *name, *path;
    struct Vector *c_meson_module_suites_v, *c_meson_module_test_cases_v;
    char *rendered_c, *rendered_h, *rendered_meson_build;
};
//////////////////////////////////////////
char *c_meson_new_test_case(const char *MODULE_NAME);
char *c_meson_new_test_suite(const char *MODULE_NAME);
char *c_meson_new_module_dep(const char *MODULE_NAME);
char *c_meson_new_module(const char *MODULE_NAME);
char *c_meson_new_module_test(const char *MODULE_NAME);
//////////////////////////////////////////
static const char c_meson_module_test_case_template[] = "\
TEST t_{{MODULE_NAME}}_0(void){\n\
  PASS();\n\
}\n\
\n";
//////////////////////////////////////////
static const char c_meson_module_test_suite_template[] = "\
SUITE(s_{{MODULE_NAME}}_0) {\n\
  RUN_TEST(t_{{MODULE_NAME}}_0);\n\
}\n\
\n";
//////////////////////////////////////////
static const char c_meson_module_h_template[] = "\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\
//////////////////////////////////////\n\
\n";      
//////////////////////////////////////////
const char c_meson_module_c_template[] = "\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.h\"\n\
//////////////////////////////////////\
\n";      
//////////////////////////////////////////
const char c_meson_module_test_h_template[] = "\
#pragma once\n\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.c\n\"\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\
//////////////////////////////////////\n\
";                               
//////////////////////////////////////////
const char c_meson_module_test_c_template[] = "\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}-test/{{MODULE_NAME}}.c\"\n\
#include \"{{MODULE_NAME}}-test/{{MODULE_NAME}}-test.c\"\n\
//////////////////////////////////////\n\
#include \"submodules/c_greatest/greatest/greatest.h\"\n\
#include \"bench/bench.h\"\n\
//////////////////////////////////////\n\
TEST t_{{MODULE_NAME}}_0(void){\n\
  PASS();\n\
}\n\
SUITE(s_{{MODULE_NAME}}_0) {\n\
  RUN_TEST(t_{{MODULE_NAME}}_0);\n\
}\n\
\n\
GREATEST_MAIN_DEFS();\n\
\n\
int main(int argc, char **argv) {\n\
  GREATEST_MAIN_BEGIN();\n\
  RUN_SUITE(s_{{MODULE_NAME}}_0);    \n\
} /* main */\n";
//////////////////////////////////////////
const char c_meson_module_dep_template[] = "\
c_unja_srcs = [files(\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.c',\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.h',\n\
)]\n\
\n\
c_unja_dirs = [\n\
  '../../../submodules/{{MODULE_NAME}}',\n\
  '../../../submodules/{{MODULE_NAME}}/src',\n\
  '../../../submodules/{{MODULE_NAME}}/include',\n\
  inc,\n\
]\n\
\n\
c_unja_deps = [\n\
\n\
]\n\
\n\
c_unja_lib = shared_library('{{MODULE_NAME}}',\n\
  c_unja_srcs,\n\
  install: false,\n\
  dependencies: c_unja_deps,\n\
  include_directories: c_unja_dirs,\n\
)\n\
\n\
c_unja_dep = declare_dependency(\n\
  include_directories: c_unja_dirs,\n\
  link_with: c_unja_lib,\n\
)\n";
//////////////////////////////////////////
