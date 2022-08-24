#pragma once
/////////////////////////////////////
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
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
  char          *name, *path;
  struct Vector *c_meson_module_suites_v, *c_meson_module_test_cases_v;
  char          *rendered_c, *rendered_h, *rendered_meson_build;
};
//////////////////////////////////////////
char *c_meson_new_test_case(const char *MODULE_NAME);
char *c_meson_new_test_suite(const char *MODULE_NAME);
char *c_meson_new_module_dep(const char *MODULE_NAME);
char *c_meson_new_module(const char *MODULE_NAME);
char *c_meson_new_module_test(const char *MODULE_NAME);
//////////////////////////////////////////
//////////////////////////////////////////
//            Embedded INCBIN Python Binaries
//////////////////////////////////////////
static const char c_meson_bash_script_template[]            = "\n\
#!/usr/bin/env bash\n\
set -eou pipefail\n\
cd \"$(cd \"$(dirname \"${BASH_SOURCE[0]}\")\" && pwd)\"\n";
static const char c_meson_embedded_incbin_python_binaries[] = "\n\
#pragma once\n\
#include \"incbin/incbin.h\"\n\
#ifndef INC_PYTON_BINARIES\n\
const size_t EMBEDDED_PYTHON_BINARIES_QTY = {{ binaries | length }};\
#define INCBIN_SILENCE_BITCODE_WARNING\n\
#ifndef INCBIN_STYLE\
 #define INCBIN_STYLE                    INCBIN_STYLE_SNAKE\n\
#endif\n\
#ifndef INCBIN_PREFIX\
 #define INCBIN_PREFIX                   inc_\n\
#endif\n\
#define INC_PYTON_BINARIES\n\n\
{% for l in binaries -%}\n\
INCTXT({{l.name|replace('-','_')}}, \"{{l.dir}}/{{l.name}}\");\n\
{% endfor %}\n\
{{inc_embedded_python_binaries_struct|replace(';','')}} static struct python_binary_t python_binaries[{{binaries|length+1}}] = {\n\
 {%-for l in binaries %}\n\
  { .name = \"{{l.name}}\", .dir = \"{{l.dir}}\", },\n\
 {%- endfor %}\n\
  { 0 },\n\
};\n\
#endif\n\
\n";
//////////////////////////////////////////
//            TEST CASE
//////////////////////////////////////////
static const char c_meson_module_test_case_template[] = "\
TEST t_{{MODULE_NAME}}_0(void){\n\
  PASS();\n\
}\n\
\n";
//////////////////////////////////////////
//////////////////////////////////////////
//            END TEST CASE

//////////////////////////////////////////
//            TEST SUITE
//////////////////////////////////////////
static const char c_meson_module_test_suite_template[] = "\
SUITE(s_{{MODULE_NAME}}_0) {\n\
  RUN_TEST(t_{{MODULE_NAME}}_0);\n\
}\n\
\n";
//////////////////////////////////////////
//            END TEST SUITE
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
const char        c_meson_module_c_template[] = "\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.h\"\n\
//////////////////////////////////////\
\n";
//////////////////////////////////////////
const char        c_meson_module_test_h_template[] = "\
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
//            MODULE
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
//            END MODULE
//////////////////////////////////////////

//////////////////////////////////////////
//               TEST EXECUTABLE
//////////////////////////////////////////
static const char c_meson_jinja2_template_test_executable_meson_build[] = "\
c_{{MODULE_NAME}}_srcs = [files(\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.c',\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.h',\n\
)]\n\
\n\
c_{{MODULE_NAME}}_dirs = [\n\
  '../../../submodules/{{MODULE_NAME}}',\n\
  '../../../submodules/{{MODULE_NAME}}/src',\n\
  '../../../submodules/{{MODULE_NAME}}/include',\n\
  inc,\n\
]\n\
\n\
c_{{MODULE_NAME}}_deps = [\n\
\n\
]\n\
\n\
c_{{MODULE_NAME}}_lib = shared_library('{{MODULE_NAME}}',\n\
  c_{{MODULE_NAME}}_srcs,\n\
  install: false,\n\
  dependencies: c_{{MODULE_NAME}}_deps,\n\
  include_directories: c_{{MODULE_NAME}}_dirs,\n\
)\n\
\n\
c_{{MODULE_NAME}}_dep = declare_dependency(\n\
  include_directories: c_{{MODULE_NAME}}_dirs,\n\
  link_with: c_{{MODULE_NAME}}_lib,\n\
)\n";
static const char c_meson_jinja2_template_test_executable_c[]           = "\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}-test/{{MODULE_NAME}}.h\"\n\
#include \"{{MODULE_NAME}}-test/{{MODULE_NAME}}-test.h\"\n\
//////////////////////////////////////\n\
#include \"c_greatest/greatest/greatest.h\"\n\
//////////////////////////////////////\n\
TEST t_{{MODULE_NAME}}_0(void){\n\
  PASS();\n\
}\n\
SUITE(s_{{MODULE_NAME}}_0) {\n\
  RUN_TEST(t_{{MODULE_NAME}}_0);\n\
}\n\
\n\
GREATEST_MAIN_DEFS();\n\
int main(int argc, char **argv) {\n\
  GREATEST_MAIN_BEGIN();\n\
  RUN_SUITE(s_{{MODULE_NAME}}_0);    \n\
}\n";
static const char c_meson_jinja2_template_test_executable_h[]           = "\
#pragma once\n\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.h\n\"\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\n";
//////////////////////////////////////////
//       END TEST EXECUTABLE
//////////////////////////////////////////

