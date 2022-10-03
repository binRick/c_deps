////////////////////////////////////////////

////////////////////////////////////////////
#include "microtar-test/microtar-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "microtar/src/microtar.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_microtar_read(void){
  //DO_WORK
  mtar_t        tar;
  mtar_header_t h;
  char          *p;

  /* Open archive for reading */
  mtar_open(&tar, "test.tar", "r");

  /* Print all file names and sizes */
  while ((mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD) {
    printf("%s (%d bytes)\n", h.name, h.size);
    mtar_next(&tar);
  }

  /* Load and print contents of file "test.txt" */
  mtar_find(&tar, "test.txt", &h);
  p = calloc(1, h.size + 1);
  mtar_read_data(&tar, p, h.size);
  printf("%s", p);
  free(p);

  /* Close archive */
  mtar_close(&tar);
  //BENCHMARK_SUMMARY(benchmark_microtar);
  PASS();
}

TEST t_microtar_write(void){
  mtar_t     tar;
  const char *str1 = "Hello world";
  const char *str2 = "Goodbye world";

  /* Open archive for writing */
  mtar_open(&tar, "test.tar", "w");

  /* Write strings to files `test1.txt` and `test2.txt` */
  mtar_write_file_header(&tar, "test1.txt", strlen(str1));
  mtar_write_data(&tar, str1, strlen(str1));
  mtar_write_file_header(&tar, "test2.txt", strlen(str2));
  mtar_write_data(&tar, str2, strlen(str2));

  /* Finalize -- this needs to be the last thing done before closing */
  mtar_finalize(&tar);

  /* Close archive */
  mtar_close(&tar);
  PASS();
}
SUITE(s_microtar_test) {
  RUN_TEST(t_microtar_read);
  RUN_TEST(t_microtar_write);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_microtar_test);
  GREATEST_MAIN_END();
}
