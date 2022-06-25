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
                         (INTEGER, unsigned int, number)
                         )


MKCREFLECT_DEFINE_STRUCT(TestStruct,
                         (INTEGER, int, i),
                         (INTEGER, long, l),
                         (INTEGER, int, i0),
                         (INTEGER, short, sh),
                         (INTEGER, unsigned long, ul),
                         (INTEGER, unsigned long long, ull),
                         (INTEGER, unsigned int, ui),
                         (INTEGER, size_t, s),
                         (INTEGER, long long, ll),
                         (STRING, char, name, 32),
                         (STRING, char, n, 2),
                         (STRING, char, n0, 2),
                         (STRUCT, Address, address)
                         )

#define EXPAND(x)                    x
#define BOOL_TO_STR(BOOL)            (BOOL) ? "Yes" : "No"
#define FIELD_IS_POINTER(TYPE_ID)    (TYPE_ID == 6)
#define TestStructInfo    mkcreflect_get_TestStruct_type_info()
#define ___STR(S)                    S
#define __STR(S)                     #S
#define _STR(S)                      __STR(S)
#define _str(S)                      ___STR(S)
#define concat0(s1, s2, s3)          (s1 s2 s3)
#define concat1(str1, str2)          (_STR(str1) _STR(str2))
//////////////////////////////////////
#define S_INFO(N)                    mkcreflect_get_ ## N ## _type_info
#define _S_INFO(N)                   ("mkcreflect_get_" N "_type_info")
//////////////////////////////////////
#define S_NAME(N)                    (char *)S_INFO(N)()->name
#define S_FIELDS_COUNT(N)            (size_t)S_INFO(N)()->fields_count
#define S_SIZE(N)                    (size_t)S_INFO(N)()->size
#define S_PACKED_SIZE(N)             (size_t)S_INFO(N)()->packed_size
#define S_FIELDS(N)                  (MKCREFLECT_FieldInfo *)S_INFO(N)()->fields
#define S_FIELD(N, F)                S_INFO(N)()->fields[F]
//////////////////////////////////////

