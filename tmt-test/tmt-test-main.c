#define DEV_MODE    true
#include "tmt-test.h"
#include <assert.h>
#define ROWS        2
#define COLS        6
unsigned int callbacks_qty;

void callback(tmt_msg_t m, TMT *vt, const void *a, void *p);

void printTerminal(TMT *vt);

int tmt_test_main(){
  char   *l = NULL;
  size_t n;

  TMT    *vt = tmt_open(ROWS, COLS, callback, NULL, NULL);

  assert(vt != NULL);

  while (getline(&l, &n, stdin) != -1) {
    tmt_write(vt, l, 0);
  }

  if (DEV_MODE) {
    tmt_write(vt, "\033[0;0H", 0);         //Bring cursor to (0,0).
    tmt_write(vt, "\033[2J", 0);           //Clear entire terminal virtual screen
    tmt_write(vt, TMT_KEY_HOME, 0);
    tmt_write(vt, "WENT HOME\n", 0);
  }

  tmt_close(vt);
  free(l);
  printf(AC_RESETALL AC_REVERSED AC_BRIGHT_YELLOW AC_BOLD "\n%d %s\n" AC_RESETALL, callbacks_qty, "x");
  return(EXIT_SUCCESS);
}

void callback(tmt_msg_t m, TMT *vt, const void *a, void *p){
  callbacks_qty++;
  const TMTSCREEN *s = tmt_screen(vt);
  const TMTPOINT  *c = tmt_cursor(vt);

  switch (m) {
  case TMT_MSG_CURSOR:
    if (false) {
      puts(">");
    }

    char *cstate;
    if (((const char *)a)[0] == 't') {
      cstate = strdup("displayed");
    } else{
      cstate = strdup("hidden");
    }

    fprintf(stderr,
            AC_RESETALL AC_REVERSED AC_BRIGHT_YELLOW "Cursor Moved! cursor is now at %zd,%zd and is" AC_RESETALL
            AC_RESETALL " " AC_RESETALL
            AC_RESETALL AC_REVERSED AC_BRIGHT_MAGENTA "%s" AC_RESETALL
            AC_RESETALL " " AC_RESETALL
            AC_RESETALL "\n" AC_RESETALL,
            c->r,
            c->c,
            cstate
            );
    break;

  case TMT_MSG_BELL:
    printf(
      AC_RESETALL AC_BRIGHT_RED "Bell Rang!\n" AC_RESETALL
      );
    break;

  case TMT_MSG_UPDATE:
    printTerminal(vt);
    break;

  case TMT_MSG_ANSWER:
    printf("Terminal answered %s\n", (const char *)a);
    break;

  case TMT_MSG_MOVED:
    printf(
      AC_RESETALL AC_BRIGHT_RED "Cursor is now at %zdx%zd\n" AC_RESETALL,
      c->r + 1,
      c->c + 1
      );
    break;
  } /* switch */
}   /* callback */

void printTerminal(TMT *vt){
  const TMTSCREEN *s                = tmt_screen(vt);
  const TMTPOINT  *c                = tmt_cursor(vt);
  unsigned int    qty_cells_printed = 0;

  for (size_t r = 0; r < s->nline; r++) {
    if (!s->lines[r]->dirty) {
      continue;
    }

    for (size_t c = 0; c < s->ncol; c++) {
      printf(
        AC_RESETALL AC_REVERSED AC_BLUE "Contents of" AC_RESETALL
        AC_RESETALL " " AC_RESETALL
        AC_RESETALL AC_BRIGHT_BLUE "%zdx%zd: " AC_RESETALL
        AC_RESETALL AC_BRIGHT_YELLOW "%c" AC_RESETALL
        AC_RESETALL " " AC_RESETALL
        AC_RESETALL "(%s|%s underline|%s reverse|%s dim)" AC_RESETALL
        AC_RESETALL "(fg:%d|bg:%d)\n" AC_RESETALL,
        r + 1, c + 1,
        s->lines[r]->chars[c].c,
        s->lines[r]->chars[c].a.bold ? AC_RESETALL AC_REVERSED AC_GREEN "Bold" AC_RESETALL : AC_RESETALL AC_WHITE "Unbold" AC_RESETALL,
        s->lines[r]->chars[c].a.underline ? "is" : "is not",
        s->lines[r]->chars[c].a.reverse ? "is" : "is not",
        s->lines[r]->chars[c].a.dim ? "is" : "is not",
        (int)(s->lines[r]->chars[c].a.fg),
        (int)(s->lines[r]->chars[c].a.bg)
        );
      qty_cells_printed++;
    }
  }
  printf(
    AC_RESETALL AC_BRIGHT_GREEN AC_REVERSED "%d %s" AC_RESETALL
    AC_RESETALL "\n" AC_RESETALL,
    qty_cells_printed,
    "x"

    );
  tmt_clean(vt);
} /* printTerminal */
