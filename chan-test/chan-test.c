#include "ansicodes.h"
#define L                      log_debug
#define DISPATCHED_JOBS_QTY    100
#define JOBS_BUFFER_QTY        10
#define WORKER_SLEEP_MS        50
#include "chan-test.h"
#include <assert.h>
#include <ctype.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

volatile int processed_jobs_qty = 0;
volatile int processed_qtys[1024];
chan_t       *jobs;
chan_t       *done;


void *worker(void *WID){
  void   *job;
  int    processed_qty = 0;
  size_t WORKER_ID     = (size_t)WID;

  L("%lu> Worker waing for jobs....", WORKER_ID);
  while (chan_recv(jobs, &job) == 0) {
    usleep(WORKER_SLEEP_MS * 1000 * WORKER_ID);
    processed_qtys[WORKER_ID]++;
    processed_qty++;
    L(AC_RESETALL AC_YELLOW "<%lu>" AC_RESETALL " #%lu OK. processed %d jobs <%d/%d> (%d jobs in queue)",
      WORKER_ID, (size_t)job,
      processed_qtys[WORKER_ID],
      processed_qty,
      DISPATCHED_JOBS_QTY,
      chan_size(jobs)
      );
  }

  L(AC_RESETALL AC_GREEN_BLACK AC_ITALIC "%lu> received all jobs> " AC_RESETALL, WORKER_ID);
  chan_send(done, (void *)WORKER_ID);
  return(NULL);
}

pthread_t th[10];


TEST t_chan_jobs_worker(void){
  jobs = chan_init(JOBS_BUFFER_QTY);
  done = chan_init(0);


  processed_qtys[1] = 0;
  pthread_create(&th[0], NULL, worker, (void *)1);

  processed_qtys[2] = 0;
  pthread_create(&th[1], NULL, worker, (void *)2);

  processed_qtys[5] = 0;
  pthread_create(&th[2], NULL, worker, (void *)50);

  for (int i = 1; i <= DISPATCHED_JOBS_QTY; i++) {
    chan_send_int(jobs, i);
    log_info("          sent job #%d/%d", i, DISPATCHED_JOBS_QTY);
  }

  chan_close(jobs);
  L("sent all jobs.waiting for done signals......");

  chan_recv(done, NULL);
  chan_recv(done, NULL);
  chan_recv(done, NULL);

  log_error("done signals received.....waiting on threads to exit....");
  pthread_join(&th[0], NULL);
  pthread_join(&th[1], NULL);
  pthread_join(&th[2], NULL);

  log_error("threads exited..disposing of channels......");
  chan_dispose(jobs);
  chan_dispose(done);
  L("cleaned up jobs channels");

  PASS();
}


GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  (void)argc; (void)argv;
  GREATEST_MAIN_BEGIN();
  RUN_TEST(t_chan_jobs_worker);
  GREATEST_MAIN_END();
  return(0);
}

