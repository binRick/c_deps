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
#include "exec-fzf-test/exec-fzf-test.h"
#include "exec-fzf/exec-fzf.h"
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
#include "ansi-utils/ansi-utils.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "exec-fzf-test/exec-fzf-test.h"
#include "submodules/log/log.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
//////////////////////////////////////////////
static void __attribute__((destructor)) __exec_fzf_test_destructor();

static void __attribute__((constructor)) __exec_fzf_test_constructor();

//////////////////////////////////////////////
TEST t_fzf_module1(void){
  struct Vector *v  = vector_new();
  size_t        qty = 5;
  char          *s[qty];

  for (size_t i = 0; i < qty; i++) {
    asprintf(&(s[i]), "%lld", timestamp());
    vector_push(v, (void *)s[i]);
  }
  module(fzf) * fzf = require(fzf);
  Dn(fzf->qty);
  fzf->items(vector_to_array(v), vector_size(v), "timestamp from array");
  fzf->items_v(v, "timestamp from vector");
  clib_module_free(fzf);
  PASS();
}

TEST t_fzf_select_from_vector(void){
  struct Vector *v  = vector_new();
  size_t        qty = 5;
  char          *s[qty];

  for (size_t i = 0; i < qty; i++) {
    asprintf(&(s[i]), "%lld", timestamp());
    vector_push(v, (void *)s[i]);
  }
  char *res = exec_fzf_select_from_items_v(v, "fingers");
  char *msg;

  asprintf(&msg, "Selected item: %s", res);
  PASSm(msg);
}

TEST t_fzf_select_from_array(void){
  size_t qty = 5;
  char   *items[qty];

  for (size_t i = 0; i < qty; i++)
    asprintf(&(items[i]), "%lld", timestamp());
  char *res = exec_fzf_select_from_items(items, qty, "fingers");
  char *msg;

  asprintf(&msg, "Selected item: %s", res);
  PASSm(msg);
}

TEST t_fzf_keybind_change_preview(void){
  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  struct fzf_keybind_t *kb1 = malloc(sizeof(struct fzf_keybind_t));
  struct fzf_keybind_t *kb2 = malloc(sizeof(struct fzf_keybind_t));
  {
    fe->header          = "my header 123444";
    fe->debug_mode      = true;
    fe->height          = 50;
    fe->select_multiple = true;
    fe->header          = "Preview Test- |ctrl+q: quit|";
  }
  {
    kb1->key  = "ctrl-n";
    kb1->type = "change-preview";
    kb1->cmd  = "echo n preview {}";
    kb1->desc = "preview test 1";
    vector_push(fe->fzf_keybinds_v, kb1);
  }
  {
    kb2->key  = "ctrl-p";
    kb2->type = "change-preview";
    kb2->cmd  = "echo p preview {}";
    kb1->desc = "preview test 2";
    vector_push(fe->fzf_keybinds_v, kb1);
    vector_push(fe->fzf_keybinds_v, kb2);
  }

  vector_push(fe->fzf_header_lines_v, (char *)"ctrl+n: preview test 1");
  vector_push(fe->fzf_header_lines_v, (char *)"ctrl+p: preview test 2");
  fe->preview_size = 50;
  fe->preview_type = "bottom";
  fe->preview_cmd  = "echo selected item {}";
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  int res = exec_fzf(fe);

  ASSERT_EQm("fzf process OK", res, 0);
  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);
  free(kb1);
  free(kb2);

  PASS();
} /* t_fzf_keybind */

TEST t_fzf_keybind_change_prompt(void){
  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  struct fzf_keybind_t *kb1 = malloc(sizeof(struct fzf_keybind_t));
  struct fzf_keybind_t *kb2 = malloc(sizeof(struct fzf_keybind_t));
  {
    fe->header          = "my header 123444";
    fe->debug_mode      = true;
    fe->height          = 50;
    fe->select_multiple = true;
    fe->header          = "Keybind Test- |ctrl+q: quit|";
  }
  {
    kb1->key  = "ctrl-n";
    kb1->type = "change-prompt";
    kb1->cmd  = "n prompt";
    kb1->desc = "preview test 1";
    vector_push(fe->fzf_keybinds_v, kb1);
  }
  {
    kb2->key  = "ctrl-p";
    kb2->type = "change-prompt";
    kb2->cmd  = "p prompt";
    kb2->desc = "preview test 2";
    vector_push(fe->fzf_keybinds_v, kb2);
  }

  vector_push(fe->fzf_header_lines_v, (char *)"ctrl+n: preview test 1");
  vector_push(fe->fzf_header_lines_v, (char *)"ctrl+p: preview test 2");
  fe->preview_size = 50;
  fe->preview_type = "bottom";
  fe->preview_cmd  = "echo selected item {}";
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  int res = exec_fzf(fe);

  ASSERT_EQm("fzf process OK", res, 0);
  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);
  free(kb1);
  free(kb2);

  PASS();
} /* t_fzf_keybind_change_prompt */

