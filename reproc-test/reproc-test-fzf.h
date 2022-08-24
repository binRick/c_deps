//////////////////////////////////////////////
#define DEBUG_MEMORY
//////////////////////////////////////////////
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
#include "ansi-utils/ansi-utils.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "reproc-test.h"
#include "submodules/log.h/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
//////////////////////////////////////////////
int execute_fzf_process();

struct fzf_exec_t {
  struct Vector          *input_options;
  struct Vector          *selected_options;
  char                   **input_array;
  char                   *input_s;
  char                   *output_file;
  char                   *tempdir;
  struct StringFNStrings output_lines;
  char                   *header;
  char                   *fzf_cmd;
  char                   *fzf_path;
  char                   **subprocess_cmd;
  int                    proc_result;
  int                    proc_exit_code;
  reproc_t               *proc;
  reproc_options         reproc_options;
};
