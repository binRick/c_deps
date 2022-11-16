#ifndef EXEC_FZF_C
#define EXEC_FZF_C
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#include "ansi-utils/ansi-utils.h"
#include "b64.c/b64.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "exec-fzf/exec-fzf.h"
#include "submodules/log/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
#include "bytes/bytes.h"
#include "exec-fzf/exec-fzf-effects.h"
#define INCBIN_SILENCE_BITCODE_WARNING
#include "incbin/incbin.h"
INCBIN(fzf_bin,"/usr/local/bin/fzf");

char *__fzf_items(module(fzf) *exports, void **items, size_t qty, char *item_name){
  clib_module_init(fzf, exports);
  log_info("items...");
}

int __fzf_init(module(fzf) *exports) {
  clib_module_init(fzf, exports);
  exports->qty++;
  log_info("%lu",exports->qty);
  return 0;
}

void __fzf_deinit(module(fzf) *exports) {
  clib_module_deinit(fzf);
}

//////////////////////////////////////////////
#define FZF_DEBUG_MODE    (fe->debug_mode == true)
bool encode_preview_cmd(struct fzf_exec_t *fe){
  asprintf(&fe->sub_preview_cmd_file,
           "%s.encoded-preview-cmd-%lld.txt",
           gettempdir(),
           timestamp()
           );
  asprintf(&fe->sub_preview_cmd,
           "%s %s --norc --noprofile < %s",
           fe->env_path, fe->sh_path, fe->sub_preview_cmd_file
           );
  asprintf(&fe->encoded_preview_cmd,
           "%s %s --norc --noprofile -c \"%s\"",
           fe->env_path, fe->sh_path, fe->sub_preview_cmd
           );
  fsio_write_text_file(fe->sub_preview_cmd_file, fe->sub_preview_cmd);
  log_info("sub_preview_cmd_file: %s", fe->sub_preview_cmd_file);
  log_info("sub_preview_cmd: %s", fe->sub_preview_cmd);
  log_info("encoded_preview_cmd: %s", fe->encoded_preview_cmd);
  log_info("preview_cmd: %s", fe->preview_cmd);
  return(true);
}
#define EF_FREE_IF(FE, VAR) if(FE->VAR)free(FE->VAR);
#define EF_FREE_IF_FXN(FE, VAR, FXN) if(FE->VAR)FXN(FE->VAR);
void exec_fzf_release(struct fzf_exec_t *fe){
  if (fe) {
    if (fe->fzf_keybinds_v) {
      for (size_t i = 0; i < vector_size(fe->fzf_keybinds_v); i++){
        struct fzf_keybind_t *kb = vector_get(fe->fzf_keybinds_v, i);
      }
      vector_release(fe->fzf_keybinds_v);
    }
    EF_FREE_IF(fe,selected_options);
    EF_FREE_IF(fe,input_options);
    if (fe->fzf_keybinds_sb)
      stringbuffer_release(fe->fzf_keybinds_sb);
    if(fe->encoded_preview_cmd)
      free(fe->encoded_preview_cmd);
    free(fe);
  }
}

struct fzf_exec_t *exec_fzf_setup(void){
  struct fzf_exec_t *e = malloc(sizeof(struct fzf_exec_t));
  {
    e->input_options      = vector_new();
    e->selected_options   = vector_new();
    e->fzf_keybinds_v     = vector_new();
    e->fzf_header_lines_v = vector_new();
  }
  {
    e->fzf_keybinds_sb     = stringbuffer_new();
    e->fzf_header_lines_sb = stringbuffer_new();
  }

  e->fzf_reverse         = true;
  e->header_first        = true;
  e->border              = true;
  e->cycle               = true;
  e->ansi                = true;
  e->query_s             = "";
  e->fzf_prompt          = ">";
  e->fzf_default_opts    = "";
  e->fzf_default_command = "";
  e->fzf_info            = "inline";
  e->separator            = stringfn_trim(b64_decode(EXEC_FZF_EFFECT_DOTS_ENCODED,strlen(EXEC_FZF_EFFECT_DOTS_ENCODED)));
  e->border_style            = "double";
  e->fzf_history_file    = "/dev/null";
  e->height              = 100;
  e->header_lines        = 0;
  e->top_margin          = 0;
  e->right_margin        = 0;
  e->left_margin         = 0;
  e->bottom_margin       = 0;
  e->fzf_pointer         = ">";
  e->fzf_marker          = ">";
  e->top_padding         = 0;
  e->right_padding       = 0;
  e->left_padding        = 0;
  e->bottom_padding      = 0;
  e->preview_size        = 70;
  e->preview_type        = "right";
  e->fzf_path       = (char *)which_path("fzf", getenv("PATH"));
  e->env_path       = (char *)which_path("env", getenv("PATH"));
  e->sh_path        = (char *)which_path("sh", getenv("PATH"));
  e->tempdir        = gettempdir();
  e->selected_options = vector_new();
  return(e);
}

