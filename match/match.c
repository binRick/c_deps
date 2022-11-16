#pragma once
#ifndef MATCH_C
#define MATCH_C
#define LOCAL_DEBUG_MODE    MATCH_DEBUG_MODE
////////////////////////////////////////////
#include "match/match.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "tinydir/tinydir.h"
#include "wildcardcmp/wildcardcmp.h"

////////////////////////////////////////////
static bool MATCH_DEBUG_MODE = false;
static char **__match__Files(const char *PATH, const char *GLOB, int *qty);
static void __attribute__((constructor)) __constructor__match(void);
///////////////////////////////////////////////////////////////////////

int __match_module_init(module(match) *exports) {
  clib_module_init(match, exports);
  return 0;
}

void __match_module_deinit(module(match) *exports) {
  clib_module_deinit(match);
}

char **__match_module_files(module(match) * exports, const char *PATH,const char *GLOB,int *qty){
  clib_module_init(match, exports);
  log_info("Match Module :: Files |%s|%s|%d|",PATH,GLOB,*qty);
  return(0);
}

char **__MATCH__GET_FILES_FROM_PATH(const char *PATH, const char *GLOB, int *qty){
  return(__match__Files(PATH,GLOB,qty));
}

static char **__match__Files(const char *PATH, const char *GLOB, int *qty){
  struct Vector *items_v = vector_new();
	tinydir_dir dir;
	if (tinydir_open(&dir, PATH) == -1){
		perror("Error opening file");
		goto bail;
	}

	while (dir.has_next){
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1){
			perror("Error getting file");
			goto bail;
		}

		if (!(file.is_dir) && file.is_reg)
      if(wildcardcmp(GLOB,file.name))
        vector_push(items_v,(void*)(strdup(file.name)));

		if (tinydir_next(&dir) == -1){
			perror("Error getting next file");
			goto bail;
		}
	}

bail:
	tinydir_close(&dir);
  *qty = (int)(size_t)vector_size(items_v);
	return(vector_to_array(items_v));
}
//__match_path_match_handler_t 
//static inline __match_path_match_handler_t __match_path_match_handler_t
//}

static void __attribute__((constructor)) __constructor__match(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_match") != NULL) {
    log_debug("Enabling match Debug Mode");
    MATCH_DEBUG_MODE = true;
  }
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE
#endif
