#pragma once
/////////////////////////////////////////////////////////////////
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <wchar.h>
/////////////////////////////////////////////////////////////////
#include "term-tests-defines.h"
#include "term-tests-types.h"
/////////////////////////////////////////////////////////////////
#include "submodules/c_ansi/ansi-codes/ansi-codes.h"
#include "submodules/c_string_buffer/include/stringbuffer.h"
#include "submodules/c_stringfn/include/stringfn.h"
#include "submodules/timestamp/timestamp.h"
/////////////////////////////////////////////////////////////////
/////              Publ;ic Functions                          ///
/////////////////////////////////////////////////////////////////
int term_tests_main(int argc, char *argv[]);

/////////////////////////////////////////////////////////////////

