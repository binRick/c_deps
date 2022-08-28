#include <stdio.h>
#include "c-libadder/c-libadder.h"

void go_string(void);


int main() {
  printf(">c-call-libadder says: about to call C...\n");
  int total = adder(23, 115);
  printf("C says: C calculated our total as %i\n", total);
  return 0;
}