int exec_fzf(struct fzf_exec_t *fe){
  fe->reproc_options = (reproc_options) { .redirect.parent = true, };
  fe->input_array    = vector_to_array(fe->input_options);
  fe->input_s        = stringfn_join(fe->input_array, "\\n", 0, vector_size(fe->input_options));
  fe->input_lines_s  = stringfn_join(fe->input_array, "\n", 0, vector_size(fe->input_options));
  asprintf(&fe->options_file, "%s.options-file-%lld.txt",
           fe->tempdir,
           timestamp()
           );
  asprintf(&fe->output_file, "%s.output-file-%lld.txt",
           fe->tempdir,
           timestamp()
           );
  if (FZF_DEBUG_MODE) {
    log_info("%s", fe->output_file);
    log_info("%s", fe->fzf_path);
    log_info("%s", fe->header);
    log_info("%s", fe->input_s);
  }

  for (size_t i = 0; i < vector_size(fe->fzf_keybinds_v); i++) {
    char                 *buf;
    struct fzf_keybind_t *kb = vector_get(fe->fzf_keybinds_v, i);
    stringbuffer_append_string(fe->fzf_keybinds_sb, " ");
    asprintf(&buf, "--bind '%s:%s(%s)'",
             kb->key,
             kb->type,
             kb->cmd
             );
    stringbuffer_append_string(fe->fzf_keybinds_sb, buf);
    stringbuffer_append_string(fe->fzf_keybinds_sb, " ");
  }

  for (size_t i = 0; i < vector_size(fe->fzf_header_lines_v); i++) {
    char *hl = vector_get(fe->fzf_header_lines_v, i);
    stringbuffer_append_string(fe->fzf_header_lines_sb, hl);
    stringbuffer_append_string(fe->fzf_header_lines_sb, "|\n");
  }
  {
    fe->fzf_header_lines_s = stringbuffer_to_string(fe->fzf_header_lines_sb);
    fe->fzf_keybinds_s     = stringbuffer_to_string(fe->fzf_keybinds_sb);
  }
  if (fe->debug_mode)
    log_info("keybinds_s: %s", fe->fzf_keybinds_s);

  asprintf(&fe->header,
           "%s\n%s",
           fe->header,
           stringfn_mut_trim(stringbuffer_to_string(fe->fzf_header_lines_sb))
           );
  asprintf(&fe->options_file_content_s,
           "%s",
           stringfn_mut_trim(fe->input_lines_s)
           );
  fsio_write_text_file(fe->options_file, fe->options_file_content_s);
  asprintf(&fe->fzf_default_opts,
           " --color='bg:#0c0c0c,bg+:#3F3F3F,info:#BDBB72,border:#6B6B6B,spinner:#98BC99'"
           " --color='hl:#719872,fg:#D9D9D9,header:#719872,fg+:#D9D9D9'"
           " --color='pointer:#E12672,marker:#E17899,prompt:#98BEDE,hl+:#98BC99'"
           " --header-lines='%lu'"
           " --height='%d'"
           " --header='Description of the interface'"
           " --query='%s'"
           " --preview='%s'"
           " --info='%s'"
           " --history='%s'"
           " --pointer='%s'"
           " --marker='%s'"
           " --prompt='%s'"
           " --margin='%d,%d,%d,%d'"
           " --padding='%d,%d,%d,%d'"
           " --preview-window='%s,%s,%s,%d%%'"
           " --%sreverse"
           " --%smulti"
           " --%sheader-first"
           " --%scycle"
           " --%sborder"
           " --%sansi"
           " --separator='%s'"
           " --border='%s'"
           " --border-label='╣" AC_GREEN AC_CURLY_UNDERLINE "%s" AC_RESETALL "╠'"
           " --border-label-pos='3,top'"
           " %s",
           (size_t)fe->header_lines,
           fe->height,
           fe->query_s,
           (fe->preview_cmd != NULL && strlen(fe->preview_cmd) > 0)
               ? fe->preview_cmd
               : "echo {}",
           fe->fzf_info,
           fe->fzf_history_file,
           fe->fzf_pointer,
           fe->fzf_marker,
           fe->fzf_prompt,
           fe->top_margin, fe->right_margin, fe->bottom_margin, fe->left_margin,
           fe->top_padding, fe->right_padding, fe->bottom_padding, fe->left_padding,
           "nofollow", "nowrap", fe->preview_type, fe->preview_size,
           (fe->fzf_reverse == true) ?     "" : "no-",
           (fe->select_multiple == true) ? "" :   "no-",
           (fe->header_first == true) ? "" :   "no-",
           (fe->cycle == true) ? "" :   "no-",
           (fe->border == true) ? "" :   "no-",
           (fe->ansi == true) ? "" :   "no-",
           (fe->separator),
           (fe->border_style),
           (fe->header),
           (fe->fzf_keybinds_s != NULL && strlen(fe->fzf_keybinds_s) > 10)
               ? fe->fzf_keybinds_s
               : ""
           );

  asprintf(&fe->fzf_cmd,
           "\"%s\""
           " -i"
           " SHELL=\"%s\""
           " FZF_DEFAULT_OPTS=\"%s\""
           " FZF_DEFAULT_COMMAND=\"%s\""
           " \"%s\""
           " < \"%s\""
           " > \"%s\""
           "",
           fe->env_path,
           fe->sh_path,
           fe->fzf_default_opts,
           fe->fzf_default_command,
           fe->fzf_path,
           fe->options_file,
           fe->output_file
           );

  if (FZF_DEBUG_MODE || (fe->debug_mode == true))
    log_debug("%s", fe->fzf_cmd);

  if(getenv("SAVE_FZF_CMD_FILE"))
    if(fsio_write_text_file(getenv("SAVE_FZF_CMD_FILE"),fe->fzf_cmd))
      log_debug("Saved %s fzf command to %s",bytes_to_string(strlen(fe->fzf_cmd)), getenv("SAVE_FZF_CMD_FILE"));


//  bool ok = encode_preview_cmd(fe);

  const char *exec_cmd[] = {
    fe->env_path, fe->sh_path, "--norc", "--noprofile", "-c", fe->fzf_cmd,
    NULL
  };

  fe->proc_result = REPROC_ENOMEM;

  fe->proc = reproc_new();
  if (fe->proc == NULL)
    goto finish;

  if (fsio_file_exists(fe->output_file))
    fsio_remove(fe->output_file);

  if (FZF_DEBUG_MODE)
    log_info("%s", fe->fzf_cmd);

  fe->proc_result = reproc_start(fe->proc, exec_cmd, (reproc_options){
    .redirect.parent = true
  });

  if (FZF_DEBUG_MODE)
    log_info("%d", fe->proc_result);

  if (fe->proc_result < 0)
    goto finish;

  fe->proc_exit_code = reproc_wait(fe->proc, REPROC_INFINITE);
  if (FZF_DEBUG_MODE)
    log_info("%d", fe->proc_exit_code);

finish:
  if (FZF_DEBUG_MODE)
    log_info("finished");
  reproc_destroy(fe->proc);
  if (FZF_DEBUG_MODE)
    log_info("destroyed");

  if (fe->proc_result < 0)
    fprintf(stderr, "Error: %s\n", reproc_strerror(fe->proc_result));
  else if (fsio_file_exists(fe->output_file)) {
    char *output = stringfn_mut_trim(fsio_read_text_file(fe->output_file));
    if (FZF_DEBUG_MODE)
      log_info("out file: %s", fe->output_file);
    fe->output_lines = stringfn_split_lines_and_trim(output);
    if (FZF_DEBUG_MODE)
      log_info("out file lines: %d", fe->output_lines.count);
    for (int i = 0; i < fe->output_lines.count; i++) {
      if (FZF_DEBUG_MODE)
        log_info("line #%d- %s", i, fe->output_lines.strings[i]);
      if (strlen(fe->output_lines.strings[i]) > 0)
        vector_push(fe->selected_options, fe->output_lines.strings[i]);
    }
    if (FZF_DEBUG_MODE)
      log_info("OK, %lu options selected", vector_size(fe->selected_options));
  }
  if (fsio_file_exists(fe->output_file))
    fsio_remove(fe->output_file);

  if (FZF_DEBUG_MODE)
    log_info("Selected %lu/%lu Options",
             vector_size(fe->selected_options),
             vector_size(fe->input_options)
             );

  if (FZF_DEBUG_MODE)
    for (size_t i = 0; i < vector_size(fe->selected_options); i++)
      log_info("Selected Option #%lu:  '%s'",
               i,
               (char *)vector_get(fe->selected_options, i)
               );
  return(EXIT_SUCCESS);
} /* execute_fwded_process */

