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
const char c_meson_module_test_case_template[] = "\
TEST t_{{MODULE_NAME}}_0(void){\
  PASS();\
}\
";
//////////////////////////////////////////
const char c_meson_module_test_suite_template[] = "\
SUITE(s_{{MODULE_NAME}}_0) {\
  RUN_TEST(t_{{MODULE_NAME}}_0);\
}\
";
//////////////////////////////////////////
const char c_meson_module_h_template[] = "\
//////////////////////////////////////\
#include <stdlib.h>\
#include <stdio.h>\
#include <stdint.h>\
#include <stdbool.h>\
#include <string.h>\
//////////////////////////////////////\
";      
//////////////////////////////////////////
const char c_meson_module_c_template[] = "\
//////////////////////////////////////\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.h\"\
//////////////////////////////////////\
";      
//////////////////////////////////////////
const char c_meson_module_test_h_template[] = "\
#pragma once\
//////////////////////////////////////\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.c\"\
//////////////////////////////////////\
#include <stdlib.h>\
#include <stdio.h>\
#include <stdint.h>\
#include <stdbool.h>\
#include <string.h>\
//////////////////////////////////////\
";                               
//////////////////////////////////////////
const char c_meson_module_test_c_template[] = "\
//////////////////////////////////////\
#include \"{{MODULE_NAME}}-test/{{MODULE_NAME}}.c\"\
#include \"{{MODULE_NAME}}-test/{{MODULE_NAME}}-test.c\"\
//////////////////////////////////////\
#include \"greatest/greatest.h\"\
#include \"bench/bench.h\"\
//////////////////////////////////////\
TEST t_{{MODULE_NAME}}_0(void){\
  PASS();\
}\
SUITE(s_{{MODULE_NAME}}_0) {\
  RUN_TEST(t_{{MODULE_NAME}}_0);\
}\
\
GREATEST_MAIN_DEFS();\
\
int main(int argc, char **argv) {\
  GREATEST_MAIN_BEGIN();\
  RUN_SUITE(s_{{MODULE_NAME}}_0);    \
} /* main */";
//////////////////////////////////////////
const char c_meson_module_dep_template[] = "\
c_unja_srcs = [files(\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.c',\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.h',\
)]\
\
c_unja_dirs = [\
  '../../../submodules/{{MODULE_NAME}}',\
  '../../../submodules/{{MODULE_NAME}}/src',\
  '../../../submodules/{{MODULE_NAME}}/include',\
  inc,\
]\
\
c_unja_deps = [\
\
]\
\
c_unja_lib = shared_library('{{MODULE_NAME}}',\
  c_unja_srcs,\
  install: false,\
  dependencies: c_unja_deps,\
  include_directories: c_unja_dirs,\
)\
\
c_unja_dep = declare_dependency(\
  include_directories: c_unja_dirs,\
  link_with: c_unja_lib,\
)";
//////////////////////////////////////////
