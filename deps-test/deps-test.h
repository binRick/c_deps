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
#include "int/int.h"
#include "socket99/socket99.h"
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
#include "submodules/str-replace.c/src/str-replace.h"
#include "submodules/str-truncate.c/src/str-truncate.h"
#include "submodules/timestamp/timestamp.h"
#include "submodules/tiny-regex-c/re.h"
#include "submodules/vtparse/vtparse/vtparse.h"
#define MKCREFLECT_IMPL


typedef struct {
  int p1;
  int p2;
} BaseStruct;


enum ExampleEvents {
  EVENT_START  = 100,
  EVENT_MIDDLE = 200,
  EVENT_END    = 300
};

struct FnArgs {
  int counter;
};

