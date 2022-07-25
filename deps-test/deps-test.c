#define MKCREFLECT_IMPL
#define LAY_IMPLEMENTATION
#define MINIAUDIO_IMPLEMENTATION
////////////////////////////////////////////
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <math.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>
#include <wchar.h>
////////////////////////////////////////////
#include "c89atomic/c89atomic.h"
#include "deps-test/deps-test.h"
#include "generic-print/print.h"
#include "hidapi/hidapi/hidapi.h"
#include "hidapi/mac/hidapi_darwin.h"
#include "layout/layout.h"
#include "libforks/libforks.h"
#include "libusb/libusb/libusb.h"
#include "libusb/libusb/os/darwin_usb.h"
#include "log.h/log.h"
#include "miniaudio/miniaudio.h"
#include "ok-file-formats/ok_jpg.h"
#include "ok-file-formats/ok_png.h"
#include "ok-file-formats/ok_wav.h"
#include "tempdir.c/tempdir.h"
////////////////////////////////////////////
static int do_get_google();
static inline int file_exists(const char *path);

static char *EXECUTABLE_PATH_DIRNAME;

#define DEF_PORT    8080
#define MAX_NAME    40
static int port = DEF_PORT;
typedef struct {
  char name[MAX_NAME];
  char *descr;
} test_case_info;

typedef struct {
  int port;
} test_case_config;

char JSON_TESTS_FILE[] = ".tests.json",
     *JSON_TESTS_CONTENT;


static inline int file_exists(const char *path) {
  struct stat b;

  return(stat(path, &b));
}


