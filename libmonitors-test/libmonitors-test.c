////////////////////////////////////////////

////////////////////////////////////////////
#include "libmonitors-test/libmonitors-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_libmonitors/src/monitors.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

void print_mode(struct libmonitors_mode *mode){
  printf("%ix%i @ %f Hz", mode->width, mode->height, mode->refresh);
  if (mode == mode->monitor->current_mode)
    printf(" CURRENT");
  printf("\n");
}

void print_monitor(struct libmonitors_monitor *monitor){
  printf("Monitor %s (%ix%i)", monitor->name, monitor->width, monitor->height);
  if (monitor->primary)
    printf(" PRIMARY");

  printf("\n");
  for (int i = 0; i < monitor->mode_count; ++i) {
    printf("  %i: ", i);
    print_mode(&monitor->modes[i]);
  }
}

////////////////////////////////////////////
TEST t_libmonitors_test(){
  if (!libmonitors_init()) {
    fputs("Failed to connect to X server\n", stderr);
    FAIL();
  }

  int                        count;
  struct libmonitors_monitor **monitors;
  if (!libmonitors_detect(&count, &monitors)) {
    fputs("Failed to detect monitors\n", stderr);
    FAIL();
  }

  printf("Detected %i monitors:\n", count);
  for (int i = 0; i < count; ++i)
    print_monitor(monitors[i]);

  libmonitors_free_monitors(count, monitors);
  libmonitors_deinit();
  PASS();
}

SUITE(s_libmonitors_test) {
  RUN_TEST(t_libmonitors_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_libmonitors_test);
  GREATEST_MAIN_END();
}
