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
#include "deps/deps.h"
#include "submodules/b64.c/b64.h"
#include "submodules/c_ansi/ansi-codes/ansi-codes.h"
#include "submodules/c_ansi/ansi-utils/ansi-utils.h"
#include "submodules/c_eventemitter/include/eventemitter.h"
#include "submodules/c_forever/include/forever.h"
#include "submodules/c_vector/include/vector.h"
#include "submodules/c_workqueue/include/workqueue.h"
#include "submodules/catpath/catpath.h"
#include "submodules/dbg.h/dbg.h"
#include "submodules/dmt/src/dmt.h"
#include "submodules/http-get.c/src/http-get.h"
#include "submodules/libbeaufort/include/beaufort.h"
#include "submodules/microtar/src/microtar.h"
#include "submodules/microui/src/microui.h"
#include "submodules/mkcreflect/lib/include/mkcreflect.h"
#include "submodules/murmurhash.c/murmurhash.h"
#include "submodules/occurrences/occurrences.h"
#include "submodules/rhash_md5.c/md5.h"
#include "submodules/siphash/siphash.h"
#include "submodules/sqldbal/src/sqldbal.h"
#include "submodules/str-replace.c/src/str-replace.h"
#include "submodules/str-truncate.c/src/str-truncate.h"
#include "submodules/timestamp/timestamp.h"
#include "submodules/tiny-regex-c/re.h"
#include "submodules/vtparse/vtparse/vtparse.h"
#define LOCATION       "deps-test.sqlite"
#define DEBUG_FLAGS    (SQLDBAL_FLAG_DEBUG | SQLDBAL_FLAG_SQLITE_OPEN_CREATE | SQLDBAL_FLAG_SQLITE_OPEN_READWRIT E)
#define FLAGS          (SQLDBAL_FLAG_SQLITE_OPEN_CREATE | SQLDBAL_FLAG_SQLITE_OPEN_READWRITE)
#define INSERT_QTY     10
#define MKCREFLECT_IMPL


typedef struct {
  int p1;
  int p2;
} BaseStruct;

MKCREFLECT_DEFINE_STRUCT(Location,
                         (STRING, char, latitude, 20),
                         (STRING, char, longitude, 20)
                         )

MKCREFLECT_DEFINE_STRUCT(Address,
                         (STRING, char, street, 20),
                         (STRUCT, Location, location),
                         (INTEGER, unsigned int, house_number)
                         )


MKCREFLECT_DEFINE_STRUCT(TestStruct,
                         (INTEGER, unsigned long, id),
                         (INTEGER, size_t, size),
                         (STRING, char, name, 64),
                         (POINTER, char *, nameptrs, 20),
                         (STRUCT, BaseStruct, base),
                         (STRUCT, Address, addresses, 5),
                         (POINTER, Address *, addressptrs, 5)
                         )


#define BOOL_TO_STR(BOOL)            (BOOL) ? "Yes" : "No"
#define FIELD_IS_POINTER(TYPE_ID)    (TYPE_ID == 6)
#define TestStructInfo    mkcreflect_get_TestStruct_type_info()


enum ExampleEvents {
  EVENT_START  = 100,
  EVENT_MIDDLE = 200,
  EVENT_END    = 300
};
struct FnArgs {
  int counter;
};

