#include <stdio.h>
#include <string.h>
#include "multi_select0.h"

const char TITLE[] = "Select an Item";

int main() {
    char *response = DoMultiSelect(
            (GoString){
                TITLE, 
                strlen(TITLE)
                }
    );
    fprintf(stdout,"\n[c] you chose: '%s'\n",response);
}