void do_socket99_tcp_server(void *PARAM){
  int             v_true = 1;
  socket99_config cfg    = {
    .host        = "127.0.0.1",
    .port        = port,
    .server      = true,
    .nonblocking = true,
    .sockopts    = {
      { SO_REUSEADDR, &v_true, sizeof(v_true) },
    },
  };

  socket99_result res;
  bool            ok = socket99_open(&cfg, &res);

  if (!ok) {
    char buf[128];
    if (128 < socket99_snprintf(buf, 128, &res)) {
      socket99_fprintf(stderr, &res);
    } else {
      fprintf(stderr, "%s\n", buf);
    }
    FAIL();
  }

  struct pollfd fds[2];

  fds[0].fd     = res.fd;
  fds[0].events = POLLIN;

  ssize_t received  = 0;
  nfds_t  poll_fds  = 1;
  int     client_fd = -1;

  for ( ;;) {
    int poll_res = poll(fds, poll_fds, 1000 /* msec */);
    if (poll_res > 0) {
      if (fds[0].revents & POLLIN) {
        struct sockaddr address;
        socklen_t       addr_len;
        client_fd = accept(res.fd, &address, &addr_len);
        if (client_fd == -1) {
          if (errno == EAGAIN) {
            errno = 0;
            continue;
          } else {
            break;
          }
        } else {
          fds[1].fd     = client_fd;
          fds[1].events = POLLIN;
          poll_fds++;
        }
      } else if (fds[0].revents & POLLERR || fds[0].revents & POLLHUP) {
        printf("POLLERR / POLLHUP\n");
        break;
      }

      if (poll_fds > 1) {
        if (fds[1].revents & POLLIN) {
          char buf[1024];
          received = recv(fds[1].fd, buf, 1024, 0);

          if (received > 0) {
            buf[received] = '\0';
            printf("Got: '%s'\n", buf);
            close(client_fd);
          } else {
            if (errno == EAGAIN) {
              errno = 0;
            } else {
              fprintf(stderr, "recv: %s\n", strerror(errno));
              close(client_fd);
            }
          }

          if (received > 0) {
            break;
          }
        } else if (fds[1].revents & POLLERR || fds[1].revents & POLLHUP) {
          printf("POLLERR / POLLHUP\n");
          close(client_fd);
          break;
        }
      }
    }
  }

  close(res.fd);
} /* do_socket99_tcp_server */


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
  fprintf(stdout,
          "CANSID_FGCOLOR:%d"
          "\t"
          "CANSID_BGCOLOR:%d"
          "\t"
          "CANSID_ENDVAL:%d",
          CANSID_FGCOLOR,
          CANSID_BGCOLOR,
          CANSID_ENDVAL
          );
  printf(AC_YELLOW AC_ITALIC "===========================================================================" AC_RESETALL "\n");

  DEBUG_STATE();
  FEED("\x1b[30mBLACK");
  FEED("\x1b[34mBLUE");
  FEED("\x1b[30m\x1b[44mBLACK-BLUE");
  //FEED(AC_BLACK_BLUE "BLACK-BLUE");
  if (true) {
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


TEST t_socket99_tcp_client(void){
  socket99_config cfg = {
    .host = "127.0.0.1",
    .port = port,
  };

  socket99_result res;
  bool            ok = socket99_open(&cfg, &res);

  if (!ok) {
    socket99_fprintf(stderr, &res);
    return(false);
  }

  const char *msg     = "hello\n";
  size_t     msg_size = strlen(msg);

  ssize_t    sent = send(res.fd, msg, msg_size, 0);
  bool       pass = ((size_t)sent == msg_size);

  close(res.fd);
  PASS();
}


TEST t_layout(void){
  lay_context ctx;

  lay_init_context(&ctx);
  lay_reserve_items_capacity(&ctx, 1024);
  lay_id root = lay_item(&ctx);

  lay_set_size_xy(&ctx, root, 2500, 1500);
  lay_set_contain(&ctx, root, LAY_ROW);
  lay_id master_list = lay_item(&ctx);

  lay_insert(&ctx, root, master_list);
  lay_set_size_xy(&ctx, master_list, 600, 0);
  lay_set_behave(&ctx, master_list, LAY_VFILL);
  lay_set_contain(&ctx, master_list, LAY_COLUMN);
  lay_id content_view  = lay_item(&ctx);
  lay_id content_view0 = lay_item(&ctx);

  lay_insert(&ctx, root, content_view);
  lay_insert(&ctx, root, content_view0);
  lay_set_behave(&ctx, content_view, LAY_HFILL | LAY_VFILL);
  lay_set_behave(&ctx, content_view0, LAY_HFILL | LAY_VFILL);
  lay_run_context(&ctx);
  lay_vec4 master_list_rect   = lay_get_rect(&ctx, master_list);
  lay_vec4 content_view_rect  = lay_get_rect(&ctx, content_view);
  lay_vec4 content_view_rect0 = lay_get_rect(&ctx, content_view0);

  for (int i = 0; i < 4; i++) {
    log_debug("content_view_rect    #%d:   %d", i, content_view_rect[i]);
    log_debug("content_view_rect0   #%d:   %d", i, content_view_rect0[i]);
    log_debug("master_list_rect     #%d:   %d", i, master_list_rect[i]);
  }
  /*my_ui_library_draw_box_x_y_width_height(
   *  master_list_rect[0],
   *  master_list_rect[1],
   *  master_list_rect[2],
   *  master_list_rect[3]);*/
  lay_reset_context(&ctx);
  lay_destroy_context(&ctx);
  PASS();
}


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
SUITE(s_socket99_tcp){
  pthread_t th;

  pthread_create(&th, NULL, do_socket99_tcp_server, (void *)12311);
  RUN_TEST(t_socket99_tcp_client);
  PASS();
}
SUITE(s_layout){
  RUN_TEST(t_layout);
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
//  RUN_TEST(t_libspinner);
  RUN_TEST(t_spin);
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


static void child_main2(libforks_ServerConn conn, int socket_fd) {
  (void)conn;
  while (true) {
    char c;
    assert(read(socket_fd, &c, 1) == 1);
    c = toupper(c);
    assert(write(socket_fd, &c, 1) == 1);
  }
}


int do_libforks_test2() {
  libforks_ServerConn conn;

  assert(libforks_start(&conn) == libforks_OK);

  int socket_fd;

  assert(libforks_fork(
           conn,
           NULL,
           &socket_fd,
           NULL,
           child_main2
           ) == libforks_OK);

  puts("Type text and press enter");
  puts("Exit with Ctrl+D");

  while (true) {
    char c;
    int  read_res = read(STDIN_FILENO, &c, 1);
    if (read_res == 0) {
      break;
    }
    assert(read_res == 1);

    assert(write(socket_fd, &c, 1) == 1);
    assert(read(socket_fd, &c, 1) == 1);
    assert(write(STDOUT_FILENO, &c, 1) == 1);
  }

  assert(libforks_stop(conn) == libforks_OK);
  return(0);
}


static void child_main1(libforks_ServerConn conn, int socket_fd) {
  assert(libforks_free_conn(conn) == libforks_OK);
  assert(socket_fd == -1);
  puts("child process started");
  sleep(1);
  puts("child process exited");
}


int do_libforks_test1() {
  libforks_ServerConn conn;

  assert(libforks_start(&conn) == libforks_OK);

  assert(libforks_fork(
           conn,
           NULL,
           NULL,
           NULL,
           child_main1
           ) == libforks_OK);
  assert(libforks_stop(conn) == libforks_OK);
  puts("main process exited");
  return(0);
}


TEST t_libforks1(void){
  int res = do_libforks_test1();

  ASSERT_EQ(res, 0);
  PASS();
}


TEST t_hidapi(void){
  int           res;
  unsigned char buf[256];

#define MAX_STR    255
  wchar_t                wstr[MAX_STR];
  hid_device             *handle;
  int                    i;

  struct hid_device_info *devs, *cur_dev;
  hid_darwin_set_open_exclusive(0);
  devs    = hid_enumerate(0x0, 0x0);
  cur_dev = devs;
  while (cur_dev) {
    printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path,
           cur_dev->serial_number);
    printf("\n");
    printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
    printf("  Product:      %ls\n", cur_dev->product_string);
    printf("  Release:      %hx\n", cur_dev->release_number);
    printf("  Interface:    %d\n", cur_dev->interface_number);
    printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
    printf("\n");
    cur_dev = cur_dev->next;
  }
  hid_free_enumeration(devs);

  PASS();
}


static void print_devs(libusb_device **devs){
  libusb_device *dev;
  int           i = 0, j = 0;
  uint8_t       path[8];

  while ((dev = devs[i++]) != NULL) {
    struct libusb_device_descriptor desc;
    int                             r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
      fprintf(stderr, "failed to get device descriptor");
      return;
    }

    printf("%04x:%04x (bus %d, device %d)",
           desc.idVendor, desc.idProduct,
           libusb_get_bus_number(dev), libusb_get_device_address(dev));

    r = libusb_get_port_numbers(dev, path, sizeof(path));
    if (r > 0) {
      printf(" path: %d", path[0]);
      for (j = 1; j < r; j++) {
        printf(".%d", path[j]);
      }
    }
    printf("\n");
  }
}


