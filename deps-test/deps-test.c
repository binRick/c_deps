#define MKCREFLECT_IMPL
#include "../submodules/generic-print/print.h"
#include "deps-test.h"
#include <assert.h>
////////////////////////////////////////////////////////
static int do_get_google();
static inline int file_exists(const char *path);

#define ASSERT_SQLDB_RESULT()    { do {                                \
                                     ASSERT_EQ(rc, SQLDBAL_STATUS_OK); \
                                   } while (0); }


////////////////////////////////////////////////////////
TEST t_sqldbal(void){
  int64_t                  ts = -1, qty = -1, rowid = -1, ins_id = -1, ins_item_id = -1, created_ts = -1;
  enum sqldbal_status_code rc;
  struct sqldbal_db        *db;
  struct sqldbal_stmt      *stmt;
  const char               *text, *created, *_created;
  char                     ts_s[1024];

  rc = sqldbal_open(SQLDBAL_DRIVER_SQLITE, LOCATION, NULL, NULL, NULL, NULL, FLAGS, NULL, 0, &db);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_exec(db, "PRAGMA foreign_keys = ON", NULL, NULL);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_exec(db,
                    "\
CREATE TABLE IF NOT EXISTS test(\
 _id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT\
, _created  DATETIME NOT NULL DEFAULT (datetime(CURRENT_TIMESTAMP, 'localtime'))\
, ts INTEGER NOT NULL\
, str VARCHAR(20) NOT NULL\
)",
                    NULL,
                    NULL);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_exec(db,
                    "\
CREATE TABLE IF NOT EXISTS test_items(\
 _id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT\
, _created  DATETIME NOT NULL DEFAULT (datetime(CURRENT_TIMESTAMP, 'localtime'))\
, test_id INTEGER NOT NULL\
, str VARCHAR(20) NOT NULL\
, CONSTRAINT fk_test_ids FOREIGN KEY (test_id) REFERENCES test(_id)\
  ON DELETE CASCADE ON UPDATE CASCADE\
)",
                    NULL,
                    NULL);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_stmt_prepare(db,
                            "DELETE FROM test",
                            -1,
                            &stmt);
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_stmt_prepare(db,
                            "DELETE FROM test_items",
                            -1,
                            &stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  printf(
    AC_RESETALL AC_BRIGHT_RED ">DELETED all rows\n" AC_RESETALL
    );
  rc = sqldbal_stmt_close(stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);

  for (size_t i = 0; i < INSERT_QTY; i++) {
    ts = timestamp();
    sprintf(ts_s, "%llu", ts);
    rc = sqldbal_stmt_prepare(db,
                              "INSERT INTO test(ts, str) VALUES(?, ?)",
                              -1,
                              &stmt);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_bind_int64(stmt, 0, ts);
    ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
    rc = sqldbal_stmt_bind_text(stmt, 1, ts_s, -1);
    ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
    rc = sqldbal_stmt_execute(stmt);
    ASSERT_SQLDB_RESULT();

    ins_id = -1;
    rc     = sqldbal_last_insert_id(db, "test_id_seq", &ins_id);
    ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
    ASSERT_GTE(ins_id, 1);
    rc = sqldbal_stmt_close(stmt);
    ASSERT_SQLDB_RESULT();

    for (size_t ii = 0; ii < INSERT_QTY; ii++) {
      rc = sqldbal_stmt_prepare(db, "INSERT INTO test_items(test_id, str) VALUES(?, ?)", -1, &stmt);
      ASSERT_SQLDB_RESULT();
      rc = sqldbal_stmt_bind_int64(stmt, 0, ins_id);
      ASSERT_SQLDB_RESULT();
      rc = sqldbal_stmt_bind_text(stmt, 1, ts_s, -1);
      ASSERT_SQLDB_RESULT();
      rc = sqldbal_stmt_execute(stmt);
      ASSERT_SQLDB_RESULT();
      ins_item_id = -1;
      rc          = sqldbal_last_insert_id(db, "test_items_id_seq", &ins_item_id);
      ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
      ASSERT_GTE(ins_item_id, 1);
      rc = sqldbal_stmt_close(stmt);
      ASSERT_SQLDB_RESULT();
    }
  }

  rc = sqldbal_stmt_prepare(db,
                            "SELECT COUNT(*) FROM test",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &qty);
    ASSERT_SQLDB_RESULT();
    printf(
      AC_RESETALL AC_YELLOW ">%llu test rows\n" AC_RESETALL,
      qty
      );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_stmt_prepare(db,
                            "SELECT COUNT(*) FROM test_items",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &qty);
    ASSERT_SQLDB_RESULT();
    printf(
      AC_RESETALL AC_YELLOW ">%llu test_item rows\n" AC_RESETALL,
      qty
      );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();


  rc = sqldbal_stmt_prepare(db,
                            "DELETE from test where _id = ?",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_bind_int64(stmt, 0, INSERT_QTY);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_stmt_prepare(db,
                            "SELECT COUNT(*) FROM test_items",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &qty);
    ASSERT_SQLDB_RESULT();
    printf(
      AC_RESETALL AC_YELLOW ">%llu test_item rows\n" AC_RESETALL,
      qty
      );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();


  rc = sqldbal_stmt_prepare(db,
                            "SELECT\
  _id\
, _created\
, ts\
, str\
, CAST(((julianday(_created)-2440587.5)*86400) as created_ts)\
  FROM test",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &rowid);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_text(stmt, 1, &_created, NULL);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_int64(stmt, 2, &ts);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_text(stmt, 3, &text, NULL);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_int64(stmt, 4, &created_ts);
    ASSERT_SQLDB_RESULT();
    fprintf(stderr,
            AC_RESETALL AC_CYAN "#%llu> %llu / %s|_created:%s|created_ts:%llu|\n" AC_RESETALL,
            rowid, ts, text, _created, created_ts
            );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();


  rc = sqldbal_close(db);
  ASSERT_SQLDB_RESULT();
  PASS();
} /* do_sqldbal */


TestStruct test_struct = {
  .name = "xxxxxxxx",
};


void do_mkcreflect(){
  printf(
    AC_RESETALL AC_GREEN AC_BOLD "<%s>" AC_RESETALL " "
    AC_YELLOW "%lub (%lub packed)" AC_RESETALL " "
    AC_BLUE "[%lu fields]" AC_RESETALL  " "
    AC_RESETALL "\n",
    TestStructInfo->name, TestStructInfo->size,
    TestStructInfo->packed_size,
    TestStructInfo->fields_count
    );
  for (size_t i = 0; i < TestStructInfo->fields_count; i++) {
    MKCREFLECT_FieldInfo *field = &TestStructInfo->fields[i];
    printf(
      AC_RESETALL AC_GREEN AC_BOLD "\t#%lu/%lu" " "
      AC_RESETALL AC_GREEN AC_BOLD "<"
      AC_RESETALL AC_BRIGHT_BLUE AC_BOLD AC_UNDERLINE AC_REVERSED "%s"
      AC_RESETALL AC_GREEN AC_BOLD ">"
      AC_RESETALL "\n"
      AC_MAGENTA "\t\tType: #"
      AC_RESETALL AC_CYAN AC_BOLD "%d" AC_RESETALL " "
      AC_MAGENTA "'"
      AC_RESETALL AC_YELLOW_BLACK AC_ITALIC "%s" AC_RESETALL
      AC_MAGENTA "'" AC_RESETALL  "\n"
      AC_CYAN "\t\tPointer? %s" AC_RESETALL  "\n"
      AC_CYAN "\t\t[%lub]" AC_RESETALL  "\n"
      AC_BLUE "\t\t[%d|%s]" AC_RESETALL  "\n",
      i + 1, TestStructInfo->fields_count, field->field_name,
      field->data_type, field->field_type,
      BOOL_TO_STR(FIELD_IS_POINTER(field->data_type)),
      field->size,
      field->array_size,
      (field->array_size != -1) ?
      AC_RESETALL AC_BOLD AC_UNDERLINE AC_YELLOW "Array" AC_RESETALL
                :
      AC_RESETALL AC_BOLD AC_UNDERLINE AC_RED "Not Array" AC_RESETALL
      );
    if (false) {
      printf("    Type: %s\t", field->field_type);
      printf("    Total size: %lu\t", field->size);
      printf("    data_type: %d\t", field->data_type);
      printf("    is_signed: %s\t", field->is_signed?"Yes":"No");
      printf("    Offset: %lu\t", field->offset);
      if (field->array_size != -1) {
        printf("    It is an array! Number of elements: %d, size of single element: %lu\t",
               field->array_size, field->size / field->array_size);
      }
    }
    //printf("\n");
  }
} /* do_mkcreflect */

char JSON_TESTS_FILE[] = ".tests.json",
     *JSON_TESTS_CONTENT;


static inline int file_exists(const char *path) {
  struct stat b;

  return(stat(path, &b));
}


static int do_get_google(){
  http_get_response_t *res = http_get("https://api.github.com/repos/clibs/clib/releases/latest");

  printf("\nok=%d\n", res->ok);
  printf("status=%lu\n", res->status);
  printf("content=%s\n\n", res->data);
  http_get_free(res);

  char *f = "./google.html";
  int  ok = http_get_file("http://google.com", f);

  printf("\nok=%d\n", ok);
  printf("file exists:%d\n\n", file_exists(f));


  return(0);
}


void do_work_fn(void *args){
  struct FnArgs *fn_args = (struct FnArgs *)args;

  usleep(100);
  printf("Counter: %d\n", fn_args->counter);

  free(fn_args);
}


size_t do_dmt_summary(void){
  size_t usage = dmt_usage();

  printf("Current memory usage: %lu bytes\n", usage);
  return(usage);
}


static void on_start(void *event_data, void *context){
  printf("OnStart, data: %s context: %s\n", (char *)event_data, (char *)context);
}


static void on_end(void *event_data, void *context){
  printf("OnEnd, data: %s context: %s\n", (char *)event_data, (char *)context);
}


static void on_unhandled(int event_id, void *event_data, void *context){
  printf("OnUnhandled, did not set listener for event: %d data: %s context: %s\n", event_id, (char *)event_data, (char *)context);
}

#define SLEEP_US    100000


void do_test_libspinner(){
  spinner_t *s = spinner_new(32);

  s->delay     = 100;
  s->prefix    = "Running ";
  s->suffix    = " I'm a suffix";
  s->final_msg = "Complete!\n";
  spinner_start(s);
  usleep(100);
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

#define DEBUG_STATE()    { do {                                                                                                  \
                             if (false) {                                                                                        \
                               DEBUG_PRINT((int)state.style, .colorscheme      = FORE_BLUE BACK_BLACK, .filestream = stdout);    \
                               DEBUG_PRINT((int)state.state, .colorscheme      = FORE_BLUE BACK_BLACK, .filestream = stdout);    \
                               DEBUG_PRINT((int)state.next_style, .colorscheme = FORE_MAGENTA BACK_BLACK, .filestream = stdout); \
                             }                                                                                                   \
                           }while (0); }

#define feed(x)          { do{                                                 \
                             struct color_char ch = cansid_process(&state, x); \
                             sprintf(S, "%c", (char)ch.ascii);                 \
                             if ((int)state.state == CANSID_FGCOLOR) {         \
                               PRINT("FG Update:", (int)state.style);          \
                               FG = (int)state.next_style;                     \
                             }                                                 \
                             if ((int)state.state == CANSID_BGCOLOR) {         \
                               PRINT("BG Update:", (int)state.style);          \
                               BG = (int)state.next_style;                     \
                             }                                                 \
                             if ((char)ch.ascii != 0) {                        \
                               PRINT(                                          \
                                 "\tString:", (char *)S,                       \
                                 "  Char:", (char)ch.ascii,                    \
                                 "  Code:", (int)ch.ascii,                     \
                                 "  State Style:", (int)state.style,           \
                                 "  State Next Style:", (int)state.next_style, \
                                 "  State State:", (int)state.state,           \
                                 "  FG:", FG,                                  \
                                 "  BG:", BG,                                  \
                                 "\t"                                          \
                                 );                                            \
                             }                                                 \
                           }while (0); }

