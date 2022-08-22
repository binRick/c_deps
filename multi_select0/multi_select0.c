#include "multi_select0.h"
#include <stdio.h>
#include <string.h>

const char TITLE[] = "Select an Item";

int main() {
  char *response = DoMultiSelect(
    (GoString){
    TITLE,
    strlen(TITLE)
  }
    );

  fprintf(stdout, "\n[c] you chose: '%s'\n", response);
}
