#pragma once
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "cargs/include/cargs.h"
#include "ee.c/src/ee.h"
#include "log.h/log.h"
#include "parson.h"
#include "reproc/reproc/include/reproc/export.h"
#include "reproc/reproc/include/reproc/reproc.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/time.h>

typedef void (*ee_target_handler)(JSON_Object *Target);

char *execute_processes();

JSON_Array *parse_execution_result(char *OUTPUT);

void iterate_targets(ee_t *ee, JSON_Array *A);
