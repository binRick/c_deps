////////////////////////////////////////////
#include "bestline/bestline.h"
////////////////////////////////////////////
#include "bestline-test/bestline-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
const char *BESTLINE_HISTORY_FILE = ".bestline-test-history.txt";

void completion(const char *buf, bestlineCompletions *lc) {
  if (buf[0] == 'h') {
    bestlineAddCompletion(lc, "ls");
    bestlineAddCompletion(lc, "hello");
    bestlineAddCompletion(lc, "hello there");
  }
}

char *hints(const char *buf, const char **ansi1, const char **ansi2) {
  if (!strcmp(buf, "l")) {
    *ansi1 = AC_YELLOW;
    *ansi2 = AC_GREEN;
    return("s");
  }
  if (!strcmp(buf, "hello")) {
    *ansi1 = "\033[35m";     /* magenta foreground */
    *ansi2 = "\033[39m";     /* reset foreground */
    return(" World");
  }
  return(NULL);
}
static char *BESTLINE;
static char *BESTLINE_PROMPTS[] = {
  "▶",
  "",
  "",
  "⬢",
  "🌞",
  "⭐",
  "→",
  "↪",
  "👉",
  "🔅",
  "👉",
  "🐧",
};
static char *BESTLINE_PREFIXES[] = {
  " ",
  " rick@ricks-Mac-Pro  ~/repos ",
  " rick@ricks-Mac-Pro  ~/.oh-my-zsh/themes   master ✚ ● ? ⍟1 ",
  "----------------------------------------------------------------------------------:: ~ »",
  "~ ➤",
  "> $",
  "[~]>",
  "[$]",
  "○",
  "[$] <>"
};
char        *BESTLINE_CURSORS[] = {
  AC_CURSOR_BLOCK,
  AC_CURSOR_BAR,
  AC_CURSOR_UNDER,
  AC_CURSOR_COLOR_RED,
};
size_t      BESTLINE_PROMPT_INDEX = 1;
size_t      BESTLINE_PREFIX_INDEX = 1;
size_t      BESTLINE_CURSOR_INDEX = 1;

char *generate_prompt(){
  asprintf(&BESTLINE,
           AC_RESETALL "%s" AC_RESETALL
           " " "%s" " "
           "%s",
           BESTLINE_PREFIXES[BESTLINE_PREFIX_INDEX],
           BESTLINE_PROMPTS[BESTLINE_PROMPT_INDEX],
           ""
           );
  return(BESTLINE);
}

////////////////////////////////////////////
TEST t_bestline_test(){
  char *line;

  fprintf(stdout, "%s", BESTLINE_CURSORS[BESTLINE_CURSOR_INDEX]);

  bestlineSetCompletionCallback(completion);
  bestlineSetHintsCallback(hints);
  bestlineHistoryLoad(BESTLINE_HISTORY_FILE);   /* Load the history at startup */

  while ((line = bestline(generate_prompt())) != NULL) {
    if (!strcmp(line, "i")) {
      BESTLINE_PROMPT_INDEX++;
      bestlineHistoryAdd(line);                   /* Add to the history. */
      bestlineHistorySave(BESTLINE_HISTORY_FILE); /* Save the history on disk. */
      fprintf(stdout, "Prompt Index: %lu\n", BESTLINE_PROMPT_INDEX);
    } else if (!strcmp(line, "p")) {
      BESTLINE_PREFIX_INDEX++;
      bestlineHistoryAdd(line);                   /* Add to the history. */
      bestlineHistorySave(BESTLINE_HISTORY_FILE); /* Save the history on disk. */
      fprintf(stdout, "Prefix Index: %lu\n", BESTLINE_PREFIX_INDEX);
    }else if (line[0] != '\0' && line[0] != '/') {
      fputs("echo: '", stdout);
      fputs(line, stdout);
      fputs("'\n", stdout);
      bestlineHistoryAdd(line);                   /* Add to the history. */
      bestlineHistorySave(BESTLINE_HISTORY_FILE); /* Save the history on disk. */
    } else if (!strncmp(line, "/mask", 5))
      bestlineMaskModeEnable();
    else if (!strncmp(line, "/unmask", 7))
      bestlineMaskModeDisable();
    else if (line[0] == '/') {
      fputs("Unreconized command: ", stdout);
      fputs(line, stdout);
      fputs("\n", stdout);
    }
    free(line);
  }
  PASS();
}

SUITE(s_bestline_test) {
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_bestline_test);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_bestline_test);
  GREATEST_MAIN_END();
}
