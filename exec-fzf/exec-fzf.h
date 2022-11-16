#pragma once
#ifndef EXEC_FZF_H
#define EXEC_FZF_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#include "c_vector/vector/vector.h"
#include "c_stringfn/include/stringfn.h"
#include "reproc/reproc.h"
//////////////////////////////////////////////
//////////////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
module(fzf) {
  define(fzf, CLIB_MODULE);
  pid_t pid;
  size_t qty;
  int (*open)();
  int (*close)();
  int (*send)(void *buf, size_t size);
  int (*recv)(void *buf, size_t size);
  char (*items)(void **items, size_t qty, char *item_name);
  char (*items_v)(struct Vector *v, char *item_name);
};
int __fzf_init(module(fzf) *exports);
void __fzf_deinit(module(fzf) *exports);
char *__fzf_items(module(fzf) *exports, void **items, size_t qty, char *item_name);
char *exec_fzf_select_from_items(void **items, size_t qty, char *item_name);
char *exec_fzf_select_from_items_v(struct Vector *v, char *item_name);
exports(fzf) {
  .init = __fzf_init,
  .deinit = __fzf_deinit,
  .items = exec_fzf_select_from_items,
  .items_v = exec_fzf_select_from_items_v,
  .qty = 0,
};
//////////////////////////////////////////////
//////////////////////////////////////////////




struct fzf_keybind_t {
  char *key, *cmd, *type, *desc;
};
struct fzf_exec_t {
  struct Vector          *input_options;
  struct Vector          *selected_options;
  struct Vector          *fzf_keybinds_v;
  struct Vector          *fzf_header_lines_v;
  struct StringBuffer    *fzf_header_lines_sb;
  struct StringBuffer    *fzf_keybinds_sb;
  struct StringFNStrings output_lines;
  char                   *fzf_keybinds_s;
  char                   **input_array;
  char                   *input_s;
  char                   *fzf_info;
  char                   *fzf_prompt;
  char                   *fzf_history_file;
  char                   *output_file;
  char                   *tempdir;
  char                   *header;
  char                   *fzf_cmd, *fzf_pointer, *fzf_marker;
  char                   *fzf_path;
  char                   *fzf_default_opts;
  char                   *fzf_default_command;
  char                   *env_path;
  char                   *sh_path;
  char                   **subprocess_cmd;
  int                    proc_result;
  int                    proc_exit_code;
  int                    height;
  int                    preview_size;
  char                   *preview_type;
  char                   *preview_cmd, *encoded_preview_cmd, *sub_preview_cmd, *sub_preview_cmd_file;
  char                   *query_s;
  int                    top_margin, bottom_margin, left_margin, right_margin;
  int                    top_padding, bottom_padding, left_padding, right_padding;
  char                   *options_file;
  char                   *options_file_content_s;
  char                   *input_lines_s;
  char                   *fzf_header_lines_s;
  char *border_label;
  int border_label_pos_number;
  char *border_label_pos_string;
  char *separator;
  char *border_style;

  reproc_t               *proc;
  reproc_options         reproc_options;
  bool                   debug_mode, select_multiple, fzf_reverse, header_first, cycle, border, ansi;
  size_t                 header_lines;
};

struct fzf_exec_t *exec_fzf_setup(void);
void exec_fzf_release(struct fzf_exec_t *fzf_exec);
int exec_fzf();

#endif
