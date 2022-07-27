#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/////////////////////////////////////
struct c_meson_dep_t {
    char *dep_name;
};
struct c_meson_test_t {
    char *test_name;
};
//////////////////////////////////////////
char *c_meson_new_test(const char *TEST_NAME);
char *c_meson_new_dep(const char *DEP_NAME);
//////////////////////////////////////////
