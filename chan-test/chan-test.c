#include "chan-test.h"
#include <assert.h>
#include <ctype.h>
#include <ctype.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
typedef struct WORKER_T {
  int delay_ms;
  int thread_index;
} worker_t;
#define L                      log_debug
#define I                      log_info
#define E                      log_error
#define DISPATCHED_JOBS_QTY    10
#define JOBS_BUFFER_QTY        5
#define WORKER_SLEEP_MS        5
//////////////////////////////////////////////////////////////////////////
#define CREATE_JOBS_SUITE(                          \
    SUITE_NAME,                                     \
    QTY, WORKERS_QTY,                               \
    SEND_JOBS_DELAY_MS,                             \
    DISPATCHED_JOBS_QTY                             \
    )                                               \
  SUITE(SUITE_NAME){                                \
    size_t                                          \
      qty                 = QTY,                    \
      workers_qty         = WORKERS_QTY,            \
      send_jobs_delay_ms  = SEND_JOBS_DELAY_MS,     \
      dispatched_jobs_qty = DISPATCHED_JOBS_QTY     \
    ;                                               \
    RUN_TESTp(t_init_workers, (void *)workers_qty); \
    RUN_TESTp(t_chan_jobs_worker                    \
              , (void *)qty                         \
              , (void *)workers_qty                 \
              , (void *)send_jobs_delay_ms          \
              , (void *)dispatched_jobs_qty         \
              );                                    \
    RUN_TEST(t_free_workers);                       \
    PASS();                                         \
  }                                                 \
//////////////////////////////////////////////////////////////////////////
#define CREATE_JOBS_SUITES()                  \
  CREATE_JOBS_SUITE(s_chan_jobs, 1, 3, 5, 10) \
//////////////////////////////////////////////////////////////////////////
#define RUN_TEST_SUITES()    { do {                      \
                                 RUN_SUITE(s_chan_jobs); \
                               } while (0); }            \
//////////////////////////////////////////////////////////////////////////

pthread_t    worker_threads[10];
worker_t     *workers;
volatile int processed_jobs_qty = 0, processed_qtys[1024];
chan_t       *JOBS_CHANNEL, *DONE_CHANNEL;


void *worker(void *WID){
  void   *job;
  int    processed_qty = 0;
  size_t WORKER_ID     = (size_t)WID;

  L("%lu> Worker waing for jobs....", WORKER_ID);
  while (chan_recv(JOBS_CHANNEL, &job) == 0) {
    usleep(WORKER_SLEEP_MS * 1000 * WORKER_ID);
    processed_qtys[WORKER_ID]++;
    processed_qty++;
    I(
      "\t"
      AC_RESETALL AC_YELLOW "<%d>" AC_RESETALL
      "\t"
      AC_RESETALL AC_YELLOW_BLACK "#" AC_RESETALL
      AC_RESETALL AC_BRIGHT_YELLOW_BLACK AC_BOLD "%lu" AC_RESETALL
      AC_RESETALL AC_YELLOW_BLACK "" AC_RESETALL
      " #%lu OK."
      " : "
      AC_RESETALL AC_UNDERLINE AC_MAGENTA_BLACK "processed %d jobs" AC_RESETALL
      " <%d/%d> "
      AC_RESETALL AC_ITALIC AC_BLUE "(%d jobs in queue)" AC_RESETALL,
      getpid(),
      WORKER_ID,
      (size_t)job,
      processed_qtys[WORKER_ID],
      processed_qty,
      DISPATCHED_JOBS_QTY,
      chan_size(JOBS_CHANNEL)
      );
  }

  L(AC_RESETALL AC_GREEN_BLACK AC_ITALIC "%lu> received all jobs> " AC_RESETALL, WORKER_ID);
  chan_send(DONE_CHANNEL, (void *)WORKER_ID);
  return(NULL);
}


void init_workers(size_t WORKERS_QTY){
  workers = malloc(sizeof(worker_t) * WORKERS_QTY);
}


TEST t_free_workers(){
  if (workers) {
    free(workers);
  }
  workers = NULL;

  ASSERT_EQ(workers, NULL);
  PASS();
}


TEST t_init_workers(void *workers_qty){
  init_workers((size_t)workers_qty);
  ASSERT_NEQ(workers, NULL);

  PASS();
}


TEST t_chan_jobs_worker(void *buffer_qty,
                        void *workers_qty,
                        void *send_jobs_delay_ms,
                        void *dispatched_jobs_qty) {
  int res = -1;
  size_t
      BUFFER_QTY       = (size_t)buffer_qty,
    WORKERS_QTY        = (size_t)workers_qty,
    SEND_JOBS_DELAY_MS = (size_t)send_jobs_delay_ms,
    JOBS_QTY           = (size_t)dispatched_jobs_qty;

  ASSERT_GTE((int)WORKERS_QTY, 0);
  ASSERT_GTE((int)BUFFER_QTY, 0);

  JOBS_CHANNEL = chan_init(BUFFER_QTY);
  ASSERT_NEQ(JOBS_CHANNEL, NULL);

  DONE_CHANNEL = chan_init(0);
  ASSERT_NEQ(DONE_CHANNEL, NULL);

  I(
    "Scheduling Channel with "
    AC_RESETALL AC_BLUE_BLACK AC_BOLD AC_REVERSED "%lu" AC_RESETALL
    " buffered items "
    AC_RESETALL AC_CYAN_BLACK AC_BOLD AC_REVERSED "%lu" AC_RESETALL
    " workers ",
    BUFFER_QTY,
    WORKERS_QTY
    );

  processed_qtys[1] = 0;
  res               = pthread_create(&worker_threads[0], NULL, worker, (void *)1);
  ASSERT_EQ(0, res);

  processed_qtys[2] = 0;
  pthread_create(&worker_threads[1], NULL, worker, (void *)2);

  processed_qtys[5] = 0;
  pthread_create(&worker_threads[2], NULL, worker, (void *)5);

  ct_start(NULL);
  char *send_dur;

  for (size_t i = 1; i <= JOBS_QTY; i++) {
    usleep(SEND_JOBS_DELAY_MS * 1000);
    chan_send(JOBS_CHANNEL, (void *)i);
  }

  free(send_dur);
  //ct_set_unit(ct_MILLISECONDS);
  char *sent_dur = ct_stop("");

  chan_close(JOBS_CHANNEL);

  L("sent all jobs in %s. waiting for done signals......",
    sent_dur
    );

  for (int i = 0; i < WORKERS_QTY; i++) {
    chan_recv(DONE_CHANNEL, NULL);
  }

  I("done signals received.....waiting on threads to exit....");
  for (int i = 0; i < WORKERS_QTY; i++) {
    pthread_join(&worker_threads[i], NULL);
  }

  I("threads exited..disposing of channels......");
  chan_dispose(JOBS_CHANNEL);
  chan_dispose(DONE_CHANNEL);
  L("cleaned up jobs channels");

  PASS();
} /* t_chan_jobs_worker */
CREATE_JOBS_SUITES()
GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  //ct_set_unit(ct_MILLISECONDS);
  GREATEST_MAIN_BEGIN();
  RUN_TEST_SUITES();
  GREATEST_MAIN_END();
  return(0);
}

