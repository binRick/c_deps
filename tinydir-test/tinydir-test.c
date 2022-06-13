#include "submodules/log.h/log.h"
#include "tinydir-test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>


//////////////////////////////////////////////


TEST t_tinydir_0(void *PATH){
  tinydir_dir dir;

  if (tinydir_open(&dir, (char *)PATH) == -1) {
    perror("Error opening file");
    goto bail;
  }

  while (dir.has_next) {
    tinydir_file file;
    if (tinydir_readfile(&dir, &file) == -1) {
      perror("Error getting file");
      goto bail;
    }

    printf("\t%s", file.name);
    if (file.is_dir) {
      printf(" (DIRECTORY)");
    }else{
      printf(" (FILE)");
    }

    if (tinydir_next(&dir) == -1) {
      perror("Error getting next file");
      goto bail;
    }
    printf("\n");
  }

  tinydir_close(&dir);
  PASS();
bail:
  tinydir_close(&dir);
}

GREATEST_MAIN_DEFS();

SUITE(t_tinydir){
  RUN_TESTp(t_tinydir_0, ".");
  PASS();
}


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(t_tinydir);

  GREATEST_MAIN_END();
  return(0);
}

