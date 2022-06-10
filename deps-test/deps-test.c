#include "deps-test.h"
#define SLEEP_US    100000


void do_test_progressbar(void){
  int         max     = 60;
  progressbar *smooth = progressbar_new("Smooth", max);

  for (int i = 0; i < max; i++) {
    usleep(SLEEP_US);
    progressbar_inc(smooth);
  }
  progressbar_finish(smooth);

  progressbar *longlabel = progressbar_new("Three Second Task with a long label", 3);

  for (int i = 0; i < 3; i++) {
    progressbar_inc(longlabel);
    sleep(1);
  }
  progressbar_finish(longlabel);

  progressbar *fast = progressbar_new("Fast", 20);

  for (int i = 0; i < 20; i++) {
    usleep(SLEEP_US);
    progressbar_inc(fast);
  }
  progressbar_finish(fast);

  progressbar *custom = progressbar_new_with_format("Custom", max, "<.>");

  for (int i = 0; i < max; i++) {
    usleep(SLEEP_US);
    progressbar_inc(custom);
  }
  progressbar_finish(custom);
}


void do_test_statusbar(void){
  statusbar *status = statusbar_new("Indeterminate");

  for (int i = 0; i < 30; i++) {
    usleep(SLEEP_US);
    statusbar_inc(status);
  }
  statusbar_finish(status);

  statusbar *longStatus = statusbar_new("Status bar with a really long label");

  for (int i = 0; i < 10; i++) {
    usleep(SLEEP_US);
    statusbar_inc(longStatus);
  }
  statusbar_finish(longStatus);

  statusbar *customStatus = statusbar_new_with_format("Custom", "(|)|");

  for (int i = 0; i < 30; i++) {
    usleep(SLEEP_US);
    statusbar_inc(customStatus);
  }
  statusbar_finish(customStatus);
}


int32_t FillFromURANDOM(uint8_t *out, size_t outlen){
  FILE *fpurandom = fopen("/dev/urandom", "r");

  if (!fpurandom) {
    return(-1);
  }
  int32_t bread = fread(out, 1, outlen, fpurandom);

  fclose(fpurandom);
  return(bread < outlen ? -1 : bread);
}


void demo_ansi_qrcode(){
  char secret[33] = { 0 };

  generate_random_secret(secret, 33, FillFromURANDOM);
  printf("Secret: %s\n", secret);
  char *qrcodeansi = create_totp_qrcode("Test", "Meow", secret);

  printf("\n----------------------------------------------------------------------------\n");
  printf("%s", qrcodeansi);
  printf("----------------------------------------------------------------------------\n");
  free(qrcodeansi);
}


void demo_totp_calculation(){
  char secret[33] = { 0 };
  char buf[512]   = { 0 };

  sprintf(buf, "%s", "abc123");
  size_t secretlen = base32decode(buf, strnlen(buf, 512),
                                  secret, 33);

  time_t now = time(0);
  int    otp = compute_totp(secret, secretlen, now, 30, 6);

  printf("OTP code>\n\tSecret:\t%s\n\tTOTP:\t%06d\n", buf, otp);
}


TEST test_statusbar(void){
  do_test_statusbar();
  PASS();
}


TEST test_progressbar(void){
  do_test_progressbar();
  PASS();
}


TEST test_libmutotp_totp(void){
  demo_totp_calculation();
  PASS();
}


TEST test_libmutotp_qrcode(void){
  demo_ansi_qrcode();
  printf("libmutotp OK!\n");
  PASS();
}


TEST test_spin(void){
  const int big_number = 1000000000 / 1;
  spinner   *s         = spin_new(utf8_pat1, "Working", UTF8_CHAR_WIDTH);
  int       x          = 0;
  int       working    = 1;

  while (working) {
    if (x == (big_number * .25)) {
      spin_upd_msg(s, "Part way through");
      spin_drw(s);
    }
    if (x == (big_number * .75)) {
      spin_upd_msg(s, "Getting close now");
      spin_drw(s);
    }
    if (x % 9999999 == 0) {
      spin_drw(s);
    }
    if (x++ > big_number) {
      working = 0;
    }
  }
  spin_del(s);
  printf("Done!\n");
  PASS();
}


TEST test_timestamp(void){
  int ts = (int)timestamp();

  DEBUG_PRINT(ts, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}


TEST test_debug_print(void){
  int  o  = 123;
  char *s = "abc123";

  DEBUG_PRINT(s, .colorscheme    = FORE_BLUE BACK_BLACK, .filestream = stdout);
  DEBUG_PRINT(o, .colorscheme    = FORE_BLACK BACK_WHITE, .filestream = stdout);
  DEBUG_PRINT("OK", .colorscheme = FORE_YELLOW BACK_BLACK, .filestream = stderr);
  PASS();
}

SUITE(suite_0) {
  RUN_TEST(test_debug_print);
  RUN_TEST(test_timestamp);
  RUN_TEST(test_libmutotp_qrcode);
  RUN_TEST(test_libmutotp_totp);
  RUN_TEST(test_progressbar);
  RUN_TEST(test_statusbar);
  RUN_TEST(test_spin);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(suite_0);
  GREATEST_MAIN_END();
}