char *exec_fzf_select_from_items_v(struct Vector *v, char *item_name){
  return(exec_fzf_select_from_items(vector_to_array(v),vector_size(v),item_name));
}

char *exec_fzf_select_from_items(void **items, size_t qty, char *item_name){
  int res;
  char *result=NULL;
  struct fzf_exec_t *fe = exec_fzf_setup();
  {
    asprintf(&(fe->header),"Select a %s", item_name);
    asprintf(&(fe->fzf_prompt),"%s> ", item_name);
    fe->debug_mode      = false;
    fe->height          = 50;
    fe->select_multiple = false;
    fe->preview_size = 25;
    fe->preview_type = "bottom";
    fe->preview_cmd  = "echo selected item {}";

  fe->height       = 25;
  fe->preview_size = 75;
  fe->preview_type = "right";
  fe->fzf_pointer  = "->";
  fe->fzf_marker   = "* ";
  fe->fzf_info     = "inline";

  }
  for(int i = 0;i<qty;i++)
    vector_push(fe->input_options,(char *)(items[i]));
  res = exec_fzf(fe);
  result = (vector_size(fe->selected_options)>0) ? (char*)vector_get(fe->selected_options,0) : NULL;
  exec_fzf_release(fe);
  return(result);
}

#undef FZF_DEBUG_MODE

#endif
