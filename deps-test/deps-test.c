#include "deps-test.h"
#include <assert.h>
enum ExampleEvents {
  EVENT_START  = 100,
  EVENT_MIDDLE = 200,
  EVENT_END    = 300
};
struct FnArgs {
  int counter;
};


void work_fn(void *args){
  struct FnArgs *fn_args = (struct FnArgs *)args;

  sleep(1);
  printf("Counter: %d\n", fn_args->counter);

  free(fn_args);
}


static void on_start(void *event_data, void *context){
  printf("OnStart, data: %s context: %s\n", (char *)event_data, (char *)context);
}


static void on_end(void *event_data, void *context){
  printf("OnEnd, data: %s context: %s\n", (char *)event_data, (char *)context);
}


static void on_unhandled(int event_id, void *event_data, void *context){
  printf("OnUnhandled, did not set listener for event: %d data: %s context: %s\n", event_id, (char *)event_data, (char *)context);
}
#define TBL1        "\
\
┌───────────────────────────────┐\
│    Test suite  #Cases  Result │\
├───────────────────────────────┤\
│ 1  Table                       \
├───────────────────────────────┤\
│      End result              \
└───────────────────────────────┘\
\
"
#define SLEEP_US    100000


#define feed(x)          { do{                                                                                                   \
                             struct color_char ch = cansid_process(&state, x);                                                   \
                             if (false) DEBUG_PRINT((int)ch.ascii, .colorscheme = FORE_CYAN BACK_BLACK, .filestream = stdout);   \
                             if (true) DEBUG_PRINT((int)ch.style, .colorscheme  = FORE_YELLOW BACK_BLACK, .filestream = stdout); \
                             DEBUG_PRINT((char)ch.ascii, .colorscheme           = FORE_CYAN BACK_BLACK, .filestream = stdout);   \
                           }while (0); }

#define DEBUG_STATE()    { do {                                                                                                  \
                             if (false) {                                                                                        \
                               DEBUG_PRINT((int)state.style, .colorscheme      = FORE_BLUE BACK_BLACK, .filestream = stdout);    \
                               DEBUG_PRINT((int)state.state, .colorscheme      = FORE_BLUE BACK_BLACK, .filestream = stdout);    \
                               DEBUG_PRINT((int)state.next_style, .colorscheme = FORE_MAGENTA BACK_BLACK, .filestream = stdout); \
                             }                                                                                                   \
                           }while (0); }


void do_test_libspinner(){
  spinner_t *s = spinner_new(32);

  s->delay     = 100000;
  s->prefix    = "Running ";
  s->suffix    = " I'm a suffix";
  s->final_msg = "Complete!\n";
  spinner_start(s);
  sleep(2);
  spinner_stop(s);
  spinner_free(s);
}


void do_test_which(){
  char *name = "ls";
  char *path = (char *)which(name);

  printf("\n<WHICH>%s: %s\n\n", name, path ? path : "not found");

  name = "ls1";
  path = (char *)which(name);
  printf("\n<WHICH>%s: %s\n\n", name, path ? path : "not found");

  free(path);
}


void do_test_slug(){
  char *s0 = "foo b ar@-";
  char s01[32];

  sprintf(s01, "%s", s0);
  char *s1 = slug(s01);

  fprintf(stdout, "\nSLUG: '%s'->'%s'\n", s0, s01);
}


void do_test_cansid(void){
  struct cansid_state state;

  state = cansid_init();
  feed('\x1B');
  char *as = malloc(1024);

  DEBUG_STATE();
  as = "OK1";
  for (int i = 0; i < strlen(as); i++) {
    feed(as[i]);
  }
  as = "\x1b[31m\x1b[40mRED_BLACK\x1b[0m";
  for (int i = 0; i < strlen(as); i++) {
    feed(as[i]);
  }
  as = "\x1b[32mRED\x1b[0mRR";
  for (int i = 0; i < strlen(as); i++) {
    feed(as[i]);
  }
}


