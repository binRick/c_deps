#include "c-libadder.h"
#include "libadder.h"
#include <stdio.h>

void go_string(void);

int adder(int a, int b) {
  printf(">libadder C says: about to call Go...\n");
  int total = GoAdder(1, 7);
  printf(">libadder C says: Go calculated our total as %i\n", total);
  return(total);
}