#define _FEED(STR)       { do{                                     \
                             for (int i = 0; i < strlen(STR); i++) \
                             feed(STR[i]);                         \
                             printf("\n");                         \
                           }while (0); }

#define FEED(STR)        { do{                                                                 \
                             PRINT(AC_RESETALL "FEED>" AC_RESETALL "\t", strdup_escaped(STR)); \
                             int FG = -1, BG = -1; char S[2];                                  \
                             _FEED(STR);                                                       \
                           }while (0); }


void do_test_cansid(void){
  struct cansid_state state;

  state = cansid_init();
  printf("\n" AC_YELLOW AC_ITALIC "===========================================================================" AC_RESETALL "\n");
  PRINT(
    "CANSID_FGCOLOR:", CANSID_FGCOLOR,
    "\t",
    "CANSID_BGCOLOR:", CANSID_BGCOLOR,
    "\t",
    "CANSID_ENDVAL:", CANSID_ENDVAL,
    "\t"
    );
  printf(AC_YELLOW AC_ITALIC "===========================================================================" AC_RESETALL "\n");

  DEBUG_STATE();
  FEED(AC_BLUE "B");
  FEED(AC_RED "R");
  FEED(AC_RED_BLUE "RB");
  if (false) { \
    FEED(AC_YELLOW "Y");
    FEED(AC_YELLOW_BLACK "YY" AC_RED_RED "RR");
    FEED(AC_RED "G");
    FEED("none");
    FEED(AC_WHITE "W");
    FEED("none");
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


void do_forever_my_program(void *context){
  dbg("t_forever_my_program", %s);
  if (context != NULL) {
    // do something with the context
  }

  usleep(100);
  exit(0);
}


int do_forever_callback(void *context, const unsigned char started, int stat_loc){
  if (context != NULL) {
    // do something with the context
  }
  dbg(stat_loc, %d);
  dbg(started, %c);
  if (stat_loc == 0 || !started) {
    return(-1); // no more retries
  }
  dbg("do_forever_callback", %s);
  return(500); // wait 500 millies before next invocation, 0 for no wait.
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


TEST t_statusbar(void){
  do_test_statusbar();
  PASS();
}


TEST t_progressbar(void){
  do_test_progressbar();
  PASS();
}


TEST t_totp(void){
  demo_totp_calculation();
  PASS();
}


TEST t_qrcode(void){
  demo_ansi_qrcode();
  PASS();
}


TEST t_spin(void){
  const int big_number = 10000000 / 1;
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


TEST t_cansid(void){
  do_test_cansid();
  PASS();
}


TEST t_timestamp(void){
  int ts = (int)timestamp();

  DEBUG_PRINT(ts, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}


TEST t_libspinner(void){
  do_test_libspinner();
  PASS();
}


TEST t_which(void){
  do_test_which();
  PASS();
}


TEST t_slug(void){
  do_test_slug();
  PASS();
}


TEST t_debug_print(void){
  int  o  = 123;
  char *s = "abc123";

  DEBUG_PRINT(s, .colorscheme    = FORE_BLUE BACK_BLACK, .filestream = stdout);
  DEBUG_PRINT(o, .colorscheme    = FORE_BLACK BACK_WHITE, .filestream = stdout);
  DEBUG_PRINT("OK", .colorscheme = FORE_YELLOW BACK_BLACK, .filestream = stderr);
  PASS();
}


TEST t_process_json_lines(void){
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


TEST t_libbeaufort(void){
  static char *monkey   = NULL;
  static char *monkey_s = NULL;

  static char *goodman   = NULL;
  static char *goodman_s = NULL;

  static char *groove   = NULL;
  static char *groove_s = NULL;

  monkey_s = "kinkajous are awesome";
  monkey   = beaufort_encrypt(monkey_s, "monkey", NULL);
  assert(monkey);
  assert(0 == strcmp(monkey, "26004Fyuv AnK Cs9sqC8"));

  goodman_s = "the \nbig \nlebowski";
  goodman   = beaufort_encrypt(goodman_s, "goodman", NULL);
  assert(goodman);
  assert(0 == strcmp(goodman, "n7A \n24u \n22D0huq5"));

  groove_s = "d4nc3 t0 th3 mus!c :D";
  groove   = beaufort_encrypt(groove_s, "groove", NULL);
  assert(groove);
  assert(0 == strcmp(groove, "3n1Cs lg y7l 9ko!F :b"));
  dbg(monkey, %s);
  dbg(monkey_s, %s);
  dbg(goodman, %s);
  dbg(goodman_s, %s);
  dbg(groove, %s);
  dbg(groove_s, %s);
  PASS();
}


TEST t_murmurhash(void){
  uint32_t   seed = 0;
  const char *key = "kinkajou";
  uint32_t   hash = murmurhash(key, (uint32_t)strlen(key), seed);

  dbg(key, %s);
  dbg(seed, %d);
  printf("%" PRIu32 "\n", hash);
  printf("%d" PRIu32 "\n", hash);

  PASS();
}


TEST t_forever(void){
  void         *context = NULL;
  unsigned int counter  = forever_with_options(
    do_forever_my_program, // function to invoke
    context,               // context that is passed to the function on every invocation
    5,                     // max amount of retries. 0 for unlimited retries.
    500                    // amount of millies to wait between invocations. 0 for no wait.
    );

  printf("Invoked %u time/s.\n", counter);
  // call 'my_program' and when it ends/crashes call the provided callback
  counter = forever_with_callback(do_forever_my_program, context, do_forever_callback);
  printf("Invoked %u time/s.\n", counter);

  PASS();
}


TEST t_eventemitter(void){
  struct EventEmitter *event_emitter = eventemitter_new();
  unsigned int        listener_id    = eventemitter_add_listener(event_emitter, EVENT_START, on_start, "some context for start 1");

  eventemitter_add_listener(event_emitter, EVENT_START, on_start, "some context for start 2");
  eventemitter_on(event_emitter, EVENT_START, on_start, "some context for shorthand start"); // shorthand version
  eventemitter_add_once_listener(event_emitter, EVENT_END, on_end, "end context 1");
  eventemitter_once(event_emitter, EVENT_END, on_end, "end context 2");                      // shorthand
  eventemitter_add_unhandled_listener(event_emitter, on_unhandled, "unhandled context 1");
  eventemitter_else(event_emitter, on_unhandled, "unhandled context 2");                     // shorthand
  eventemitter_emit(event_emitter, EVENT_START, "my start event data");
  eventemitter_remove_listener(event_emitter, EVENT_START, listener_id);
  eventemitter_emit(event_emitter, EVENT_START, "my second start event data");
  eventemitter_emit(event_emitter, EVENT_MIDDLE, "middle event data");
  eventemitter_emit(event_emitter, EVENT_END, "end event data");
  eventemitter_emit(event_emitter, EVENT_END, "end event data again");
  eventemitter_emit(event_emitter, EVENT_END, "end event data again 2");
  printf("Releasing Event Emitter\n");
  eventemitter_release(event_emitter);
  PASS();
} /* t_eventemitter */


TEST t_dmt_summary(void){
  size_t used = do_dmt_summary();

  ASSERT_EQ(used, 0);
  PASS();
}


TEST t_dmt(void){
  char *a = dmt_malloc(16);
  char *b = dmt_calloc(16, 2);
  char *c = dmt_malloc(128);

  printf("Size of 'a' variable's allocation: %lu bytes\n", dmt_size(a));
  a = dmt_realloc(a, 128);
  printf("Size of 'a' variable's allocation: %lu bytes\n", dmt_size(a));

  dmt_free(a);
  dmt_free(b);
  dmt_free(c);

  dmt_dump(stdout);

  printf("done\n");
  PASS();
}


TEST t_microtar_read(void){
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


TEST t_workqueue(void){
  printf("Library Examples:\n");

  // create new threaded work queue with default queue size
  // workqueue_new_with_options can be used to define custom queue size
  // each queue owns its own background thread and its possible to create many queues in parallel.
  struct WorkQueue *queue = workqueue_new();

  printf("Queue Size: %zu Backlog Size: %zu\n", workqueue_get_queue_size(queue), workqueue_get_backlog_size(queue));

  for (size_t index = 0; index < 20; index++) {
    struct FnArgs *args = malloc(sizeof(struct FnArgs));
    args->counter = index;

    if (!workqueue_push(queue, do_work_fn, args)) {
      printf("Failed to push work function to queue\n");
      free(args);
    }
  }

  printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queue));

  // wait for queue to finish, queue can still be used afterwards
  workqueue_drain(queue);
  printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queue));

  // release when done
  workqueue_release(queue);

  PASS();
}


TEST t_vector(void){
  struct Vector *vector = vector_new();

  // populate vector using multiple available functions
  vector_push(vector, "test push");
  vector_insert(vector, 1, "test insert");                          // shifts all items from index 1 forward
  vector_prepend(vector, "test prepend");
  char *previous_value = (char *)vector_set(vector, 1, "test set"); // replaces the item at index 1

  printf("Replaced value at index 1, old value: %s\n", previous_value);

  // can fetch any item
  char *value = (char *)vector_get(vector, 1);

  printf("Value at index 1: %s\n", value);
  value = (char *)vector_pop(vector);
  printf("Last Value: %s\n", value);

  // or fetch all items
  void **all_items = vector_to_array(vector);

  printf("First item: %s\n", (char *)all_items[0]);

  // can remove any item
  value = (char *)vector_remove(vector, 0); // shifts all items after index backward
  printf("Removed first item: %s\n", value);

  // modify the vector size
  size_t size     = vector_size(vector);
  size_t capacity = vector_capacity(vector);

  printf("Current size: %zu capacity: %zu\n", size, capacity);
  vector_shrink(vector);
  size     = vector_size(vector);
  capacity = vector_capacity(vector);
  printf("Current size: %zu capacity: %zu\n", size, capacity);
  vector_shrink(vector);
  size     = vector_ensure_capacity(vector, 100);
  capacity = vector_capacity(vector);
  printf("Current size: %zu capacity: %zu\n", size, capacity);

  // when we are done with the vector, we release it
  vector_release(vector);
  PASS();
} /* test_vector */


TEST t_occurrences(void){
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


TEST t_read_json_file(void){
  DEBUG_PRINT(JSON_TESTS_FILE, .colorscheme    = FORE_BLUE BACK_BLACK, .filestream = stdout);
  JSON_TESTS_CONTENT                           = fsio_read_text_file(JSON_TESTS_FILE);
  DEBUG_PRINT(JSON_TESTS_CONTENT, .colorscheme = FORE_BLUE BACK_BLACK, .filestream = stdout);
  PASS();
}


TEST t_ansi_utils(void){
  const unsigned char buf[]        = "\e[1m\e[38;2;255;128;255mPINK\e[0m";
  const size_t        buf_len      = sizeof(buf) - 1U;
  char                *escaped_buf = strdup_escaped(buf);

  printf("escaped: '%s'\n", escaped_buf);
  PASS();
}


TEST t_vtparse_csi(void){
  const unsigned char buf[]   = "\e[1m\e[38;2;255;128;255mPINK\e[0m";
  const size_t        buf_len = sizeof(buf) - 1U;

  vtparse_t           parser;

  vtparse_init(&parser);

  ASSERT_EQ(vtparse_has_event(&parser), false);
  ASSERT_EQ(4, vtparse_parse(&parser, buf, buf_len));
  ASSERT_EQ(vtparse_has_event(&parser), true);
  ASSERT_EQ(VTPARSE_ACTION_CSI_DISPATCH, parser.action);
  ASSERT_EQ('m', parser.ch);
  ASSERT_EQ(1U, parser.num_params);
  ASSERT_EQ(1, parser.params[0]);
  printf("\n");
  PRINT(
    "\t",
    "PARAMS:  ", parser.params[0],
    "# Intermediate:  ", parser.num_intermediate_chars,
    "\t"
    )
  ASSERT_EQ(0, parser.num_intermediate_chars);
  ASSERT_EQ(0, parser.error);

  ASSERT_EQ(19, vtparse_parse(&parser, buf + 4, buf_len - 4));
  ASSERT_EQ(vtparse_has_event(&parser), true);
  ASSERT_EQ(VTPARSE_ACTION_CSI_DISPATCH, parser.action);
  ASSERT_EQ('m', parser.ch);
  ASSERT_EQ(5U, parser.num_params);
  ASSERT_EQ(38, parser.params[0]);
  ASSERT_EQ(2, parser.params[1]);
  ASSERT_EQ(255, parser.params[2]);
  ASSERT_EQ(128, parser.params[3]);
  ASSERT_EQ(255, parser.params[4]);
  ASSERT_EQ(0, parser.num_intermediate_chars);
  ASSERT_EQ(0, parser.error);

  ASSERT_EQ(8, vtparse_parse(&parser, buf + 23, buf_len - 23));
  ASSERT_EQ(vtparse_has_event(&parser), true);
  ASSERT_EQ(VTPARSE_ACTION_PRINT, parser.action);
  ASSERT_EQ(0, parser.error);
  ASSERT_EQ(buf + 23, parser.data_begin);
  ASSERT_EQ(buf + 27, parser.data_end);
  printf("\n");
  PRINT(
    "\t",
    "# Intermediate:  ", parser.num_intermediate_chars,
    "# Params:  ", parser.num_params,
    "\t"
    );

  ASSERT_EQ(0U, vtparse_parse(&parser, NULL, 0U));
  ASSERT_EQ(vtparse_has_event(&parser), true);
  ASSERT_EQ(VTPARSE_ACTION_CSI_DISPATCH, parser.action);
  ASSERT_EQ('m', parser.ch);
  ASSERT_EQ(1U, parser.num_params);
  ASSERT_EQ(0, parser.params[0]);
  ASSERT_EQ(0, parser.num_intermediate_chars);
  ASSERT_EQ(0, parser.error);

  ASSERT_EQ(0U, vtparse_parse(&parser, NULL, 0U));
  ASSERT_EQ(vtparse_has_event(&parser), false);

  PASS();
} /* t_vtparse_csi */


TEST t_vtparse_simple(void){
  const unsigned char buf[]   = "Hello World";
  const size_t        buf_len = sizeof(buf) - 1U;

  vtparse_t           parser;

  vtparse_init(&parser);

  size_t parsed_len = vtparse_parse(&parser, buf, buf_len);

  PRINT("parsed len: ", parsed_len, "buf len:", buf_len)
  ASSERT_EQ(buf_len, parsed_len);
  ASSERT_EQ(VTPARSE_ACTION_PRINT, parser.action);
  ASSERT_EQ(0, parser.error);
  ASSERT_EQ(buf, parser.data_begin);
  ASSERT_EQ(buf + buf_len, parser.data_end);

  ASSERT_EQ(0U, vtparse_parse(&parser, NULL, 0U));
  ASSERT_EQ(vtparse_has_event(&parser), false);


  PASS();
}


TEST t_mkcreflect(){
  do_mkcreflect();

  PASS();
}


TEST t_generic_print(){
  int  x[]     = { 1, 2, 3 };
  char *args[] = { "gcc", "hello.c", "-o", "hello" };

  PRINT(x, args);
  PASS();
}


TEST t_str_replace(){
  char *replaced = str_replace("hello world", "hello", "goodbye");

  printf("%s\n", replaced);
  free(replaced);
  PASS();
}
SUITE(s_eventemitter){
  RUN_TEST(t_eventemitter);
  PASS();
}
SUITE(s_forever){
  RUN_TEST(t_forever);
  PASS();
}
SUITE(s_libbeaufort){
  RUN_TEST(t_libbeaufort);
  PASS();
}
SUITE(s_murmurhash){
  RUN_TEST(t_murmurhash);
  PASS();
}
SUITE(s_dmt){
  RUN_TEST(t_dmt);
  RUN_TEST(t_dmt_summary);
  PASS();
}
SUITE(s_dmt_summary){
  RUN_TEST(t_dmt_summary);
  PASS();
}
SUITE(s_cansid){
  RUN_TEST(t_cansid);
  PASS();
}
SUITE(s_ansi_utils){
  RUN_TEST(t_ansi_utils);
  PASS();
}
SUITE(s_vtparse){
  RUN_TEST(t_vtparse_simple);
  RUN_TEST(t_vtparse_csi);
  PASS();
}
SUITE(s_microtar){
  RUN_TEST(t_microtar_write);
  RUN_TEST(t_microtar_read);
  PASS();
}
SUITE(s_workqueue){
  RUN_TEST(t_workqueue);
  PASS();
}
SUITE(s_vector){
  RUN_TEST(t_vector);
  PASS();
}
SUITE(s_occurrences){
  RUN_TEST(t_occurrences);
  PASS();
}
SUITE(s_str_replace){
  RUN_TEST(t_str_replace);
  PASS();
}
SUITE(s_time) {
  RUN_TEST(t_timestamp);
  PASS();
}
SUITE(s_spinner) {
  //RUN_TEST(t_libspinner);
  //RUN_TEST(t_spin);
  PASS();
}
SUITE(s_totp) {
  RUN_TEST(t_totp);
  PASS();
}
SUITE(s_qrcode) {
  RUN_TEST(t_qrcode);
  PASS();
}
SUITE(s_status) {
  RUN_TEST(t_statusbar);
  PASS();
}
SUITE(s_progress) {
  RUN_TEST(t_progressbar);
  PASS();
}
SUITE(s_path) {
  RUN_TEST(t_which);
  PASS();
}
SUITE(s_debug) {
  RUN_TEST(t_debug_print);
  PASS();
}
SUITE(s_string) {
  RUN_TEST(t_slug);
  PASS();
}


TEST t_md5(void){
  md5_ctx       ctx;
  const char    *IN = "hello world!";
  unsigned char hash[16];

  rhash_md5_init(&ctx);
  rhash_md5_update(&ctx, (const unsigned char *)IN, strlen(IN));
  rhash_md5_final(&ctx, hash);

  printf("MD5 of '%s' is '%s'\n",
         IN, stringfn_replace(stringfn_trim(stringfn_replace(stringfn_replace(b64_encode(hash, 16), '/', '_'), '=', ' ')), ' ', '_')
         );
  PASS();
}


TEST t_truncate(void){
  char *str = str_truncate("really long sentence", 2);

  printf("this should only be two characters: %s\n", str);

  PASS();
}


TEST t_catpath(void){
  char *some_path = NULL; // You must init the first path with NULL!

  catpath(&some_path, "/starts/with/slash-and-end-with-slash/");
  catpath(&some_path, "/other/path");
  printf("some_path: %s\n", some_path);
  free(some_path);
  PASS();
}


TEST t_regex(void){
  int        match_length;
  const char *string_to_search = "ahem.. 'hello world !' ..";
  re_t       pattern           = re_compile("[Hh]ello [Ww]orld\\s*[!]?");
  int        match_idx         = re_matchp(pattern, string_to_search, &match_length);

  ASSERT_GTE(match_idx, 0);
  if (match_idx >= 0) {
    printf("match at idx %i, %i chars long.\n", match_idx, match_length);
  }

  PASS();
}
SUITE(s_truncate) {
  RUN_TEST(t_truncate);
  PASS();
}
SUITE(s_catpath) {
  RUN_TEST(t_catpath);
  PASS();
}
SUITE(s_regex) {
  RUN_TEST(t_regex);
  PASS();
}
SUITE(s_md5) {
  RUN_TEST(t_md5);
  PASS();
}
SUITE(s_generic_print) {
  RUN_TEST(t_generic_print);
  PASS();
}

SUITE(s_sqldbal) {
  RUN_TEST(t_sqldbal);
  PASS();
}
SUITE(s_mkcreflect) {
  RUN_TEST(t_mkcreflect);
  PASS();
}
SUITE(s_json) {
  RUN_TEST(t_read_json_file);
  RUN_TEST(t_process_json_lines);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_json);
  RUN_SUITE(s_string);
  RUN_SUITE(s_debug);
  RUN_SUITE(s_time);
  RUN_SUITE(s_path);
  RUN_SUITE(s_progress);
  RUN_SUITE(s_qrcode);
  RUN_SUITE(s_totp);
  RUN_SUITE(s_spinner);
  RUN_SUITE(s_occurrences);
  RUN_SUITE(s_str_replace);
  RUN_SUITE(s_vector);
  RUN_SUITE(s_workqueue);
  RUN_SUITE(s_microtar);
  RUN_SUITE(s_dmt);
  RUN_SUITE(s_forever);
  RUN_SUITE(s_eventemitter);
  RUN_SUITE(s_regex);
  RUN_SUITE(s_catpath);
  RUN_SUITE(s_truncate);
  RUN_SUITE(s_dmt_summary);
  RUN_SUITE(s_md5);
  RUN_SUITE(s_vtparse);
  RUN_SUITE(s_cansid);
  RUN_SUITE(s_ansi_utils);
  RUN_SUITE(s_generic_print);
  RUN_SUITE(s_murmurhash);
  RUN_SUITE(s_libbeaufort);
  RUN_SUITE(s_mkcreflect);
  RUN_SUITE(s_sqldbal);
  GREATEST_MAIN_END();
  size_t used = do_dmt_summary();
  dbg(used, %lu);
  //ASSERT_EQ(used, 0);
}
