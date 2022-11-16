#pragma once
#ifndef MATCH_H
#define MATCH_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "exec-fzf/exec-fzf.h"
#define MATCH_PATH_HANDLER_ARGS const char *PATH, const char *MATCH_GLOB, int *qty
typedef char**(*__match_path_match_handler_t)(MATCH_PATH_HANDLER_ARGS);

module(match) {
  define(match, CLIB_MODULE);
  char **(*files)(MATCH_PATH_HANDLER_ARGS);
};

int  __match_module_init(module(match) * exports);
void __match_module_deinit(module(match) * exports);
char **__match_module_files(module(match) * exports, const char *PATH,const char *GLOB,int *qty);

exports(match) {
  .init   = __match_module_init,
  .deinit = __match_module_deinit,
  .files = 0,
};

//////////////////////////////////////
char **__MATCH__GET_FILES_FROM_PATH(const char *PATH, const char *MATCH_GLOB, int *qty);
#define match_files __MATCH__GET_FILES_FROM_PATH
#endif