void do_test_progressbar(void){
  int         max     = 60 / 1;
  progressbar *smooth = progressbar_new("Smooth", max);

  for (int i = 0; i < max; i++) {
    usleep(SLEEP_US / 10);
    progressbar_inc(smooth);
  }
  progressbar_finish(smooth);

  progressbar *longlabel = progressbar_new("Three Second Task with a long label", 3);

  for (int i = 0; i < 3; i++) {
    progressbar_inc(longlabel);
    usleep(SLEEP_US / 10);
  }
  progressbar_finish(longlabel);

  progressbar *fast = progressbar_new("Fast", 20);

  for (int i = 0; i < 20; i++) {
    usleep(SLEEP_US / 10);
    progressbar_inc(fast);
  }
  progressbar_finish(fast);

  progressbar *custom = progressbar_new_with_format("Custom", max, "<.>");

  for (int i = 0; i < max; i++) {
    usleep(SLEEP_US / 10);
    progressbar_inc(custom);
  }
  progressbar_finish(custom);
}


void do_test_statusbar(void){
  statusbar *status = statusbar_new("Indeterminate");

  for (int i = 0; i < 30; i++) {
    usleep(SLEEP_US / 10);
    statusbar_inc(status);
  }
  statusbar_finish(status);

  statusbar *longStatus = statusbar_new("Status bar with a really long label");

  for (int i = 0; i < 10; i++) {
    usleep(SLEEP_US / 10);
    statusbar_inc(longStatus);
  }
  statusbar_finish(longStatus);

  statusbar *customStatus = statusbar_new_with_format("Custom", "(|)|");

  for (int i = 0; i < 30; i++) {
    usleep(SLEEP_US);
    statusbar_inc(customStatus);
  }
  statusbar_finish(customStatus);
}


int32_t FillFromURANDOM(uint8_t *out, size_t outlen){
  FILE *fpurandom = fopen("/dev/urandom", "r");

  if (!fpurandom) {
    return(-1);
  }
  int32_t bread = fread(out, 1, outlen, fpurandom);

  fclose(fpurandom);
  return(bread < outlen ? -1 : bread);
}


void demo_ansi_qrcode(){
  char secret[33] = { 0 };

  generate_random_secret(secret, 33, FillFromURANDOM);
  printf("Secret: %s\n", secret);
  char *qrcodeansi = create_totp_qrcode("Test", "Meow", secret);

  printf("\n----------------------------------------------------------------------------\n");
  printf("%s", qrcodeansi);
  printf("----------------------------------------------------------------------------\n");
  free(qrcodeansi);
}


void demo_totp_calculation(){
  char secret[33] = { 0 };
  char buf[512]   = { 0 };

  sprintf(buf, "%s", "abc123");
  size_t secretlen = base32decode(buf, strnlen(buf, 512),
                                  secret, 33);

  time_t now = time(0);
  int    otp = compute_totp(secret, secretlen, now, 30, 6);

  printf("OTP code>\n\tSecret:\t%s\n\tTOTP:\t%06d\n", buf, otp);
}


TEST test_statusbar(void){
  do_test_statusbar();
  PASS();
}


TEST test_progressbar(void){
  do_test_progressbar();
  PASS();
}


TEST test_totp(void){
  demo_totp_calculation();
  PASS();
}


TEST test_qrcode(void){
  demo_ansi_qrcode();
  PASS();
}


TEST test_spin(void){
  const int big_number = 1000000000 / 1;
  spinner   *s         = spin_new(utf8_pat1, "Working", UTF8_CHAR_WIDTH);
  int       x          = 0;
  int       working    = 1;

  while (working) {
    if (x == (big_number * .25)) {
      spin_upd_msg(s, "Part way through");
      spin_drw(s);
    }
    if (x == (big_number * .75)) {
      spin_upd_msg(s, "Getting close now");
      spin_drw(s);
    }
    if (x % 9999999 == 0) {
      spin_drw(s);
    }
    if (x++ > big_number) {
      working = 0;
    }
  }
  spin_del(s);
  printf("Done!\n");
  PASS();
}


TEST test_cansid(void){
  do_test_cansid();
}


