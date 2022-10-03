////////////////////////////////////////////

////////////////////////////////////////////
#include "which-test/which-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"

////////////////////////////////////////////
TEST t_which_test(){
  char *ls      = (char *)which("ls");
  char *ffmpeg  = (char *)which("ffmpeg");
  char *convert = (char *)which("convert");
  char *meson   = (char *)which("meson");
  char *sh      = (char *)which("sh");
  char *bash    = (char *)which("bash");
  char *env     = (char *)which("env");
  char *passh   = (char *)which("passh");
  char *ls1     = (char *)which("ls1");

  printf("PATH:        %s\n", getenv("PATH"));
  printf("\n<WHICH>%s: %s\n\n", "ls", ls ? ls : "not found");
  printf("\n<WHICH>%s: %s\n\n", "bash", bash ? bash : "not found");
  printf("\n<WHICH>%s: %s\n\n", "ffmpeg", ffmpeg ? ffmpeg : "not found");
  printf("\n<WHICH>%s: %s\n\n", "convert", convert ? convert : "not found");
  printf("\n<WHICH>%s: %s\n\n", "meson", meson ? meson : "not found");
  printf("\n<WHICH>%s: %s\n\n", "sh", sh ? sh : "not found");
  printf("\n<WHICH>%s: %s\n\n", "env", env ? env : "not found");
  printf("\n<WHICH>%s: %s\n\n", "passh", passh ? passh : "not found");
  printf("\n<WHICH>%s: %s\n\n", "ls1", ls1 ? ls1 : "not found");

  PASS();
}

SUITE(s_which_test) {
  RUN_TEST(t_which_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_which_test);
  GREATEST_MAIN_END();
}