TEST t_libusb1(void){
  libusb_device **devs;
  int           r;
  ssize_t       cnt;

  r = libusb_init(NULL);
  if (r < 0) {
    return(r);
  }

  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0) {
    libusb_exit(NULL);
    return((int)cnt);
  }

  print_devs(devs);
  libusb_free_device_list(devs, 1);

  libusb_exit(NULL);
  PASS();
}


int verbose = 0;


static void print_endpoint_comp(const struct libusb_ss_endpoint_companion_descriptor *ep_comp){
  printf("      USB 3.0 Endpoint Companion:\n");
  printf("        bMaxBurst:           %u\n", ep_comp->bMaxBurst);
  printf("        bmAttributes:        %02xh\n", ep_comp->bmAttributes);
  printf("        wBytesPerInterval:   %u\n", ep_comp->wBytesPerInterval);
}


static void print_endpoint(const struct libusb_endpoint_descriptor *endpoint){
  int i, ret;

  printf("      Endpoint:\n");
  printf("        bEndpointAddress:    %02xh\n", endpoint->bEndpointAddress);
  printf("        bmAttributes:        %02xh\n", endpoint->bmAttributes);
  printf("        wMaxPacketSize:      %u\n", endpoint->wMaxPacketSize);
  printf("        bInterval:           %u\n", endpoint->bInterval);
  printf("        bRefresh:            %u\n", endpoint->bRefresh);
  printf("        bSynchAddress:       %u\n", endpoint->bSynchAddress);

  for (i = 0; i < endpoint->extra_length;) {
    if (LIBUSB_DT_SS_ENDPOINT_COMPANION == endpoint->extra[i + 1]) {
      struct libusb_ss_endpoint_companion_descriptor *ep_comp;

      ret = libusb_get_ss_endpoint_companion_descriptor(NULL, endpoint, &ep_comp);
      if (LIBUSB_SUCCESS != ret) {
        continue;
      }

      print_endpoint_comp(ep_comp);

      libusb_free_ss_endpoint_companion_descriptor(ep_comp);
    }

    i += endpoint->extra[i];
  }
}