TEST test_timestamp(void){
  int ts = (int)timestamp();

  DEBUG_PRINT(ts, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}


TEST test_libspinner(void){
  do_test_libspinner();
  PASS();
}


TEST test_which(void){
  do_test_which();
  PASS();
}


TEST test_slug(void){
  do_test_slug();
  PASS();
}


TEST test_debug_print(void){
  int  o  = 123;
  char *s = "abc123";

  DEBUG_PRINT(s, .colorscheme    = FORE_BLUE BACK_BLACK, .filestream = stdout);
  DEBUG_PRINT(o, .colorscheme    = FORE_BLACK BACK_WHITE, .filestream = stdout);
  DEBUG_PRINT("OK", .colorscheme = FORE_YELLOW BACK_BLACK, .filestream = stderr);
  PASS();
}

SUITE(test_time) {
  RUN_TEST(test_timestamp);
  PASS();
}
SUITE(test_spinner) {
  RUN_TEST(test_libspinner);
  RUN_TEST(test_spin);
  PASS();
}
SUITE(suite_totp) {
  RUN_TEST(test_totp);
  PASS();
}
SUITE(suite_qrcode) {
  RUN_TEST(test_qrcode);
  PASS();
}
SUITE(test_status) {
  RUN_TEST(test_statusbar);
  PASS();
}
SUITE(test_progress) {
  RUN_TEST(test_progressbar);
  PASS();
}

SUITE(test_path) {
  RUN_TEST(test_which);
  PASS();
}
SUITE(test_debug) {
  RUN_TEST(test_debug_print);
  PASS();
}
SUITE(test_parse) {
  RUN_TEST(test_cansid);
  PASS();
}
SUITE(test_string) {
  RUN_TEST(test_slug);
  PASS();
}
/////////////////////////////////////////
char JSON_TESTS_FILE[] = ".tests.json";
char *JSON_TESTS_CONTENT;


TEST process_json_lines(void){
  struct StringFNStrings LINES = stringfn_split_lines_and_trim(JSON_TESTS_CONTENT);

  free(JSON_TESTS_CONTENT);
  if (false) {
    DEBUG_PRINT(LINES.count, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  }
  for (int i = 0; i < LINES.count; i++) {
    if (strlen(LINES.strings[i]) < 2) {
      continue;
    }
    if (false) {
      DEBUG_PRINT(LINES.strings[i], .colorscheme = FORE_GREEN BACK_BLACK, .filestream = stdout);
    }
    JSON_Value  *Line        = json_parse_string(LINES.strings[i]);
    JSON_Object *LineObject  = json_object(Line);
    char        *suite_name  = json_object_get_string(LineObject, "suite");
    char        *binary_name = json_object_get_string(LineObject, "binary");
    if (false) {
      DEBUG_PRINT(suite_name, .colorscheme = FORE_GREEN BACK_BLACK, .filestream = stdout);
    }
    JSON_Array *Tests    = json_object_get_array(LineObject, "tests");
    size_t     tests_qty = json_array_get_count(Tests);
    if (false) {
      DEBUG_PRINT((int)tests_qty, .colorscheme = FORE_YELLOW BACK_BLACK, .filestream = stdout);
    }
    for (size_t i = 0; i < tests_qty; i++) {
      char *test_name = json_array_get_string(Tests, i);
      fprintf(stdout, "[%s] %15s %3lu/%lu  %12s\n",
              binary_name,
              suite_name,
              i + 1,
              tests_qty,
              test_name
              );
      free(test_name);
    }
    json_value_free(LineObject);
    free(suite_name);
    free(binary_name);
  }
  stringfn_release_strings_struct(LINES);
  PASS();
} /* process_json_lines */


void t_forever_my_program(void *context){
  dbg("t_forever_my_program", %s);
  if (context != NULL) {
    // do something with the context
  }

  usleep(1000 * 100);
  exit(0);
}


int t_forever_callback(void *context, const unsigned char started, int stat_loc){
  if (context != NULL) {
    // do something with the context
  }
  dbg(stat_loc, %d);
  dbg(started, %c);

  if (stat_loc == 0 || !started) {
    return(-1); // no more retries
  }
  dbg("t_forever_callback", %s);
  return(500); // wait 500 millies before next invocation, 0 for no wait.
}


TEST t_forever(void){
  void *context = NULL;

  // call 'my_program' and when it ends/crashes invoke it again, up
  // to 10 times and wait 250 millies between invocations.
  // counter will hold the amount of times 'my_program' was invoked.
  unsigned int counter = forever_with_options(
    t_forever_my_program, // function to invoke
    context,              // context that is passed to the function on every invocation
    5,                    // max amount of retries. 0 for unlimited retries.
    500                   // amount of millies to wait between invocations. 0 for no wait.
    );

  printf("Invoked %u time/s.\n", counter);

  // call 'my_program' and when it ends/crashes call the provided callback
  counter = forever_with_callback(t_forever_my_program, context, t_forever_callback);
  printf("Invoked %u time/s.\n", counter);

  PASS();
}


TEST t_eventemitter(void){
  // first create a new event emitter which will host the listeners and emit the events
  struct EventEmitter *event_emitter = eventemitter_new();

  // lets add few listeners.
  // we can add as many as we want
  // this listener will be triggered for the 'start' event
  // we are adding the same callback multiple times so for each event triggered
  // the callback will be called several times
  // The last param is a context that the specific listener will get each time its triggered
  // Each add function returns a unique ID which can be used to remove the listener
  unsigned int listener_id = eventemitter_add_listener(event_emitter, EVENT_START, on_start, "some context for start 1");

  eventemitter_add_listener(event_emitter, EVENT_START, on_start, "some context for start 2");
  eventemitter_on(event_emitter, EVENT_START, on_start, "some context for shorthand start"); // shorthand version

  // we can add listeners that are triggered once and are removed afterwards
  eventemitter_add_once_listener(event_emitter, EVENT_END, on_end, "end context 1");
  eventemitter_once(event_emitter, EVENT_END, on_end, "end context 2"); // shorthand

  // we can add listeners to any event triggered but no listeners were registered to it
  eventemitter_add_unhandled_listener(event_emitter, on_unhandled, "unhandled context 1");
  eventemitter_else(event_emitter, on_unhandled, "unhandled context 2"); // shorthand

  // trigger the 'start' event and pass some optional event data (any type) which
  // listeners will get in the callback
  eventemitter_emit(event_emitter, EVENT_START, "my start event data");

  // lets remove one of the 'start' listeners and emit it again
  eventemitter_remove_listener(event_emitter, EVENT_START, listener_id);
  eventemitter_emit(event_emitter, EVENT_START, "my second start event data");

  // lets trigger an event that no one listens to and see how the unhandled listeners are triggered
  eventemitter_emit(event_emitter, EVENT_MIDDLE, "middle event data");

  // lets trigger the 'end' event
  eventemitter_emit(event_emitter, EVENT_END, "end event data");
  // since all 'end' event listeners were added as 'once' they are no longer registered
  // so we will trigger it again and see how the unhandled listeners are invoked
  eventemitter_emit(event_emitter, EVENT_END, "end event data again");
  eventemitter_emit(event_emitter, EVENT_END, "end event data again 2");

  // once done with the emitter, we should release it
  // no need to release the listeners manually
  printf("Releasing Event Emitter\n");
  eventemitter_release(event_emitter);

  PASS();
} /* t_eventemitter */


TEST t_workqueue(void){
  printf("Library Examples:\n");

  // create new threaded work queue with default queue size
  // workqueue_new_with_options can be used to define custom queue size
  // each queue owns its own background thread and its possible to create many queues in parallel.
  struct WorkQueue *queue = workqueue_new();

  printf("Queue Size: %zu Backlog Size: %zu\n", workqueue_get_queue_size(queue), workqueue_get_backlog_size(queue));

  for (size_t index = 0; index < 20; index++) {
    struct FnArgs *args = malloc(sizeof(struct FnArgs));
    args->counter = index;

    if (!workqueue_push(queue, work_fn, args)) {
      printf("Failed to push work function to queue\n");
      free(args);
    }
  }

  printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queue));

  // wait for queue to finish, queue can still be used afterwards
  workqueue_drain(queue);
  printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queue));

  // release when done
  workqueue_release(queue);

  PASS();
}


