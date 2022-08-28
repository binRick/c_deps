#include <stdio.h>
#include "libhello.h"

void go_string(void);


int main() {
  go_string();
  return 0;
}

// Callback function to be called from Go
void CallbackInC(char *go_str) {
    printf("CallbackInC(): %s\n", go_str);
    GoFreeString(go_str); // Release the Go string
}



void go_string(void){

    {
        char *go_str = GoStringFromGo();
        printf("GoStringFromGo(): %s\n", go_str);
        GoFreeString(go_str); // Release the Go string
    }
    {
        GoStringToGo("Calling from C");
    }
    {
        Demo_Array *go_array = GoArrayFromGo();
        printf("GoArrayFromGo():");
        int i;
        for(i=0; i < go_array->len; i++) {
            printf(" %d", ( (int *)(go_array->data) )[i]);
        }
        printf("\n");
        GoFreeArray(go_array); // Release the Demo_Array
    }

    // Pass array to a Go library function
    {
        int c_array[] = { 4, 5, 6 };
        // Create a Demo_Array wrapper for the native C array
        Demo_Array go_array = { c_array, sizeof(c_array)/sizeof(c_array[0]) };
    }
    {
        GoFunctionToGo(&CallbackInC);
    }

    // Receive a Go callback function and call it from here
    {
        void (*go_ptr)() = GoFunctionFromGo();
        (go_ptr)("Calling from C");
    }    
}
