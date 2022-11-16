
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "c_workqueue/include/workqueue.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "workqueue-test/workqueue-test.h"

struct FnArgs {
  int counter;
};

void work_fn(void *);

void work_fn(void *args){
  struct FnArgs *fn_args = (struct FnArgs *)args;

  sleep(1);
  printf("Counter: %d\n", fn_args->counter);

  free(fn_args);
}

TEST t_workqueue_test1(){
  struct WorkQueue *queues[5];

  for (size_t wq = 0; wq < 5; wq++) {
    queues[wq] = workqueue_new_with_options(10, NULL);

    printf("Queue Size: %zu Backlog Size: %zu\n", workqueue_get_queue_size(queues[wq]), workqueue_get_backlog_size(queues[wq]));

    for (size_t index = 0; index < 5; index++) {
      struct FnArgs *args = malloc(sizeof(struct FnArgs));
      args->counter = index;

      if (!workqueue_push(queues[wq], work_fn, args)) {
        printf("Failed to push work function to queue\n");
        free(args);
      }
    }
  }

  for (size_t wq = 0; wq < 5; wq++)
    printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queues[wq]));

  // wait for queue to finish, queue can still be used afterwards
  for (size_t wq = 0; wq < 5; wq++)
    workqueue_drain(queues[wq]);
  for (size_t wq = 0; wq < 5; wq++)
    printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queues[wq]));

  // release when done
  for (size_t wq = 0; wq < 5; wq++)
    workqueue_release(queues[wq]);
  PASS();
}

SUITE(s_workqueue_test) {
  RUN_TEST(t_workqueue_test1);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_workqueue_test);
  GREATEST_MAIN_END();
}
