#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "multi_select1.h"

const char TITLE[] = "Select an Country";


int main() {
  char **responses = DoMultiSelectArray(
            (GoString){
                TITLE, 
                strlen(TITLE)
                }
  );

  char **n;
  int responses_qty = 0;
  n = responses;
  while (*n != NULL) {
      responses_qty++;
      *n++;
  }    
  fprintf(stdout,"You chose %d Countries:\n",responses_qty);
  n = responses;
  while (*n != NULL) {
    printf ("%s\n",  *n++);
  }    
}