static void print_altsetting(const struct libusb_interface_descriptor *interface){
  uint8_t i;

  printf("    Interface:\n");
  printf("      bInterfaceNumber:      %u\n", interface->bInterfaceNumber);
  printf("      bAlternateSetting:     %u\n", interface->bAlternateSetting);
  printf("      bNumEndpoints:         %u\n", interface->bNumEndpoints);
  printf("      bInterfaceClass:       %u\n", interface->bInterfaceClass);
  printf("      bInterfaceSubClass:    %u\n", interface->bInterfaceSubClass);
  printf("      bInterfaceProtocol:    %u\n", interface->bInterfaceProtocol);
  printf("      iInterface:            %u\n", interface->iInterface);

  for (i = 0; i < interface->bNumEndpoints; i++) {
    print_endpoint(&interface->endpoint[i]);
  }
}


static void print_2_0_ext_cap(struct libusb_usb_2_0_extension_descriptor *usb_2_0_ext_cap){
  printf("    USB 2.0 Extension Capabilities:\n");
  printf("      bDevCapabilityType:    %u\n", usb_2_0_ext_cap->bDevCapabilityType);
  printf("      bmAttributes:          %08xh\n", usb_2_0_ext_cap->bmAttributes);
}


static void print_ss_usb_cap(struct libusb_ss_usb_device_capability_descriptor *ss_usb_cap){
  printf("    USB 3.0 Capabilities:\n");
  printf("      bDevCapabilityType:    %u\n", ss_usb_cap->bDevCapabilityType);
  printf("      bmAttributes:          %02xh\n", ss_usb_cap->bmAttributes);
  printf("      wSpeedSupported:       %u\n", ss_usb_cap->wSpeedSupported);
  printf("      bFunctionalitySupport: %u\n", ss_usb_cap->bFunctionalitySupport);
  printf("      bU1devExitLat:         %u\n", ss_usb_cap->bU1DevExitLat);
  printf("      bU2devExitLat:         %u\n", ss_usb_cap->bU2DevExitLat);
}


static void print_bos(libusb_device_handle *handle){
  struct libusb_bos_descriptor *bos;
  uint8_t                      i;
  int                          ret;

  ret = libusb_get_bos_descriptor(handle, &bos);
  if (ret < 0) {
    return;
  }

  printf("  Binary Object Store (BOS):\n");
  printf("    wTotalLength:            %u\n", bos->wTotalLength);
  printf("    bNumDeviceCaps:          %u\n", bos->bNumDeviceCaps);

  for (i = 0; i < bos->bNumDeviceCaps; i++) {
    struct libusb_bos_dev_capability_descriptor *dev_cap = bos->dev_capability[i];

    if (dev_cap->bDevCapabilityType == LIBUSB_BT_USB_2_0_EXTENSION) {
      struct libusb_usb_2_0_extension_descriptor *usb_2_0_extension;

      ret = libusb_get_usb_2_0_extension_descriptor(NULL, dev_cap, &usb_2_0_extension);
      if (ret < 0) {
        return;
      }

      print_2_0_ext_cap(usb_2_0_extension);
      libusb_free_usb_2_0_extension_descriptor(usb_2_0_extension);
    } else if (dev_cap->bDevCapabilityType == LIBUSB_BT_SS_USB_DEVICE_CAPABILITY) {
      struct libusb_ss_usb_device_capability_descriptor *ss_dev_cap;

      ret = libusb_get_ss_usb_device_capability_descriptor(NULL, dev_cap, &ss_dev_cap);
      if (ret < 0) {
        return;
      }

      print_ss_usb_cap(ss_dev_cap);
      libusb_free_ss_usb_device_capability_descriptor(ss_dev_cap);
    }
  }

  libusb_free_bos_descriptor(bos);
} /* print_bos */


