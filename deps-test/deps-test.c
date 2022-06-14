#include "deps-test.h"
#include <assert.h>
#define TBL1        "\
\
┌───────────────────────────────┐\
│    Test suite  #Cases  Result │\
├───────────────────────────────┤\
│ 1  Table                       \
├───────────────────────────────┤\
│      End result              \
└───────────────────────────────┘\
\
"
#define SLEEP_US    100000


#define feed(x)          { do{                                                                                                   \
                             struct color_char ch = cansid_process(&state, x);                                                   \
                             if (false) DEBUG_PRINT((int)ch.ascii, .colorscheme = FORE_CYAN BACK_BLACK, .filestream = stdout);   \
                             if (true) DEBUG_PRINT((int)ch.style, .colorscheme  = FORE_YELLOW BACK_BLACK, .filestream = stdout); \
                             DEBUG_PRINT((char)ch.ascii, .colorscheme           = FORE_CYAN BACK_BLACK, .filestream = stdout);   \
                           }while (0); }

#define DEBUG_STATE()    { do {                                                                                                  \
                             if (false) {                                                                                        \
                               DEBUG_PRINT((int)state.style, .colorscheme      = FORE_BLUE BACK_BLACK, .filestream = stdout);    \
                               DEBUG_PRINT((int)state.state, .colorscheme      = FORE_BLUE BACK_BLACK, .filestream = stdout);    \
                               DEBUG_PRINT((int)state.next_style, .colorscheme = FORE_MAGENTA BACK_BLACK, .filestream = stdout); \
                             }                                                                                                   \
                           }while (0); }


void do_test_libspinner(){
  spinner_t *s = spinner_new(32);

  s->delay     = 100000;
  s->prefix    = "Running ";
  s->suffix    = " I'm a suffix";
  s->final_msg = "Complete!\n";
  spinner_start(s);
  sleep(2);
  spinner_stop(s);
  spinner_free(s);
}


void do_test_which(){
  char *name = "ls";
  char *path = (char *)which(name);

  printf("\n<WHICH>%s: %s\n\n", name, path ? path : "not found");

  name = "ls1";
  path = (char *)which(name);
  printf("\n<WHICH>%s: %s\n\n", name, path ? path : "not found");

  free(path);
}


void do_test_slug(){
  char *s0 = "foo b ar@-";
  char s01[32];

  sprintf(s01, "%s", s0);
  char *s1 = slug(s01);

  fprintf(stdout, "\nSLUG: '%s'->'%s'\n", s0, s01);
}


void do_test_cansid(void){
  struct cansid_state state;

  state = cansid_init();
  feed('\x1B');
  char *as = malloc(1024);

  DEBUG_STATE();
  as = "OK1";
  for (int i = 0; i < strlen(as); i++) {
    feed(as[i]);
  }
  as = "\x1b[31m\x1b[40mRED_BLACK\x1b[0m";
  for (int i = 0; i < strlen(as); i++) {
    feed(as[i]);
  }
  as = "\x1b[32mRED\x1b[0mRR";
  for (int i = 0; i < strlen(as); i++) {
    feed(as[i]);
  }
}


void do_test_progressbar(void){
  int         max     = 60 / 1;
  progressbar *smooth = progressbar_new("Smooth", max);

  for (int i = 0; i < max; i++) {
    usleep(SLEEP_US / 10);
    progressbar_inc(smooth);
  }
  progressbar_finish(smooth);

  progressbar *longlabel = progressbar_new("Three Second Task with a long label", 3);

  for (int i = 0; i < 3; i++) {
    progressbar_inc(longlabel);
    usleep(SLEEP_US / 10);
  }
  progressbar_finish(longlabel);

  progressbar *fast = progressbar_new("Fast", 20);

  for (int i = 0; i < 20; i++) {
    usleep(SLEEP_US / 10);
    progressbar_inc(fast);
  }
  progressbar_finish(fast);

  progressbar *custom = progressbar_new_with_format("Custom", max, "<.>");

  for (int i = 0; i < max; i++) {
    usleep(SLEEP_US / 10);
    progressbar_inc(custom);
  }
  progressbar_finish(custom);
}


