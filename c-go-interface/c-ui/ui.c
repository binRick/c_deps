#include <stdio.h>
#include "c-ui/ui.h"
#include "go-ui/libui.h"

int main() {
  printf("C says: about to call Go...\n");
  UiMain();
  return 0;
}