TEST t_vector(void){
  struct Vector *vector = vector_new();

  // populate vector using multiple available functions
  vector_push(vector, "test push");
  vector_insert(vector, 1, "test insert");                          // shifts all items from index 1 forward
  vector_prepend(vector, "test prepend");
  char *previous_value = (char *)vector_set(vector, 1, "test set"); // replaces the item at index 1

  printf("Replaced value at index 1, old value: %s\n", previous_value);

  // can fetch any item
  char *value = (char *)vector_get(vector, 1);

  printf("Value at index 1: %s\n", value);
  value = (char *)vector_pop(vector);
  printf("Last Value: %s\n", value);

  // or fetch all items
  void **all_items = vector_to_array(vector);

  printf("First item: %s\n", (char *)all_items[0]);

  // can remove any item
  value = (char *)vector_remove(vector, 0); // shifts all items after index backward
  printf("Removed first item: %s\n", value);

  // modify the vector size
  size_t size     = vector_size(vector);
  size_t capacity = vector_capacity(vector);

  printf("Current size: %zu capacity: %zu\n", size, capacity);
  vector_shrink(vector);
  size     = vector_size(vector);
  capacity = vector_capacity(vector);
  printf("Current size: %zu capacity: %zu\n", size, capacity);
  vector_shrink(vector);
  size     = vector_ensure_capacity(vector, 100);
  capacity = vector_capacity(vector);
  printf("Current size: %zu capacity: %zu\n", size, capacity);

  // when we are done with the vector, we release it
  vector_release(vector);
  PASS();
} /* test_vector */