static void print_interface(const struct libusb_interface *interface){
  int i;

  for (i = 0; i < interface->num_altsetting; i++) {
    print_altsetting(&interface->altsetting[i]);
  }
}


static void print_configuration(struct libusb_config_descriptor *config){
  uint8_t i;

  printf("  Configuration:\n");
  printf("    wTotalLength:            %u\n", config->wTotalLength);
  printf("    bNumInterfaces:          %u\n", config->bNumInterfaces);
  printf("    bConfigurationValue:     %u\n", config->bConfigurationValue);
  printf("    iConfiguration:          %u\n", config->iConfiguration);
  printf("    bmAttributes:            %02xh\n", config->bmAttributes);
  printf("    MaxPower:                %u\n", config->MaxPower);

  for (i = 0; i < config->bNumInterfaces; i++) {
    print_interface(&config->interface[i]);
  }
}


static void print_device(libusb_device *dev, libusb_device_handle *handle){
  struct libusb_device_descriptor desc;
  unsigned char                   string[256];
  const char                      *speed;
  int                             ret;
  uint8_t                         i;

  switch (libusb_get_device_speed(dev)) {
  case LIBUSB_SPEED_LOW:          speed = "1.5M"; break;
  case LIBUSB_SPEED_FULL:         speed = "12M"; break;
  case LIBUSB_SPEED_HIGH:         speed = "480M"; break;
  case LIBUSB_SPEED_SUPER:        speed = "5G"; break;
  case LIBUSB_SPEED_SUPER_PLUS:   speed = "10G"; break;
  default:                        speed = "Unknown";
  }

  ret = libusb_get_device_descriptor(dev, &desc);
  if (ret < 0) {
    fprintf(stderr, "failed to get device descriptor");
    return;
  }

  printf("Dev (bus %u, device %u): %04X - %04X speed: %s\n",
         libusb_get_bus_number(dev), libusb_get_device_address(dev),
         desc.idVendor, desc.idProduct, speed);

  if (!handle) {
    libusb_open(dev, &handle);
  }

  if (handle) {
    if (desc.iManufacturer) {
      ret = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, string, sizeof(string));
      if (ret > 0) {
        printf("  Manufacturer:              %s\n", (char *)string);
      }
    }

    if (desc.iProduct) {
      ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
      if (ret > 0) {
        printf("  Product:                   %s\n", (char *)string);
      }
    }

    if (desc.iSerialNumber && verbose) {
      ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
      if (ret > 0) {
        printf("  Serial Number:             %s\n", (char *)string);
      }
    }
  }

  if (verbose) {
    for (i = 0; i < desc.bNumConfigurations; i++) {
      struct libusb_config_descriptor *config;

      ret = libusb_get_config_descriptor(dev, i, &config);
      if (LIBUSB_SUCCESS != ret) {
        printf("  Couldn't retrieve descriptors\n");
        continue;
      }

      print_configuration(config);

      libusb_free_config_descriptor(config);
    }

    if (handle && desc.bcdUSB >= 0x0201) {
      print_bos(handle);
    }
  }

  if (handle) {
    libusb_close(handle);
  }
} /* print_device */


static int test_wrapped_device(const char *device_name){
  libusb_device_handle *handle;
  int                  r, fd;

  fd = open(device_name, O_RDWR);
  if (fd < 0) {
    printf("Error could not open %s: %s\n", device_name, strerror(errno));
    return(1);
  }
  r = libusb_wrap_sys_device(NULL, fd, &handle);
  if (r) {
    printf("Error wrapping device: %s: %s\n", device_name, libusb_strerror(r));
    close(fd);
    return(1);
  }
  print_device(libusb_get_device(handle), handle);
  close(fd);
  return(0);
}


