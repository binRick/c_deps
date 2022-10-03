////////////////////////////////////////////

////////////////////////////////////////////
#include "stp_print-test/stp_print-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "stp_print/stp_print.h"
#include "timestamp/timestamp.h"
typedef enum {
  A = 1 << 0,
  B = 1 << 1,
  C = 1 << 2,
  D = 1 << 3,
} enum_t;

typedef struct {
  char *msg;
} sub2_t;

typedef struct {
  int    sub_dat1;
  int    sub_dat2;
  int    sub_dat3;
  sub2_t *psub2a;
  sub2_t *psub2b;
} sub_t;

typedef struct {
  int    data_int;
  char   c;
  void   *addr;
  enum_t e;
  sub_t  sub;
  char   *text;
  sub_t  *psub;
} data_t;

void push_str(char *buf, int expr, char *val, int *flag){
  if (expr) {
    if (*flag) {
      sprintf(buf, "%s | ", buf);
    }
    *flag = 1;
    sprintf(buf, "%s%s", buf, val);
  }
}

int print_enum_t(char *buf, int buf_size, void *ptr, char *fmt){
  char   msg[32];
  enum_t e = *((enum_t *)ptr);

  memset(msg, 0, sizeof(msg));
  int flag = 0;

  sprintf(msg, "%s{ ", msg);
  push_str(msg, (e & A), "A", &flag);
  push_str(msg, (e & B), "B", &flag);
  push_str(msg, (e & C), "C", &flag);
  push_str(msg, (e & D), "D", &flag);
  sprintf(msg, "%s }", msg);

  return(snprintf(buf, buf_size, "%s", msg));
}

stp_print_begin(sub2_t, 1) {
  stp_print_field_string(msg);
  stp_print_end();
}

stp_print_begin(sub_t, 5) {
  stp_print_field_int(sub_dat1);
  stp_print_field_uint(sub_dat2);
  stp_print_field_int(sub_dat3);
  stp_print_field_structp(psub2a, sub2_t);
  stp_print_field_structp(psub2b, sub2_t);
  stp_print_end();
}

stp_print_begin(data_t, 7) {
  stp_print_field_int(data_int);
  stp_print_field_struct(sub, sub_t);
  stp_print_field_char(c);
  stp_print_field_ptr(addr, void *);
  stp_print_field_any(e, enum_t, print_enum_t);
  stp_print_field_string(text);
  stp_print_field_structp(psub, sub_t);
  stp_print_end();
}

void print_data(data_t *ptr, int level){
  char msg[1024];

  printf("----\n");
  stp_snprintf(data_t, msg, sizeof(msg), ptr, "data", level);
  printf("%s", msg);
}
int    hoge;
sub2_t sub2 = {
  .msg = "abcdefghijklmnopqrstuvwxyz"
         "abcdefghijklmnopqrstuvwxyz"
         "abcdefghijklmnopqrstuvwxyz",
};
sub_t  sub = {
  .sub_dat1 = 1,
  .sub_dat2 = 2,
  .sub_dat3 = 3,
  .psub2b   = &sub2,
};
data_t d = {
  .data_int = 1,
  .c        = 'x',
  .addr     = &hoge,
  .e        = A | C | D,
  .sub      = {
    .sub_dat1 = 123,
    .sub_dat2 = -1,
    .sub_dat3 = 0xa,
  },
  .text = "hogehoge",
  .psub = &sub,
};

////////////////////////////////////////////
TEST t_stp_print_test(){
  print_data(&d, 0);
  printf("sub=%p\n", &sub);
  print_data(&d, 2);
  PASS();
}

SUITE(s_stp_print_test) {
  RUN_TEST(t_stp_print_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_stp_print_test);
  GREATEST_MAIN_END();
}