TEST t_fzf_keybind_preview(void){
  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  struct fzf_keybind_t *kb1 = malloc(sizeof(struct fzf_keybind_t));
  struct fzf_keybind_t *kb2 = malloc(sizeof(struct fzf_keybind_t));
  {
    fe->header          = "my header 123444";
    fe->debug_mode      = true;
    fe->height          = 50;
    fe->select_multiple = true;
    fe->header          = "Preview Test- |ctrl+q: quit|";
  }
  {
    kb1->key  = "ctrl-n";
    kb1->type = "preview";
    kb1->cmd  = "echo n preview {}";
    kb1->desc = "preview test 1";
    vector_push(fe->fzf_keybinds_v, kb1);
  }
  {
    kb2->key  = "ctrl-p";
    kb2->type = "preview";
    kb2->cmd  = "echo p preview {}";
    kb2->desc = "preview test 2";
    vector_push(fe->fzf_keybinds_v, kb1);
    vector_push(fe->fzf_keybinds_v, kb2);
  }

  vector_push(fe->fzf_header_lines_v, (char *)"ctrl+n: preview test 1");
  vector_push(fe->fzf_header_lines_v, (char *)"ctrl+p: preview test 2");
  fe->preview_size = 50;
  fe->preview_type = "bottom";
  fe->preview_cmd  = "echo selected item {}";
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  int res = exec_fzf(fe);

  ASSERT_EQm("fzf process OK", res, 0);
  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);
  free(kb1);
  free(kb2);

  PASS();
} /* t_fzf_keybind */

TEST t_fzf_preview(void){
  int               res = -1;

  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  fe->header          = "my header 123444";
  fe->debug_mode      = true;
  fe->height          = 50;
  fe->select_multiple = true;
  fe->header          = "Multiple Test";
  fe->preview_size    = 50;
  fe->preview_cmd     = "echo selected item {}";
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  res = exec_fzf(fe);
  ASSERT_EQm("fzf process OK", res, 0);
  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);

  PASS();
}

TEST t_fzf_multiple(void){
  int               res = -1;

  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  fe->header          = "my header 123444";
  fe->debug_mode      = false;
  fe->height          = 25;
  fe->select_multiple = true;
  fe->fzf_pointer     = "➤ ";
  fe->fzf_marker      = "○ ";
  fe->fzf_prompt      = "Select one or more Items ➤ ";
  fe->fzf_info        = "default";
  fe->header          = "Multiple Test";
  fe->preview_size    = 50;
  asprintf(&(fe->preview_cmd), "%s -g %dx%d -pk -o /tmp/png/window-{}.ansi /tmp/png/window-{}.png && echo kitty +kitten icat --align=right --place 40x20@100x20 --scale-up /tmp/png/window-{}.png && qoiconv /tmp/png/window-{}.png /tmp/png/window-{}.qoi && qoirconv /tmp/png/window-{}.png /tmp/png/window-{}.qoir && qoirview /tmp/png/window-{}.qoir",
           which("timg"),
           120, 40
           );
  vector_push(fe->input_options, "162");
  vector_push(fe->input_options, "327");
  vector_push(fe->input_options, "343");
  vector_push(fe->input_options, "1174");
  vector_push(fe->input_options, "1310");

  res = exec_fzf(fe);
  ASSERT_EQm("fzf process OK", res, 0);
  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);

  PASS();
}

TEST t_fzf_short(void){
  int               res = -1;

  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  fe->header       = "my header 123444";
  fe->debug_mode   = false;
  fe->height       = 25;
  fe->preview_size = 0;
  fe->fzf_pointer  = "->";
  fe->fzf_marker   = "* ";
  fe->fzf_info     = "inline";
  fe->header       = "[Short Test]";
  fe->fzf_prompt   = "Select an Item > ";
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  res = exec_fzf(fe);
  ASSERT_EQm("fzf process OK", res, 0);

  //log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);

  PASS();
}

TEST t_fzf_single(void){
  int               res = -1;

  struct fzf_exec_t *fe = exec_fzf_setup();

  ASSERT_NEQm("fzf setup OK", fe, NULL);
  fe->header       = "my header 123444";
  fe->debug_mode   = true;
  fe->height       = 50;
  fe->preview_size = 0;
  fe->header       = "Single Test";
  vector_push(fe->input_options, "option 1");
  vector_push(fe->input_options, "option 2");
  vector_push(fe->input_options, "option 3");
  vector_push(fe->input_options, "option wow............");

  res = exec_fzf(fe);
  ASSERT_EQm("fzf process OK", res, 0);

  log_info("Selected %lu/%lu options", vector_size(fe->selected_options), vector_size(fe->input_options));
  exec_fzf_release(fe);

  PASS();
}

SUITE(s_fzf_v2){
  RUN_TEST(t_fzf_select_from_array);
  RUN_TEST(t_fzf_select_from_vector);
}
SUITE(s_fzf_module){
  RUN_TEST(t_fzf_module1);
}
SUITE(s_fzf_basic){
  RUN_TEST(t_fzf_short);
  RUN_TEST(t_fzf_single);
  RUN_TEST(t_fzf_multiple);
  RUN_TEST(t_fzf_preview);
  RUN_TEST(t_fzf_keybind_preview);
  RUN_TEST(t_fzf_keybind_change_prompt);
  RUN_TEST(t_fzf_keybind_change_preview);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
    RUN_SUITE(s_fzf_basic);
    RUN_SUITE(s_fzf_v2);
    RUN_SUITE(s_fzf_module);
  }
  GREATEST_MAIN_END();
  return(0);
}

static void __attribute__((constructor)) __exec_fzf_test_constructor(){
}
static void __attribute__((destructor)) __exec_fzf_test_destructor(){
#ifdef DEBUG_MEMORY
  fprintf(stderr, "<%d> [%s] Checking for memory leaks\n", getpid(), __FUNCTION__);
  print_allocated_memory();
#endif
}