TEST test_occurrences(void){
  int qty;

  qty = occurrences("l", "hello");
  ASSERT_EQ(2, qty);
  qty = occurrences("L", "hello");
  ASSERT_EQ(0, qty);
  qty = occurrences(NULL, "hello");
  ASSERT_EQ(-1, qty);
  qty = occurrences("hello", NULL);
  ASSERT_EQ(-1, qty);
  PASS();
}


TEST test_str_replace(){
  char *replaced = str_replace("hello world", "hello", "goodbye");

  printf("%s\n", replaced);
  free(replaced);
  PASS();
}
SUITE(s_eventemitter){
  RUN_TEST(t_eventemitter);
  PASS();
}
SUITE(s_forever){
  RUN_TEST(t_forever);
  PASS();
}
SUITE(s_workqueue){
  RUN_TEST(t_workqueue);
  PASS();
}
SUITE(s_vector){
  RUN_TEST(t_vector);
  PASS();
}

SUITE(s_deps){
  RUN_TEST(test_occurrences);
  RUN_TEST(test_str_replace);
  PASS();
}


TEST read_json_file(void){
  DEBUG_PRINT(JSON_TESTS_FILE, .colorscheme    = FORE_BLUE BACK_BLACK, .filestream = stdout);
  JSON_TESTS_CONTENT                           = fsio_read_text_file(JSON_TESTS_FILE);
  DEBUG_PRINT(JSON_TESTS_CONTENT, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}
SUITE(tests) {
  RUN_TEST(read_json_file);
  RUN_TEST(process_json_lines);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(tests);
  RUN_SUITE(test_parse);
  RUN_SUITE(test_string);
  RUN_SUITE(test_debug);
  RUN_SUITE(test_time);
  RUN_SUITE(test_path);
  RUN_SUITE(test_progress);
  RUN_SUITE(suite_qrcode);
  RUN_SUITE(suite_totp);
  RUN_SUITE(test_spinner);
  RUN_SUITE(s_deps);
  RUN_SUITE(s_vector);
  RUN_SUITE(s_workqueue);
  RUN_SUITE(s_forever);
  RUN_SUITE(s_eventemitter);
  GREATEST_MAIN_END();
}