TEST t_libusb2(void){
  int           verbose      = 1;
  const char    *device_name = NULL;
  libusb_device **devs;
  ssize_t       cnt;
  int           r, i;

  r = libusb_init(NULL);
  if (r < 0) {
    return(r);
  }

  if (device_name) {
    r = test_wrapped_device(device_name);
  } else {
    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0) {
      libusb_exit(NULL);
      return(1);
    }

    for (i = 0; devs[i]; i++) {
      print_device(devs[i], NULL);
    }

    libusb_free_device_list(devs, 1);
  }

  libusb_exit(NULL);
  PASS();
}


void record_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount){
  ma_encoder *pEncoder = (ma_encoder *)pDevice->pUserData;

  MA_ASSERT(pEncoder != NULL);
  ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount, NULL);
  (void)pOutput;
}


void play_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount){
  ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;

  if (pDecoder == NULL) {
    return;
  }

  ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

  (void)pInput;
}


static char *get_self_path(void){
  char     dir[PATH_MAX];
  uint32_t size = sizeof dir;

  _NSGetExecutablePath(dir, &size);
  return(dir);
}


int do_miniaudio_record_file(char *record_file){
  ma_result         result;
  ma_encoder_config encoderConfig;
  ma_encoder        encoder;
  ma_device_config  deviceConfig;
  ma_device         device;

  encoderConfig = ma_encoder_config_init(ma_encoding_format_wav, ma_format_f32, 2, 44100);

  if (ma_encoder_init_file(record_file, &encoderConfig, &encoder) != MA_SUCCESS) {
    printf("Failed to initialize output file.\n");
    return(-1);
  }

  deviceConfig                  = ma_device_config_init(ma_device_type_capture);
  deviceConfig.capture.format   = encoder.config.format;
  deviceConfig.capture.channels = encoder.config.channels;
  deviceConfig.sampleRate       = encoder.config.sampleRate;
  deviceConfig.dataCallback     = record_callback;
  deviceConfig.pUserData        = &encoder;

  result = ma_device_init(NULL, &deviceConfig, &device);
  if (result != MA_SUCCESS) {
    printf("Failed to initialize capture device.\n");
    return(-2);
  }

  result = ma_device_start(&device);
  if (result != MA_SUCCESS) {
    ma_device_uninit(&device);
    printf("Failed to start device.\n");
    return(-3);
  }

  usleep(1000 * 1000);

  ma_device_uninit(&device);
  ma_encoder_uninit(&encoder);

  return(0);
} /* do_miniaudio_record_file */


int do_miniaudio_play_file(char *wav_file){
  ma_result result;
  ma_engine engine;

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    printf("Failed to initialize audio engine.");
    return(-1);
  }


  float len = 0;

  // ma_sound_get_cursor_in_seconds(&engine,&len);
  printf("ma_sound_get_cursor_in_seconds:%f\n", len);

  ma_sound sound;

  result = ma_sound_init_from_file(&engine, wav_file, 0, NULL, NULL, &sound);
  if (result != MA_SUCCESS) {
    return(result);
  }

//ma_sound_set_stop_time_in_pcm_frames(&sound, ma_engine_get_time(&engine) + (ma_engine_get_sample_rate(&engine) * 2));


  ma_sound_start(&sound);

  //ma_engine_play_sound(&engine, wav_file, NULL);

  usleep(1000 * 1000);


  ma_engine_uninit(&engine);
  return(0);
}


TEST t_miniaudio_play_file(void *PLAY_FILE){
  int res;

  res = do_miniaudio_play_file((char *)PLAY_FILE);
  ASSERT_EQ(res, 0);
  printf("play ok- %s\n", (char *)PLAY_FILE);
  PASS();
}


TEST t_miniaudio_record_file(void *RECORD_FILE){
  int res;

  res = do_miniaudio_record_file((char *)RECORD_FILE);
  ASSERT_EQ(res, 0);
  printf("recorded ok- %s\n", (char *)RECORD_FILE);
  PASS();
}


TEST t_tempdir(void){
  char *temp_dir = gettempdir();

  fprintf(stdout, "temp_dir:%s\n", temp_dir);
  PASS();
}