//////////////////////////////////////////
//       EXECUTABLE
//////////////////////////////////////////
static const char c_meson_jinja2_template_executable_meson_build[] = "\
c_{{MODULE_NAME}}_srcs = [files(\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.c',\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.h',\n\
)]\n\
\n\
c_{{MODULE_NAME}}_dirs = [\n\
  '../../../submodules/{{MODULE_NAME}}',\n\
  '../../../submodules/{{MODULE_NAME}}/src',\n\
  '../../../submodules/{{MODULE_NAME}}/include',\n\
  inc,\n\
]\n\
\n\
c_{{MODULE_NAME}}_deps = [\n\
\n\
]\n\
\n\
c_{{MODULE_NAME}}_lib = shared_library('{{MODULE_NAME}}',\n\
  c_{{MODULE_NAME}}_srcs,\n\
  install: false,\n\
  dependencies: c_{{MODULE_NAME}}_deps,\n\
  include_directories: c_{{MODULE_NAME}}_dirs,\n\
)\n\
\n\
c_{{MODULE_NAME}}_dep = declare_dependency(\n\
  include_directories: c_{{MODULE_NAME}}_dirs,\n\
  link_with: c_{{MODULE_NAME}}_lib,\n\
)\n";
static const char c_meson_jinja2_template_executable_c[]           = "\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.h\"\n\
//////////////////////////////////////\n\
int main(int argc, char **argv) {\n\
    return(EXIT_SUCESS);\n\
}\n";
static const char c_meson_jinja2_template_executable_h[]           = "\
#pragma once\n\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\
//////////////////////////////////////\n";
//////////////////////////////////////////
//       END EXECUTABLE
//////////////////////////////////////////

//////////////////////////////////////////
//       LIBRARY
//////////////////////////////////////////
static const char c_meson_jinja2_template_library_meson_build[] = "\
c_{{MODULE_NAME}}_srcs = [files(\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.c',\n\
  '../../../submodules/{{MODULE_NAME}}/src/{{MODULE_NAME}}.h',\n\
)]\n\
\n\
c_{{MODULE_NAME}}_dirs = [\n\
  '../../../submodules/{{MODULE_NAME}}',\n\
  '../../../submodules/{{MODULE_NAME}}/src',\n\
  '../../../submodules/{{MODULE_NAME}}/include',\n\
  inc,\n\
]\n\
\n\
c_{{MODULE_NAME}}_deps = [\n\
\n\
]\n\
\n\
c_{{MODULE_NAME}}_lib = shared_library('{{MODULE_NAME}}',\n\
  c_{{MODULE_NAME}}_srcs,\n\
  install: false,\n\
  dependencies: c_{{MODULE_NAME}}_deps,\n\
  include_directories: c_{{MODULE_NAME}}_dirs,\n\
)\n\
\n\
c_{{MODULE_NAME}}_dep = declare_dependency(\n\
  include_directories: c_{{MODULE_NAME}}_dirs,\n\
  link_with: c_{{MODULE_NAME}}_lib,\n\
)\n";
static const char c_meson_jinja2_template_library_c[]           = "\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\
//////////////////////////////////////\n\
#include \"{{MODULE_NAME}}/{{MODULE_NAME}}.h\"\n\
//////////////////////////////////////\n\
static int t_{{MODULE_NAME}}(void *DAT){\n\
    return(EXIT_SUCESS);\n\
}\n";
//////////////////////////////////////////
static const char c_meson_jinja2_template_library_h[] = "\
//////////////////////////////////////\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdbool.h>\n\
#include <string.h>\n\
//////////////////////////////////////\n\
static int t_{{MODULE_NAME}}(void *DAT);\n";
//////////////////////////////////////////
//       END LIBRARY
//////////////////////////////////////////
