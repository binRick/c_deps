#include <stdbool.h>
#define DEBUG_MEMORY_ENABLED    true
#include "introspect.h"
#include "submodules/log.h/log.h"
#include "submodules/progress.c/progress.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//////////////////////////////////////////////
#define NUM_CHILDREN        1
#define MAX_OUTPUT_BYTES    1024 * 1024
#define D                   log_debug
#define E                   log_error
//////////////////////////////////////////////
#ifdef DEBUG_MEMORY_ENABLED
#include "submodules/debug-memory/debug_memory.h"
#endif


static void db_progress_start(progress_data_t *data) {
  assert(data);
  fprintf(stdout,
          AC_HIDE_CURSOR
          AC_RESETALL AC_GREEN AC_ITALIC "Processing" AC_RESETALL
          AC_RESETALL " "
          AC_RESETALL AC_BLUE AC_REVERSED AC_BOLD "%d"
          AC_RESETALL " "
          AC_RESETALL AC_GREEN AC_ITALIC "JSON Lines" AC_RESETALL
          "\n",
          data->holder->total
          );
  progress_write(data->holder);
}


static void db_progress(progress_data_t *data) {
  progress_write(data->holder);
}


static void db_progress_end(progress_data_t *data) {
  fprintf(stdout,
          AC_SHOW_CURSOR
          AC_RESETALL "\n"
          AC_GREEN AC_REVERSED AC_BOLD "Complete" AC_RESETALL
          "\n"
          );
}


void iterate_targets(ee_t *ee, JSON_Array *A){
  JSON_Value  *V = json_value_init_object();
  JSON_Object *O = json_value_init_object();
  char        *name, *type;

  for (size_t i = 0; i < json_array_get_count(A); i++) {
    V = json_array_get_value(A, i);
    O = json_array_get_object(A, i);
    size_t props_qty = json_object_get_count(O);
    assert(json_value_get_type(V) == JSONObject);
    type = json_object_get_string(O, "type");
    if (ee_listener_count(ee, type) > 0) {
      ee_emit(ee, type, V);
    }else{
      E("NOT HANDLED> type: '%s' qty:%d", type, ee_listener_count(ee, type));
    }
  }
  json_value_free(V);
}


JSON_Array *parse_execution_result(char *OUTPUT){
  JSON_Array *A = NULL;

  assert(strlen(OUTPUT) > 0);
  JSON_Value *V = json_parse_string(OUTPUT);

  assert(V != NULL);
  assert(json_value_get_type(V) == JSONArray);

  A = json_value_get_array(V);
  assert(A != NULL);
  size_t qty = json_array_get_count(A);

  assert(qty > 0);
  //log_debug("output is %lub and %lu properties", strlen(OUTPUT), json_array_get_count(A));
  //D("parse........%lu", json_array_get_count(A));
  return(A);
}


char *execute_processes(char *MESON_BUILD_FILE){
  uint8_t             output[MAX_OUTPUT_BYTES];
  reproc_event_source children[NUM_CHILDREN] = { { 0 } };
  int                 r                      = -1;

  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[] = {
      "meson", "introspect", "--targets", MESON_BUILD_FILE,
      NULL
    };

    r = reproc_start(process, date_args, (reproc_options){ .nonblocking = true });
    if (r < 0) {
      goto finish;
    }

    children[i].process   = process;
    children[i].interests = REPROC_EVENT_OUT;
  }

  for ( ;;) {
    r = reproc_poll(children, NUM_CHILDREN, REPROC_INFINITE);
    if (r < 0) {
      r = r == REPROC_EPIPE ? 0 : r;
      goto finish;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
      if (children[i].process == NULL || !children[i].events) {
        continue;
      }
      r = reproc_read(children[i].process, REPROC_STREAM_OUT, output, sizeof(output));
      if (r == REPROC_EPIPE) {
        children[i].process = reproc_destroy(children[i].process);
        continue;
      }

      if (r < 0) {
        goto finish;
      }
      output[r] = '\0';

      if (false) {
        char msg[strlen(output) + 1024];
        sprintf(&msg, "<%d> " AC_RESETALL AC_YELLOW_BLACK AC_REVERSED AC_ITALIC "%s" AC_RESETALL, getpid(), stringfn_trim(output));
        log_debug("%s", msg);
      }
    }
  }

finish:
  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_destroy(children[i].process);
  }

  if (r < 0) {
    log_error("%s", reproc_strerror(r));
  }

  char *o = malloc(strlen(output));

  sprintf(o, "%s", stringfn_trim(output));
  //free(o);
  return(o);
} /* execute_processes */
