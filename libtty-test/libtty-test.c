#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "libtty-test/libtty-test.h"
#include "log/log.h"
#include "ms/ms.h"
#include "termrec/libtty/tty.h"
#include "termrec/libtty/ttyrec.h"
#include "termrec/sys/error.h"
#include "timestamp/timestamp.h"
#include <bzlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <zlib.h>

TEST t_libtty_test2(){
  /*
   * recorder r;
   * struct timeval tv;
   * tv.tv_sec=20;
   * tv.tv_usec=10;
   * if (!(r=ttyrec_w_open(-1, 0, "/tmp/tty1", &tv)))
   *    die("Can't write the ttyrec to %s\n", "/tmp/tty1");
   * ttyrec_w_write(r, &tv, "Abc", 3);    tv.tv_sec++;
   * ttyrec_w_write(r, &tv, "D", 1);      tv.tv_sec++;
   * ttyrec_w_write(r, &tv, "Ef", 2);     tv.tv_sec++;
   * ttyrec_w_write(r, &tv, "G", 1);      tv.tv_sec++;
   * ttyrec_w_write(r, &tv, "Hij\n",4); tv.tv_sec++;
   * ttyrec_w_close(r);
   */
  PASS();
}
#define BUFFER_SIZE    65536

TEST t_libtty_test1(){
  tty  vt;
  char buf[BUFFER_SIZE] = "ls";
  int  len              = strlen(buf);

  vt = tty_init(20, 5, 1);

  tty_write(vt, buf, len);

  tty_free(vt);

  PASS();
}

SUITE(s_libtty_test) {
  RUN_TEST(t_libtty_test1);
  RUN_TEST(t_libtty_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_libtty_test);
  GREATEST_MAIN_END();
}
