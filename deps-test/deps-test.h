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
