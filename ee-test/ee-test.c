#include "ee-test.h"
int ee_main(void);

int ee_main_once(void);

int ee_main_loop(void);

void on_added_new_listener(void *arg);

ee_t *EE;
#define LOOP_LIM    10
#define L           log_info

void on_hello(void *arg);

void on_hi(void *arg);

TEST test_logh(void){
  log_info("logging an info message");
  log_warn("logging a warn message");
  log_debug("logging a debug message");
  log_error("logging an error %d", 123);
  L("xxxxxxxxxxxx %s", "2222222222");
  PASS();
}

TEST test_ee_loop(void){
  ee_main_loop();
  PASS();
}

TEST test_ee_once(void){
  ee_main_once();
  PASS();
}

TEST test_ee(void){
  ee_main();
  PASS();
}

SUITE(suite_ee_once) {
  test_ee_once();
  PASS();
}
SUITE(suite_logh) {
  test_logh();
  PASS();
}
SUITE(suite_ee_loop) {
  test_ee_loop();
  PASS();
}
SUITE(suite_ee) {
  test_ee();
  PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(suite_logh);
  RUN_SUITE(suite_ee);
  RUN_SUITE(suite_ee_once);
  RUN_SUITE(suite_ee_loop);

  GREATEST_MAIN_END();
  return(0);
}

void on_added_new_listener(void *arg) {
  ee_new_listener_t *listener;

  listener = (ee_new_listener_t *)arg;
  L("New listener added for event '%s'.", listener->name);
}

int ee_main_once(void) {
  const char *event_hello = "hello";
  const char *event_hi    = "hi";

  EE = ee_new();
  ee_once(EE, event_hi, on_hi);
  assert(1 == ee_listener_count(EE, event_hi));
  ee_emit(EE, event_hi, "world");
  assert(0 == ee_listener_count(EE, event_hi));
  ee_emit(EE, event_hi, "world"); /* => nothing happens */
  return(0);
}

int ee_main_loop(void) {
  const char *event_hello = "hello";
  const char *event_hi    = "hi";

  EE = ee_new();
  ee_on(EE, EE_NEW_LISTENER, on_added_new_listener);
  ee_on(EE, event_hello, on_hello);
  ee_once(EE, event_hi, on_hi);
  for (int i = 0; i < LOOP_LIM; i++) {
    ee_emit(EE, event_hello, "world");
    ee_emit(EE, event_hi, "world");
  }
}

void on_hello(void *arg) {
  char *s = (char *)arg;

  L("Invoked `on_hello` with  '%s'", s);
}

void on_hi(void *arg) {
  char *s = (char *)arg;

  L("Invoked `on_hi` with  '%s'", s);
}

int ee_main(void) {
  const char *event_hello = "hello";
  const char *event_hi    = "hi";

  EE = ee_new();

  ee_on(EE, EE_NEW_LISTENER, on_added_new_listener);

  assert(0 == ee_listener_count(EE, event_hello));

  /* subscribe "hello" indefinitely, "hi" only once */
  ee_on(EE, event_hello, on_hello);
  ee_once(EE, event_hi, on_hi);

  L("ee_listener_count,event_hello->%d", ee_listener_count(EE, event_hello));
  assert(1 == ee_listener_count(EE, event_hello));
  assert(1 == ee_listener_count(EE, event_hi));

  ee_emit(EE, event_hello, "world");
  ee_emit(EE, event_hi, "world");

  assert(1 == ee_listener_count(EE, event_hello));
  assert(0 == ee_listener_count(EE, event_hi));

  ee_emit(EE, event_hello, "world");
  ee_emit(EE, event_hi, "world"); /* => nothing happens */

  ee_remove_listener(EE, event_hello, on_hello);
  assert(0 == ee_listener_count(EE, event_hello));

  ee_emit(EE, event_hello, "world"); /* => nothing happens */

  return(0);
}
