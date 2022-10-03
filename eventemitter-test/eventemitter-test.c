////////////////////////////////////////////

////////////////////////////////////////////
#include "eventemitter-test/eventemitter-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

enum ExampleEvents {
  EVENT_START  = 100,
  EVENT_MIDDLE = 200,
  EVENT_END    = 300
};

static void on_start(void *event_data, void *context){
  printf("OnStart, data: %s context: %s\n", (char *)event_data, (char *)context);
}

static void on_end(void *event_data, void *context){
  printf("OnEnd, data: %s context: %s\n", (char *)event_data, (char *)context);
}

static void on_unhandled(int event_id, void *event_data, void *context){
  printf("OnUnhandled, did not set listener for event: %d data: %s context: %s\n", event_id, (char *)event_data, (char *)context);
}

////////////////////////////////////////////
TEST t_eventemitter_test(){
  struct EventEmitter *event_emitter = eventemitter_new();

  // lets add few listeners.
  // we can add as many as we want
  // this listener will be triggered for the 'start' event
  // we are adding the same callback multiple times so for each event triggered
  // the callback will be called several times
  // The last param is a context that the specific listener will get each time its triggered
  // Each add function returns a unique ID which can be used to remove the listener
  unsigned int listener_id = eventemitter_add_listener(event_emitter, EVENT_START, on_start, "some contextfor start 1");

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
} /* t_eventemitter_test */

SUITE(s_eventemitter_test) {
  RUN_TEST(t_eventemitter_test);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_eventemitter_test);
  GREATEST_MAIN_END();
}
