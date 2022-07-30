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
#include "c_vector/include/vector.h"
#include "exec-fzf/exec-fzf.h"
#include "submodules/log.h/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
//////////////////////////////////////////////
#define FZF_DEBUG_MODE    (fzf_exec->debug_mode == true)


void release_fzf_exec(struct fzf_exec_t *fzf_exec){
  if (fzf_exec) {
    free(fzf_exec);
  }
}

struct fzf_exec_t *setup_fzf_exec(void){
  struct fzf_exec_t *e = malloc(sizeof(struct fzf_exec_t));

  e->input_options    = vector_new();
  e->selected_options = vector_new();
  return(e);
}


int execute_fzf_process(struct fzf_exec_t *fzf_exec){
  if (fzf_exec->selected_options == NULL) {
    fzf_exec->selected_options = vector_new();
  }
  fzf_exec->reproc_options = (reproc_options) { .redirect.parent = true, };
  if (fzf_exec->tempdir == NULL) {
    fzf_exec->tempdir = gettempdir();
  }
  if (fzf_exec->fzf_path == NULL) {
    fzf_exec->fzf_path    = (char *)which_path("fzf", getenv("PATH")),
    fzf_exec->input_array = vector_to_array(fzf_exec->input_options);
  }
  fzf_exec->input_s = stringfn_join(fzf_exec->input_array, "\\n", 0, vector_size(fzf_exec->input_options));
  if (FZF_DEBUG_MODE) {
    log_info("%lu in:'%s'\n", vector_size(fzf_exec->input_options), fzf_exec->input_s);
  }
  asprintf(&fzf_exec->output_file, "%s.output-file-%lld.txt",
           fzf_exec->tempdir,
           timestamp()
           );
  if (FZF_DEBUG_MODE) {
    log_info("%s", fzf_exec->output_file);
  }
  asprintf(&fzf_exec->fzf_cmd,
           "printf '%s' | %s -m --reverse --header='%s' > '%s'",
           fzf_exec->input_s,
           fzf_exec->fzf_path,
           fzf_exec->header,
           fzf_exec->output_file
           );

  const char *exec_cmd[] = {
    "/usr/bin/env",    "sh", "--norc", "--noprofile", "-c",
    fzf_exec->fzf_cmd,
    NULL
  };

  fzf_exec->proc_result = REPROC_ENOMEM;

  fzf_exec->proc = reproc_new();
  if (fzf_exec->proc == NULL) {
    goto finish;
  }

  if (fsio_file_exists(fzf_exec->output_file)) {
    fsio_remove(fzf_exec->output_file);
  }

  if (FZF_DEBUG_MODE) {
    log_info("%s", fzf_exec->fzf_cmd);
  }

  fzf_exec->proc_result = reproc_start(fzf_exec->proc, exec_cmd, (reproc_options){
    .redirect.parent = true
  });

  if (FZF_DEBUG_MODE) {
    log_info("%d", fzf_exec->proc_result);
  }

  if (fzf_exec->proc_result < 0) {
    goto finish;
  }

  fzf_exec->proc_exit_code = reproc_wait(fzf_exec->proc, REPROC_INFINITE);
  if (FZF_DEBUG_MODE) {
    log_info("%d", fzf_exec->proc_exit_code);
  }

finish:
  if (FZF_DEBUG_MODE) {
    log_info("finished");
  }
  reproc_destroy(fzf_exec->proc);
  if (FZF_DEBUG_MODE) {
    log_info("destroyed");
  }


  if (fzf_exec->proc_result < 0) {
    fprintf(stderr, "Error: %s\n", reproc_strerror(fzf_exec->proc_result));
  }else{
    if (fsio_file_exists(fzf_exec->output_file)) {
      char *output = stringfn_mut_trim(fsio_read_text_file(fzf_exec->output_file));
      if (FZF_DEBUG_MODE) {
        log_info("out file: %s", fzf_exec->output_file);
      }
      fzf_exec->output_lines = stringfn_split_lines_and_trim(output);
      if (FZF_DEBUG_MODE) {
        log_info("out file lines: %d", fzf_exec->output_lines.count);
      }
      fsio_remove(fzf_exec->output_file);
      for (size_t i = 0; i < fzf_exec->output_lines.count; i++) {
        if (FZF_DEBUG_MODE) {
          log_info("line #%lu- %s", i, fzf_exec->output_lines.strings[i]);
        }
        if (strlen(fzf_exec->output_lines.strings[i]) > 0) {
          vector_push(fzf_exec->selected_options, fzf_exec->output_lines.strings[i]);
        }
      }
      if (FZF_DEBUG_MODE) {
        log_info("OK, %lu options selected", vector_size(fzf_exec->selected_options));
      }
    }
  }

  if (FZF_DEBUG_MODE) {
    log_info("Selected %lu/%lu Options",
             vector_size(fzf_exec->selected_options),
             vector_size(fzf_exec->input_options)
             );
  }

  if (FZF_DEBUG_MODE) {
    for (size_t i = 0; i < vector_size(fzf_exec->selected_options); i++) {
      log_info("Selected Option #%lu:  '%s'",
               i,
               (char *)vector_get(fzf_exec->selected_options, i)
               );
    }
  }
  return(EXIT_SUCCESS);
} /* execute_fwded_process */


static void __attribute__((constructor)) __exec_fzf_constructor(){
}
static void __attribute__((destructor)) __exec_fzf_subprocess_destructor(){
}
#undef FZF_DEBUG_MODE