void do_test_statusbar(void){
  statusbar *status = statusbar_new("Indeterminate");

  for (int i = 0; i < 30; i++) {
    usleep(SLEEP_US / 10);
    statusbar_inc(status);
  }
  statusbar_finish(status);

  statusbar *longStatus = statusbar_new("Status bar with a really long label");

  for (int i = 0; i < 10; i++) {
    usleep(SLEEP_US / 10);
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


TEST test_totp(void){
  demo_totp_calculation();
  PASS();
}


TEST test_qrcode(void){
  demo_ansi_qrcode();
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


TEST test_cansid(void){
  do_test_cansid();
}


TEST test_timestamp(void){
  int ts = (int)timestamp();

  DEBUG_PRINT(ts, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}


TEST test_libspinner(void){
  do_test_libspinner();
  PASS();
}


TEST test_which(void){
  do_test_which();
  PASS();
}


TEST test_slug(void){
  do_test_slug();
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

SUITE(test_time) {
  RUN_TEST(test_timestamp);
  PASS();
}
SUITE(test_spinner) {
  RUN_TEST(test_libspinner);
  RUN_TEST(test_spin);
  PASS();
}
SUITE(suite_totp) {
  RUN_TEST(test_totp);
  PASS();
}
SUITE(suite_qrcode) {
  RUN_TEST(test_qrcode);
  PASS();
}
SUITE(test_status) {
  RUN_TEST(test_statusbar);
  PASS();
}
SUITE(test_progress) {
  RUN_TEST(test_progressbar);
  PASS();
}

SUITE(test_path) {
  RUN_TEST(test_which);
  PASS();
}
SUITE(test_debug) {
  RUN_TEST(test_debug_print);
  PASS();
}
SUITE(test_parse) {
  RUN_TEST(test_cansid);
  PASS();
}
SUITE(test_string) {
  RUN_TEST(test_slug);
  PASS();
}
/////////////////////////////////////////
char JSON_TESTS_FILE[] = ".tests.json";
char *JSON_TESTS_CONTENT;


TEST process_json_lines(void){
  struct StringFNStrings LINES = stringfn_split_lines_and_trim(JSON_TESTS_CONTENT);

  free(JSON_TESTS_CONTENT);
  if (false) {
    DEBUG_PRINT(LINES.count, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  }
  for (int i = 0; i < LINES.count; i++) {
    if (strlen(LINES.strings[i]) < 2) {
      continue;
    }
    if (false) {
      DEBUG_PRINT(LINES.strings[i], .colorscheme = FORE_GREEN BACK_BLACK, .filestream = stdout);
    }
    JSON_Value  *Line        = json_parse_string(LINES.strings[i]);
    JSON_Object *LineObject  = json_object(Line);
    char        *suite_name  = json_object_get_string(LineObject, "suite");
    char        *binary_name = json_object_get_string(LineObject, "binary");
    if (false) {
      DEBUG_PRINT(suite_name, .colorscheme = FORE_GREEN BACK_BLACK, .filestream = stdout);
    }
    JSON_Array *Tests    = json_object_get_array(LineObject, "tests");
    size_t     tests_qty = json_array_get_count(Tests);
    if (false) {
      DEBUG_PRINT((int)tests_qty, .colorscheme = FORE_YELLOW BACK_BLACK, .filestream = stdout);
    }
    for (size_t i = 0; i < tests_qty; i++) {
      char *test_name = json_array_get_string(Tests, i);
      fprintf(stdout, "[%s] %15s %3lu/%lu  %12s\n",
              binary_name,
              suite_name,
              i + 1,
              tests_qty,
              test_name
              );
      free(test_name);
    }
    json_value_free(LineObject);
    free(suite_name);
    free(binary_name);
  }
  stringfn_release_strings_struct(LINES);
  PASS();
} /* process_json_lines */


TEST test_occurrences(void){
  int qty;

  qty = occurrences("l", "hello");
  ASSERT_EQ(2, qty);
  qty = occurrences("L", "hello");
  ASSERT_EQ(0, qty);
  qty = occurrences(NULL, "hello");
  ASSERT_EQ(-1, qty);
  qty = occurrences("hello", NULL);
  ASSERT_EQ(-1, qty);
  PASS();
}


TEST test_str_replace(){
  char *replaced = str_replace("hello world", "hello", "goodbye");

  printf("%s\n", replaced);
  free(replaced);
  PASS();
}

SUITE(s_deps){
  RUN_TEST(test_occurrences);
  RUN_TEST(test_str_replace);
  PASS();
}


TEST read_json_file(void){
  DEBUG_PRINT(JSON_TESTS_FILE, .colorscheme    = FORE_BLUE BACK_BLACK, .filestream = stdout);
  JSON_TESTS_CONTENT                           = fsio_read_text_file(JSON_TESTS_FILE);
  DEBUG_PRINT(JSON_TESTS_CONTENT, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}
SUITE(tests) {
  RUN_TEST(read_json_file);
  RUN_TEST(process_json_lines);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(tests);
  RUN_SUITE(test_parse);
  RUN_SUITE(test_string);
  RUN_SUITE(test_debug);
  RUN_SUITE(test_time);
  RUN_SUITE(test_path);
  RUN_SUITE(test_progress);
  RUN_SUITE(suite_qrcode);
  RUN_SUITE(suite_totp);
  RUN_SUITE(test_spinner);
  RUN_SUITE(s_deps);
  GREATEST_MAIN_END();
}
