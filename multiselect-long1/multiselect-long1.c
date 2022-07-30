#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "multiselect-long1.h"

const char TITLE[] = "Select an Country";
const char *OPTIONS[] = {
    "o1", 
    "o2", 
    NULL,
};

typedef struct {
    int a;
    int b;
} Foo;

void pass_struct(Foo *in) { printf("A: %d\tB: %d\n", in->a, in->b); }


void pass_array(Foo **in, int len) {
    for(int i = 0; i < len; i++) {
        printf("A: %d\tB: %d\n", (*in+i)->a, (*in+i)->b);
    }
}

static char**makeCharArray(int size) {
    return calloc(sizeof(char*), size);
}

static void setArrayString(char **a, char *s, int n) {
    a[n] = s;
}

static void freeCharArray(char **a, int size) {
    int i;
    for (i = 0; i < size; i++)
        free(a[i]);
    free(a);
}


GoSlice argcvToSlice(int argc, const char** argv) {
  GoString* strs = malloc(sizeof(GoString) * argc);
  GoSlice ret;
  ret.cap = argc;
  ret.len = argc;
  ret.data = (void*)strs;
  for(int i = 0; i < argc; i++) {
    strs[i] = *((GoString*)malloc(sizeof(GoString)));
    strs[i].p = (char*)argv[i];
    strs[i].n = strlen(argv[i]);
  }

  return ret;
}

GoSlice cgo_str_slice(GoString **s) {
  int n = sizeof(s)/sizeof(s[0]);
  printf("%d\n", n);
  GoSlice l = {s, n, sizeof(GoString)*n};
  return l;
}


GoString cgo_str(char *s) {
  GoString id = {s, strlen(s)};
  return id;
}

int main(){
  GoString strs[] = {
    cgo_str("xxxxxxxxxxxxxx"), 
    cgo_str("yyyyyyyyyyyyyyy"),
    cgo_str("11111"),
    cgo_str("xxxxxxxxz"),
    cgo_str("a"),
  };
  char **responses = DoMultiSelectLong(
    (GoString){TITLE},
    (GoSlice){
        .data = strs, 
        .len = sizeof(strs)/sizeof(strs[0]), 
        .cap = sizeof(GoString)*sizeof(strs)/sizeof(strs[0]),
    }
  );
  int responses_qty = 0;
  char **n;
  for(n = responses, responses_qty = 0; *n != NULL && (responses_qty < 999); responses_qty++, *n++){
      fprintf(stdout,">%d:'%s'\n",responses_qty,*n);
  }    
  fprintf(stdout,"You chose %d items:\n",responses_qty);
  /*
  char **n1 = responses;
  int on = 0;
  while (on < responses_qty && *n1 != NULL) {
    printf (" - %s\n",  *n1++);
    on++;
  }    
  fprintf(stdout,"You chose %d Countries:\n",responses_qty);
  */


return(0);
}
/*
void _main(){
  int ia[] = {
      1,
      2,
      3,
      NULL,
  };
  GoSlice s = {
        .data = ia,
        .len = 4,
        .cap = 32,
  };
  char **responses = DoMultiSelectLong(
          (GoString){TITLE},
          ia
  );

  int responses_qty = 0;
  char **n = responses;
  while (*n != NULL) {
      responses_qty++;
      *n++;
  }    
  fprintf(stdout,"You chose %d items:\n",responses_qty);
  char **n1 = responses;
  int on = 0;
  while (on < responses_qty && *n1 != NULL) {
    printf (" - %s\n",  *n1++);
    on++;
  }    
  fprintf(stdout,"You chose %d Countries:\n",responses_qty);
}
*/
