////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "fancy-progress-test/fancy-progress-test.h"
#include "fancy-progress/src/fancy-progress.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define ROUNDS           150
#define STRINGS_COUNT    10
int               SLEEP_MS = 50;
////////////////////////////////////////////
static const char *strings[] = {
  "Lorem ipsum dolor sit amet",
  "Consectetur adipiscing elit",
  "Vivamus faucibus sagittis dui, tincidunt rhoncus mi",
  "Fringilla sollicitudin. Donec eget sagittis",
  "Quam, vitae fringilla nisl",
  "Donec dolor justo, hendrerit sed accumsan id, sodales",
  "Eu odio",
  "Nunc vehicula hendrerit risus, vel condimentum dui rutrum sed.",
  "Quisque metus enim, pellentesque nec nibh sit amet.",
  "Commodo molestie diam."
};

TEST t_fancy_progress_test(){
  int i, r;

  fancy_progress_start();

  // just echoes random strings and updates the progress bar
  srand(time(NULL));
  for (i = 0; i <= ROUNDS; i++) {
    r = rand() % STRINGS_COUNT;
    fprintf(stdout, "%s...\n", strings[r]);
    fancy_progress_step(((float)i / ROUNDS) * 100);
    usleep(SLEEP_MS * 1000);
  }

  usleep(500 * 1000);

  fancy_progress_stop();

  PASS();
}

SUITE(s_fancy_progress_test) {
  RUN_TEST(t_fancy_progress_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
    RUN_SUITE(s_fancy_progress_test);
  }
  GREATEST_MAIN_END();
}