TEST t_libforks2(void){
  if (isatty(STDOUT_FILENO)) {
    int res = do_libforks_test2();
    ASSERT_EQ(res, 0);
    PASS();
  }else{
    PASS();
  }
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


TEST t_c89atomic(void){
  c89atomic_flag a0 = 0;
  c89atomic_flag b0 = 1;
  c89atomic_bool r0 = c89atomic_flag_test_and_set(&b0);

  PRINT("r0:", r0);

  c89atomic_uint8 a = 42;
  c89atomic_uint8 b = 123;

  c89atomic_store_8(&a, b);

  PRINT("a:", a);
  PRINT("b:", b);

  PASS();
}


TEST t_ok_file_format_wav(void){
  char *wav_file = malloc(1024);

  sprintf(wav_file, "%s/../sounds/key_space_down.wav", EXECUTABLE_PATH_DIRNAME);
  dbg(wav_file, %s);
  FILE   *file = fopen(wav_file, "rb");
  ok_wav audio = ok_wav_read(file, OK_WAV_DEFAULT_DECODE_FLAGS);

  fclose(file);
  if (audio.data) {
    printf("Got audio! Length: %f seconds\n", (audio.num_frames / audio.sample_rate));
    free(audio.data);
  }
  PASS();
}


TEST t_ok_file_format_jpg(void){
  char *jpg_file = malloc(1024);

  sprintf(jpg_file, "%s/../images/accomplishments.jpg", EXECUTABLE_PATH_DIRNAME);
  FILE   *file = fopen(jpg_file, "rb");
  ok_jpg image = ok_jpg_read(file, OK_JPG_COLOR_FORMAT_RGBA);

  fclose(file);
  if (image.data) {
    printf("Got JPG image! Size: %li x %li\n", (long)image.width, (long)image.height);
    free(image.data);
  }
  PASS();
}


TEST t_ok_file_format_png(void){
  char *png_file = malloc(1024);

  sprintf(png_file, "%s/../images/vttest1.png", EXECUTABLE_PATH_DIRNAME);
  FILE   *file = fopen(png_file, "rb");
  ok_png image = ok_png_read(file, OK_PNG_COLOR_FORMAT_RGBA);

  fclose(file);
  if (image.data) {
    printf("Got PNG image! Size: %li x %li\n", (long)image.width, (long)image.height);
    free(image.data);
  }
  PASS();
}

SUITE(s_ok_file_formats) {
  RUN_TEST(t_ok_file_format_wav);
  RUN_TEST(t_ok_file_format_png);
  RUN_TEST(t_ok_file_format_jpg);
}

SUITE(s_c89atomic) {
  RUN_TEST(t_c89atomic);
}

SUITE(s_miniaudio) {
  char play_file[1024];

  sprintf(&play_file, "%s/../sounds/key_space_down.wav", EXECUTABLE_PATH_DIRNAME);
  char record_file[1024] = "/tmp/record.wav";

  RUN_TESTp(t_miniaudio_play_file, (void *)play_file);
  RUN_TESTp(t_miniaudio_record_file, (void *)record_file);
  RUN_TESTp(t_miniaudio_play_file, (void *)record_file);
}

SUITE(s_hidapi) {
  RUN_TEST(t_hidapi);
}
SUITE(s_libusb) {
  RUN_TEST(t_libusb1);
  RUN_TEST(t_libusb2);
}
SUITE(s_tempdir) {
  RUN_TEST(t_tempdir);
}
SUITE(s_libforks) {
  RUN_TEST(t_libforks1);
  RUN_TEST(t_libforks2);
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

SUITE(s_json) {
  RUN_TEST(t_read_json_file);
  RUN_TEST(t_process_json_lines);
  PASS();
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };

  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
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
  RUN_SUITE(s_layout);
  RUN_SUITE(s_socket99_tcp);
  RUN_SUITE(s_libforks);
  RUN_SUITE(s_tempdir);
  RUN_SUITE(s_hidapi);
  RUN_SUITE(s_libusb);
  RUN_SUITE(s_miniaudio);
  RUN_SUITE(s_c89atomic);
  RUN_SUITE(s_ok_file_formats);
  GREATEST_MAIN_END();
  size_t used = do_dmt_summary();

  dbg(used, %lu);
  assert(used == 0);
} /* main */
