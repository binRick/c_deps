////////////////////////////////////////////
#include <fcntl.h>
////////////////////////////////////////////
#include "get-next-line-test/get-next-line-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "get_next_line/get_next_line.h"

////////////////////////////////////////////
TEST t_get_next_line_test(){
  char *line;
  int  fd;

  fd = open("/etc/passwd", O_RDONLY);
  while (get_next_line(fd, &line) == 1) {
    printf("%s\n", line);
    free(line);
  }
  PASS();
}

SUITE(s_get_next_line_test) {
  RUN_TEST(t_get_next_line_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_get_next_line_test);
  GREATEST_MAIN_END();
}
