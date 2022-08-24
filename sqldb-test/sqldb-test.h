#pragma once
//////////////////////////////////////
#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
//////////////////////////////////////
#include "int/int.h"
#include "sqldb-test/sqldb-test.h"
#include "submodules/b64.c/b64.h"
#include "submodules/c_ansi/ansi-codes/ansi-codes.h"
#include "submodules/c_ansi/ansi-utils/ansi-utils.h"
#include "submodules/c_eventemitter/include/eventemitter.h"
#include "submodules/c_forever/include/forever.h"
#include "submodules/c_string_buffer/include/stringbuffer.h"
#include "submodules/c_stringfn/include/stringfn.h"
#include "submodules/c_vector/vector/vector.h"
#include "submodules/catpath/catpath.h"
#include "submodules/dbg.h/dbg.h"
#include "submodules/dmt/src/dmt.h"
#include "submodules/libbeaufort/include/beaufort.h"
#include "submodules/murmurhash.c/murmurhash.h"
#include "submodules/sqldbal/src/sqldbal.h"
#include "submodules/str-replace.c/src/str-replace.h"
#include "submodules/str-truncate.c/src/str-truncate.h"
#include "submodules/timestamp/timestamp.h"
#include "submodules/tiny-regex-c/re.h"
#define DEBUG_FLAGS    (SQLDBAL_FLAG_DEBUG | SQLDBAL_FLAG_SQLITE_OPEN_CREATE | SQLDBAL_FLAG_SQLITE_OPEN_READWRITE)
#define _FLAGS         (SQLDBAL_FLAG_SQLITE_OPEN_CREATE | SQLDBAL_FLAG_SQLITE_OPEN_READWRITE)
#define FLAGS          DEBUG_FLAGS
#define INSERT_QTY     3
#define LOCATION       "sqldb-test.sqlite"
