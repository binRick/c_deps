#include "reproc-test.h"
#include "submodules/log.h/log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define NUM_CHILDREN    10
static int child(void);
static int parent();
static inline void millisleep(long ms);


TEST t_reproc_0(void){
  parent();
  PASS();
}

SUITE(s_reproc_0){
  t_reproc_0();
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_reproc_0);

  GREATEST_MAIN_END();
  return(0);
}


static inline void millisleep(long ms){
  nanosleep(&(struct timespec){
    .tv_sec  = (ms) / 1000,
    .tv_nsec = ((ms) % 1000L) * 1000000,
  }, NULL
            );
}


static int parent(){
  reproc_event_source children[NUM_CHILDREN] = { { 0 } };
  int                 r                      = -1;

  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_t   *process = reproc_new();

    const char *date_args[] = { "date", NULL };

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
      uint8_t output[4096];
      r = reproc_read(children[i].process, REPROC_STREAM_OUT, output, sizeof(output));
      if (r == REPROC_EPIPE) {
        children[i].process = reproc_destroy(children[i].process);
        continue;
      }

      if (r < 0) {
        goto finish;
      }
      output[r] = '\0';

      char msg[1024];
      sprintf(&msg, "<%d> " AC_RESETALL AC_YELLOW_BLACK AC_REVERSED AC_ITALIC "%s" AC_RESETALL, getpid(), stringfn_trim(output));
      log_debug("%s", msg);
    }
  }

finish:
  for (int i = 0; i < NUM_CHILDREN; i++) {
    reproc_destroy(children[i].process);
  }

  if (r < 0) {
    log_error("%s", reproc_strerror(r));
  }


  return(abs(r));
} /* parent */


static int child(void){
  srand(((unsigned int)getpid()));
  int ms = rand() % NUM_CHILDREN * 4; // NOLINT

  millisleep(ms);
  log_info("Process %i slept %i milliseconds.", getpid(), ms);
  return(EXIT_SUCCESS);
}

