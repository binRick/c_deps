#define MKCREFLECT_IMPL
#define LAY_IMPLEMENTATION
#define MINIAUDIO_IMPLEMENTATION
#define TB_IMPL
#define HTTPSERVER_IMPL
#define HTTPSERVER_LISTEN_PORT    8199
//#define DEBUG_MEMORY
////////////////////////////////////////////
#include <stdio.h>
////////////////////////////////////////////
#include "termbox2/termbox.h"
////////////////////////////////////////////
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <poll.h>
#include <signal.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wchar.h>
////////////////////////////////////////////
#ifdef DEBUG_MEMORY
#include "debug-memory/debug_memory.h"
#endif
////////////////////////////////////////////
#include "ansi-rgb-utils/ansi-rgb-utils.h"
#include "ansi-utils/ansi-utils.h"
#include "bench/bench.h"
#include "bitfield/bitfield.h"
#include "c-timestamp/timestamp.h"
#include "c89atomic/c89atomic.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "chfreq.c/chfreq.h"
#include "container_of/container_of.h"
#include "deps-test/deps-test.h"
#include "dotenv-c/src/dotenv.h"
#include "emojis/emojis.h"
#include "extname.c/src/extname.h"
#include "flingfd/src/flingfd.h"
#include "generic-print/print.h"
#include "genpassword.c/src/genpassword.h"
#include "hashmap.h/hashmap.h"
#include "hidapi/hidapi/hidapi.h"
#include "hidapi/mac/hidapi_darwin.h"
#include "httpserver.h/httpserver.h"
#include "incbin/incbin.h"
#include "is_number.c/is_number.h"
#include "jinja2-cli/jinja2-cli.h"
#include "kitty/kitty.h"
#include "layout/layout.h"
#include "levenshtein.c/levenshtein.h"
#include "libconfuse/src/confuse.h"
#include "libforks/libforks.h"
#include "libtinyfiledialogs/tinyfiledialogs.h"
#include "libtrycatch/trycatch.h"
#include "libusb/libusb/libusb.h"
#include "libusb/libusb/os/darwin_usb.h"
#include "libut/include/libut.h"
#include "libut/include/ringbuf.h"
#include "libut/include/utvector.h"
#include "libyuarel/yuarel.h"
#include "list/src/list.h"
#include "log.h/log.h"
#include "miniaudio/miniaudio.h"
#include "minmax/include/minmax.h"
#include "msgbox/msgbox.h"
#include "ok-file-formats/ok_jpg.h"
#include "ok-file-formats/ok_png.h"
#include "ok-file-formats/ok_wav.h"
#include "path-basename.c/src/path-basename.h"
#include "path-normalize.c/src/path-normalize.h"
#include "path_module/src/path.h"
#include "pidfile/pidfile.h"
#include "posix-tree/posix-tree.h"
#include "process/process.h"
#include "querystring.c/querystring.h"
#include "semver.c/semver.h"
#include "sense-c/src/git.h"
#include "sense-c/src/lang.h"
#include "str-flatten.c/src/str-flatten.h"
#include "subhook/subhook.h"
#include "submodules/seethe/seethe.h"
#include "tai64n/tai64n.h"
#include "tempdir.c/tempdir.h"
#include "uptime/include/uptime/uptime.h"
#include "uri.c/uri.h"
#include "url.h/url.h"
#include "url_router/include/url_router/url_router.h"
#include "wildcardcmp/wildcardcmp.h"
//#include "libucl/include/ucl.h"
////////////////////////////////////////////
void __attribute__((constructor)) premain(){
  char *s = malloc(1024);

  sprintf(s, "%s", "test");
  char *s0 = strdup(s);
}
void __attribute__((destructor)) postmain(){
#ifdef DEBUG_MEMORY
  printf("\nChecking for memory leak\n");
  print_allocated_memory();
#endif
}


static int do_get_google();
static inline int file_exists(const char *path);

static char *EXECUTABLE_PATH_DIRNAME;
/*
 * ////////////////////////////////////////
 *  BENCHMARK_QTY(benchmark_name, 20)
 *  //DO_WORK
 *  END_BENCHMARK(benchmark_name)
 *  BENCHMARK_SUMMARY(benchmark_name);
 * ////////////////////////////////////////
 *  MEASURE(measurement_name)
 *  //DO_WORK
 *  END_MEASURE(measurement_name)
 *  MEASURE_SUMMARY(measurement_name);
 * ////////////////////////////////////////
 */

#define DEF_PORT    HTTPSERVER_LISTEN_PORT
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


int request_target_is(struct http_request_s *request, char const *target) {
  http_string_t url = http_request_target(request);
  int           len = strlen(target);

  return(len == url.len && memcmp(url.buf, target, url.len) == 0);
}


struct http_server_s *poll_server;
struct http_req_s    *_s;


void handle_request(struct http_request_s *request) {
  http_request_connection(request, HTTP_AUTOMATIC);
  http_string_t url = http_request_target(request);

  {
    dbg(url.buf, %s);
    char                   *U             = stringfn_substring(url.buf, 0, url.len);
    struct StringFNStrings lines          = stringfn_split_lines_and_trim(url.buf);
    char                   *req_data      = lines.strings[lines.count - 1];
    struct StringFNStrings params_strings = stringfn_split(req_data, '&');
    struct StringFNStrings url_strings    = stringfn_split(U, '/');
    struct Vector          *url_v         = vector_new();
    struct StringBuffer    *url_sb        = stringbuffer_new();
    for (size_t usi = 0; usi < url_strings.count; usi++) {
      if (strlen(url_strings.strings[usi]) > 0) {
        vector_push(url_v, url_strings.strings[usi]);
        stringbuffer_append_string(url_sb, "/");
        stringbuffer_append_string(url_sb, url_strings.strings[usi]);
      }
    }
    char                   *normalized_url = stringbuffer_to_string(url_sb);
    dbg(normalized_url, %s);
    struct StringFNStrings normalized_url_strings = stringfn_split(normalized_url, '/');


    int                 p;
    struct yuarel       yurl;
    struct yuarel_param params[params_strings.count];
    char                *parts[3];
    char                *url_string;
    asprintf(&url_string, "http://localhost:%d%s?%s", HTTPSERVER_LISTEN_PORT, normalized_url, req_data);
    dbg(url_string, %s);

    if (-1 == yuarel_parse(&yurl, url_string)) {
      fprintf(stderr, "Could not parse url!\n");
      return(1);
    }

    if (false) {
      printf("scheme:\t%s\n", yurl.scheme);
      printf("host:\t%s\n", yurl.host);
    }
    dbg(params_strings.count, %d);
    dbg(req_data, %s);
    dbg(lines.count, %d);
    dbg(normalized_url_strings.count, %d);
    printf("port:\t%d\n", yurl.port);
    printf("path:\t%s\n", yurl.path);
    printf("query:\t%s\n", yurl.query);
    printf("fragment:\t%s\n", yurl.fragment);


    printf("Print Path items\n");
    if (normalized_url_strings.count > 1 && strlen(normalized_url) > 1) {
      yuarel_split_path(yurl.path, parts, normalized_url_strings.count - 1);
      for (int i = 0; i < normalized_url_strings.count - 1; i++) {
        if (parts[i]) {
          printf("part #%d: %s\n", i, parts[i]);
        }
      }
    }
    printf("Query string parameters:\n");
    p = yuarel_parse_query(yurl.query, '&', params, params_strings.count);
    while (p-- > 0) {
      if (params[p].key && params[p].val) {
        printf("\t%s: %s\n", params[p].key, params[p].val);
      }
    }


    char *uri_encoded = uri_encode("Betty's favorite language is Français");
    char *uri_decoded = uri_decode(req_data);

    char *u;
    asprintf(&u, "\n\turl:%s\n\tlen:%d\n", url.buf, url.len);
    if (false) {
      dbg(uri_decoded, %s);
      dbg(uri_encoded, %s);
      printf("%s", u);
    }
  }
  struct http_response_s *response = http_response_init();
  http_response_status(response, 200);
  char                   *R;
  asprintf(&R, "%lld", timestamp());
  if (false) {
    printf("R:%s\n", R);
  }
  if (request_target_is(request, "/echo")) {
    http_string_t body = http_request_body(request);
    http_response_header(response, "Content-Type", "text/plain");
    http_response_body(response, body.buf, body.len);
  } else if (request_target_is(request, "/host")) {
    http_string_t ua = http_request_header(request, "Host");
    http_response_header(response, "Content-Type", "text/plain");
    http_response_body(response, ua.buf, ua.len);
  } else if (request_target_is(request, "/ts")) {
    http_response_header(response, "Content-Type", "text/plain");
    http_response_body(response, R, strlen(R));
  } else {
    http_response_header(response, "Content-Type", "text/plain");
    http_response_body(response, R, strlen(R));
  }
  http_respond(request, response);
} /* handle_request */

struct http_server_s *server;


void handle_sigterm(int signum) {
  (void)signum;
  free(server);
  free(poll_server);
  exit(0);
}


int httpserver_main() {
  signal(SIGTERM, handle_sigterm);
  server = http_server_init(HTTPSERVER_LISTEN_PORT, handle_request);
  http_server_listen(server);
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
  char *name    = "ls";
  char *path    = (char *)which(name);
  char *ffmpeg  = (char *)which("ffmpeg");
  char *convert = (char *)which("convert");
  char *meson   = (char *)which("meson");
  char *sh      = (char *)which("sh");
  char *bash    = (char *)which("bash");
  char *env     = (char *)which("env");
  char *passh   = (char *)which("passh");

  printf("PATH:        %s\n", getenv("PATH"));
  printf("\n<WHICH>%s: %s\n\n", "name", path ? path : "not found");
  printf("\n<WHICH>%s: %s\n\n", "ffmpeg", ffmpeg ? ffmpeg : "not found");
  printf("\n<WHICH>%s: %s\n\n", "convert", convert ? convert : "not found");
  printf("\n<WHICH>%s: %s\n\n", "meson", meson ? meson : "not found");
  printf("\n<WHICH>%s: %s\n\n", "sh", sh ? sh : "not found");
  printf("\n<WHICH>%s: %s\n\n", "env", env ? env : "not found");
  printf("\n<WHICH>%s: %s\n\n", "passh", passh ? passh : "not found");
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
  printf(AC_YELLOW AC_ITALIC "\n===========================================================================" AC_RESETALL "\n");

  DEBUG_STATE();
  state = cansid_init();
  FEED("\x1b[30m\x1b[44mBLACK-BLUEBG");
  DEBUG_STATE();
  state = cansid_init();
  FEED("\x1b[30mBLACK");
  DEBUG_STATE();
  state = cansid_init();
  FEED("\x1b[34mBLUE");
  DEBUG_STATE();
  state = cansid_init();
  FEED("\x1b[44mBLUEBG");
  DEBUG_STATE();
  state = cansid_init();
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
  dbg(started, % c);
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

  // BENCHMARK_SUMMARY(benchmark_name);
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


void H(size_t I, void *HANDLED_ITEM){
  printf(" Handled Item: #%lu> %s\n", I, (char *)HANDLED_ITEM);
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
  vector_push(vector, "test push");
  vector_push(vector, "test push");
  vector_push(vector, "test push");

  struct Vector *V = vector_new();

  vector_push(V, "v0");
  vector_push(V, "v1");
  vector_push(V, "v2");


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
  char     *dir = calloc(1, PATH_MAX);
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
  int res = do_libforks_test2();

  ASSERT_EQ(res, 0);
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


TEST t_libtinyfiledialogs(void){
  char const    *lTmp;
  char const    *lTheSaveFileName;
  char const    *lTheOpenFileName;
  char const    *lTheSelectFolderName;
  char const    *lTheHexColor;
  char const    *lWillBeGraphicMode;
  unsigned char lRgbColor[3];
  FILE          *lIn;
  char          lBuffer[1024];
  char          lThePassword[1024];
  char const    *lFilterPatterns[2] = { "*.txt", "*.text" };

  lWillBeGraphicMode = tinyfd_inputBox("tinyfd_query", NULL, NULL);

  if (lWillBeGraphicMode) {
    strcpy(lBuffer, "graphic mode: ");
  }else {
    strcpy(lBuffer, "console mode: ");
  }
  strcat(lBuffer, tinyfd_response);
  strcpy(lThePassword, "tinyfiledialogs v");
  strcat(lThePassword, tinyfd_version);
  tinyfd_messageBox(lThePassword, lBuffer, "ok", "info", 0);

  if (lWillBeGraphicMode && !tinyfd_forceConsole) {
    tinyfd_forceConsole = !tinyfd_messageBox("Hello World",
                                             "graphic dialogs [yes] / console mode [no]?",
                                             "yesno", "question", 1);
  }

  lTmp = tinyfd_inputBox(
    "a password box", "your password will be revealed", NULL);

  if (!lTmp) {
    return(1);
  }

  /* copy lTmp because saveDialog would overwrites
   * inputBox static buffer in basicinput mode */

  strcpy(lThePassword, lTmp);

  lTheSaveFileName = tinyfd_saveFileDialog(
    "let us save this password",
    "passwordFile.txt",
    2,
    lFilterPatterns,
    NULL);

  if (!lTheSaveFileName) {
    tinyfd_messageBox(
      "Error",
      "Save file name is NULL",
      "ok",
      "error",
      1);
    return(1);
  }

  lIn = fopen(lTheSaveFileName, "w");
  if (!lIn) {
    tinyfd_messageBox(
      "Error",
      "Can not open this file in write mode",
      "ok",
      "error",
      1);
    return(1);
  }
  fputs(lThePassword, lIn);
  fclose(lIn);

  lTheOpenFileName = tinyfd_openFileDialog(
    "let us read the password back",
    "",
    2,
    lFilterPatterns,
    NULL,
    0);

  if (!lTheOpenFileName) {
    tinyfd_messageBox(
      "Error",
      "Open file name is NULL",
      "ok",
      "error",
      1);
    return(1);
  }

  lIn = fopen(lTheOpenFileName, "r");

  if (!lIn) {
    tinyfd_messageBox(
      "Error",
      "Can not open this file in read mode",
      "ok",
      "error",
      1);
    return(1);
  }
  lBuffer[0] = '\0';
  fgets(lBuffer, sizeof(lBuffer), lIn);
  fclose(lIn);

  tinyfd_messageBox("your password is",
                    lBuffer, "ok", "info", 1);

  lTheSelectFolderName = tinyfd_selectFolderDialog(
    "let us just select a directory", NULL);

  if (!lTheSelectFolderName) {
    tinyfd_messageBox(
      "Error",
      "Select folder name is NULL",
      "ok",
      "error",
      1);
    return(1);
  }

  tinyfd_messageBox("The selected folder is",
                    lTheSelectFolderName, "ok", "info", 1);

  lTheHexColor = tinyfd_colorChooser(
    "choose a nice color",
    "#FF0077",
    lRgbColor,
    lRgbColor);

  if (!lTheHexColor) {
    tinyfd_messageBox(
      "Error",
      "hexcolor is NULL",
      "ok",
      "error",
      1);
    return(1);
  }

  tinyfd_messageBox("The selected hexcolor is",
                    lTheHexColor, "ok", "info", 1);


  PASS();
} /* t_libtinyfiledialogs */


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


struct my_struct {
  int            id;           /* key */
  char           name[21];
  UT_hash_handle hh;           /* makes this structure hashable */
};

struct my_struct *users = NULL;


void add_user(int user_id, const char *name){
  struct my_struct *s;

  HASH_FIND_INT(users, &user_id, s);    /* id already in the hash? */
  if (s == NULL) {
    s     = (struct my_struct *)malloc(sizeof *s);
    s->id = user_id;
    HASH_ADD_INT(users, id, s);      /* id is the key field */
  }
  strcpy(s->name, name);
}

struct my_struct *find_user(int user_id){
  struct my_struct *s;

  HASH_FIND_INT(users, &user_id, s);    /* s: output pointer */
  return(s);
}


void delete_user(struct my_struct *user){
  HASH_DEL(users, user);    /* user: pointer to deletee */
  free(user);
}


void delete_all(){
  struct my_struct *current_user;
  struct my_struct *tmp;

  HASH_ITER(hh, users, current_user, tmp) {
    HASH_DEL(users, current_user);      /* delete it (users advances to next) */
    free(current_user);                 /* free it */
  }
}


void print_users(){
  struct my_struct *s;

  for (s = users; s != NULL; s = (struct my_struct *)(s->hh.next)) {
    printf("user id %d: name %s\n", s->id, s->name);
  }
}


int by_name(const struct my_struct *a, const struct my_struct *b){
  return(strcmp(a->name, b->name));
}


int by_id(const struct my_struct *a, const struct my_struct *b){
  return(a->id - b->id);
}


const char *getl(const char *prompt){
  static char buf[21];
  char        *p;

  printf("%s? ", prompt); fflush(stdout);
  p = fgets(buf, sizeof(buf), stdin);
  if (p == NULL || (p = strchr(buf, '\n')) == NULL) {
    puts("Invalid input!");
    exit(EXIT_FAILURE);
  }
  *p = '\0';
  return(buf);
}


TEST t_bitfield(void){
  bitfield_t *bf = bitfield_new(100);

  bitfield_mark(bf, 77);
  bitfield_unmark(bf, 50);
  bool im = bitfield_is_marked(bf, 77);

  ASSERT_EQ(im, true);
  im = bitfield_is_marked(bf, 78);
  ASSERT_EQ(im, false);
  printf("77th bit is marked\n");
  printf("78th bit is not marked\n");
  PASS();
}


TEST t_bench(void){
  FILE *file;

  file = fopen("/etc/passwd", "r");
  fclose(file);


  FILE *file1;

  file1 = fopen("/etc/passwd", "r");
  fclose(file1);

  PASS();
}


TEST t_minmax(void){
  int val;

  val = max(2, 5);
  ASSERT_EQ(val, 5);
  PASS();
}


INCBIN(char *, MesonBuildTyped, "meson.build");


TEST t_incbin(void){
  printf("gMesonBuildTypedData:%s\n", gMesonBuildTypedData[0]);
  printf("gMesonBuildTypedSize:%d\n", gMesonBuildTypedSize);
  PASS();
}

static volatile size_t svr_recv_msgs = 0;
static volatile size_t cl_recv_msgs  = 0;


void msg_update_server(msg_Conn *conn, msg_Event event, msg_Data data) {
  if (event == msg_request) {
    msg_send(conn, data);
    svr_recv_msgs++;
  }
}


void msg_update_client(msg_Conn *conn, msg_Event event, msg_Data data) {
  if (event == msg_connection_ready) {
    msg_Data data = msg_new_data("hello!");
    msg_get(conn, data, msg_no_context);
    msg_delete_data(data);
  }
  if (event == msg_reply) {
    printf("Got the reply: '%s'.\n", msg_as_str(data));
    cl_recv_msgs++;
  }
}


TEST t_msgbox_tcp_client(void){
  msg_connect("tcp://127.0.0.1:2101", msg_update_client, msg_no_context);
  while (cl_recv_msgs < 1) {
    msg_runloop(10);
  }
  ASSERT_GTE(cl_recv_msgs, 1);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on client", cl_recv_msgs);
  PASSm(msg);
}


TEST t_msgbox_udp_client(void){
  msg_connect("udp://127.0.0.1:2100", msg_update_client, msg_no_context);
  while (cl_recv_msgs < 1) {
    msg_runloop(10);
  }
  ASSERT_GTE(cl_recv_msgs, 1);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on client", cl_recv_msgs);
  PASSm(msg);
}


TEST t_msgbox_tcp_server(void){
  msg_listen("tcp://*:2101", msg_update_server);
  while (svr_recv_msgs < 2) {
    msg_runloop(10);
  }
  ASSERT_GTE(svr_recv_msgs, 2);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on server", svr_recv_msgs);
  PASSm(msg);
}


TEST t_msgbox_udp_server(void){
  msg_listen("udp://*:2100", msg_update_server);
  while (svr_recv_msgs < 2) {
    msg_runloop(10);
  }
  ASSERT_GTE(svr_recv_msgs, 2);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on server", svr_recv_msgs);
  PASSm(msg);
}


TEST t_msgbox(void){
  PASS();
}


TEST t_termbox2(void){
  struct tb_event ev;
  int             y = 0;

  tb_init();

  tb_printf(0, y++, TB_GREEN, 0, "hello from termbox");
  tb_printf(0, y++, 0, 0, "width=%d height=%d", tb_width(), tb_height());
  tb_printf(0, y++, 0, 0, "press any key...");
  tb_present();

  tb_poll_event(&ev);

  y++;
  tb_printf(0, y++, 0, 0, "event type=%d key=%d ch=%c", ev.type, ev.key, ev.ch);
  tb_printf(0, y++, 0, 0, "press any key to quit...");
  tb_present();

  tb_poll_event(&ev);
  tb_shutdown();

  PASS();
}


TEST t_httpserver(void){
  int i = httpserver_main();

  ASSERT_EQ(i, 0);
  PASS();
}
struct parsed_data {
  char *name;
  int  age;
  int  size;
};


void querystring_parser(void *data, char *fst, char *snd) {
  struct parsed_data *parsed_data = (struct parsed_data *)data;

  if (strcmp(fst, "name") == 0) {
    parsed_data->name = snd;
  }else if (strcmp(fst, "size") == 0) {
    parsed_data->size = atoi(snd);
  }else if (strcmp(fst, "age") == 0) {
    parsed_data->age = atoi(snd);
  }
}


TEST t_kitty_send_text(void){
  char *ok = kitty_send_text("pwd");

  ASSERT_EQ(ok, true);
  char *text = kitty_get_last_cmd_output();

  printf(AC_RESETALL AC_YELLOW "text:%s\n%lu bytes\n"AC_RESETALL,
         text,
         strlen(text)
         );
  PASS();
}


TEST t_kitty_get_colors(void){
  char *text = kitty_get_colors();

  printf(AC_RESETALL AC_YELLOW "text:%s\n%lu bytes\n"AC_RESETALL,
         text,
         strlen(text)
         );
  PASS();
}


TEST t_kitty_list_fonts(void){
  char *text = kitty_list_fonts();

  printf(AC_RESETALL AC_BLUE "text:%s\n%lu bytes\n"AC_RESETALL,
         text,
         strlen(text)
         );
  PASS();
}


TEST t_kitty_query_terminal(void){
  char *text = kitty_query_terminal();

  printf(AC_RESETALL AC_BLUE "text:%s\n%lu bytes\n"AC_RESETALL,
         text,
         strlen(text)
         );
  PASS();
}


TEST t_kitty_ls_kittens(void){
  char *text = kitty_ls_kittens();

  printf(AC_RESETALL AC_YELLOW "text:%s\n%lu bytes\n"AC_RESETALL,
         text,
         strlen(text)
         );
  PASS();
}


TEST t_kitty_get_text(void){
  char *text = kitty_get_text();

  printf("text:%s\n%lu bytes\n",
         text,
         strlen(text)
         );
  PASS();
}


TEST t_kitty_set_window_title(void){
  char *title;

  asprintf(&title, "window %d", getpid());
  bool ok = kitty_set_window_title(title);

  ASSERT_EQ(ok, true);
  PASS();
}


TEST t_kitty_set_tab_title(void){
  char *title;

  asprintf(&title, "pid %d", getpid());
  bool ok = kitty_set_tab_title(title);

  ASSERT_EQ(ok, true);
  PASS();
}


TEST t_kitty_ls(void){
  char *ls = kitty_get_ls();

  printf("ls text:%s\n%lu bytes\n",
         ls,
         strlen(ls)
         );
  PASS();
}


TEST t_kitty_set_layout_vertical(void){
  bool ok = kitty_set_layout("vertical");

  ASSERT_EQ(ok, true);

  PASS();
}


TEST t_kitty_reset_tab_color(void){
  bool ok = kitty_set_tab_color("active_fg", "NONE");

  ASSERT_EQ(ok, true);
  ok = kitty_set_tab_color("active_bg", "NONE");
  ASSERT_EQ(ok, true);
  ok = kitty_set_tab_color("inactive_fg", "NONE");
  ASSERT_EQ(ok, true);
  ok = kitty_set_tab_color("inactive_bg", "NONE");
  ASSERT_EQ(ok, true);
  PASS();
}


TEST t_kitty_set_tab_color(void){
  bool ok = kitty_set_tab_color("active_fg", "green");

  ASSERT_EQ(ok, true);
  ok = kitty_set_tab_color("active_bg", "black");
  ASSERT_EQ(ok, true);
  ok = kitty_set_tab_color("inactive_fg", "yellow");
  ASSERT_EQ(ok, true);
  ok = kitty_set_tab_color("inactive_bg", "blue");
  ASSERT_EQ(ok, true);
  PASS();
}


TEST t_kitty_set_layout_stack(void){
  bool ok = kitty_set_layout("stack");

  ASSERT_EQ(ok, true);

  PASS();
}


TEST t_kitty_set_font_size(void){
  bool ok = kitty_set_font_size(30);

  ASSERT_EQ(ok, true);
  PASS();
}


TEST t_kitty_image(void){
  bool ok = kitty_draw_image();

  ASSERT_EQ(ok, true);
  PASS();
}


TEST t_kitty(void){
  bool ok = kitty_clear_screen();

  ASSERT_EQ(ok, true);

  PASS();
}


TEST t_my_cwd(void){
  char *d = get_my_cwd();

  PASS();
}


TEST t_jinja2_cli(void){
  struct jinja2_render_template_t *CFG = jinja2_init_config();

  CFG->input_json_string = "{\"abc\":\"world\"}";
  CFG->template_s        = "hello {{ abc }}";
  CFG->debug_mode        = true;
  CFG->debug_mode        = false;
  int res = jinja2_render_template(CFG);

  ASSERT_EQ(res, 0);
  ASSERT_EQ(CFG->success, true);
  ASSERT_EQ(strcmp(CFG->output_s, "hello world"), 0);

  printf(AC_RESETALL AC_BLUE "%s" AC_RESETALL "\n", CFG->output_s);

  PASS();
}

typedef struct {
  char *name;
  int  cash;
} account_t;


void deposit(int *current_balance, int change){
  account_t *acc = container_of(current_balance, account_t, cash);

  printf("Increased %s's account by %d\n", acc->name, change);
}


TEST t_path_normalize(void){
  char *path = NULL;

  assert(NULL == path_normalize(NULL));

  path = path_normalize("/home//stephen//");
  assert(0 == strcmp("/home/stephen/", path));
  free(path);

  path = path_normalize("home//stephen//");
  assert(0 == strcmp("home/stephen/", path));
  free(path);

  path = path_normalize("/home//stephen//");
  assert(0 == strcmp("/home/stephen/", path));
  free(path);

  path = path_normalize("////home//stephen");
  assert(0 == strcmp("/home/stephen", path));
  free(path);

  PASS();
}


TEST t_hashmap_h_4(){
  struct hashmap_s hashmap;
  int              x = 42;

  ASSERT_EQ(0, hashmap_create(1, &hashmap));
  ASSERT_EQ(0, hashmap_put(&hashmap, "foo", (unsigned)strlen("foo"), &x));
  ASSERT_EQ(0, hashmap_remove(&hashmap, "foo", (unsigned)strlen("foo")));
  hashmap_destroy(&hashmap);
  PASS();
}


TEST t_hashmap_h_3(){
  const char *const key = "foo&bar";

  struct hashmap_s  hashmap;
  int               x = 42;

  ASSERT_EQ(0, hashmap_create(1, &hashmap));
  ASSERT_EQ(0, hashmap_put(&hashmap, key, 3, &x));

  /* Use a new string here so that we definitely have a different pointer key
   * being provided. */
  ASSERT_EQ(key, hashmap_remove_and_return_key(&hashmap, "foo",
                                               (unsigned)strlen("foo")));
  hashmap_destroy(&hashmap);

  PASS();
}


TEST t_hashmap_h_2(){
  struct hashmap_s hashmap;
  int              x = 42;

  ASSERT_EQ(0, hashmap_create(1, &hashmap));
  ASSERT_EQ(0u, hashmap_num_entries(&hashmap));
  ASSERT_EQ(0, hashmap_put(&hashmap, "foo", (unsigned)strlen("foo"), &x));
  ASSERT_EQ(1u, hashmap_num_entries(&hashmap));
  ASSERT_EQ(0, hashmap_remove(&hashmap, "foo", (unsigned)strlen("foo")));
  ASSERT_EQ(0u, hashmap_num_entries(&hashmap));
  hashmap_destroy(&hashmap);
  PASS();
}


TEST t_flingfd_client(){
  int fd = fileno(stdout);

  flingfd_simple_send("/tmp/some_unique_path", fd);
  printf("fd sent\n");
  PASS();
}


TEST t_flingfd_server(){
  int fd = flingfd_simple_recv("/tmp/some_unique_path");

  printf("fd recvd\n");
  write(fd, "Hello world\n", 12);
  PASS();
}
subhook_t foo_hook1;


void foo1(int x) {
  printf("real foo1(%d) called\n", x);
}


void my_foo1(int x) {
  subhook_remove(foo_hook1);
  printf("hooked foo1(%d) called\n", x);
  foo1(x);
  subhook_install(foo_hook1);
}


TEST t_subhook1(){
  foo_hook1 = subhook_new((void *)foo1, (void *)my_foo1, 0);
  subhook_install(foo_hook1);
  foo1(123);
  subhook_remove(foo_hook1);
  subhook_free(foo_hook1);
  PASS();
}


int cb_validate_bookmark(cfg_t *cfg, cfg_opt_t *opt){
  /* only validate the last bookmark */
  cfg_t *sec = cfg_opt_getnsec(opt, cfg_opt_size(opt) - 1);

  if (!sec) {
    cfg_error(cfg, "section is NULL!?");
    return(-1);
  }
  if (cfg_getstr(sec, "machine") == NULL) {
    cfg_error(cfg, "machine option must be set for bookmark '%s'", cfg_title(sec));
    return(-1);
  }
  return(0);
}


TEST t_posix_tree(){
  tree_demo();
  PASS();
}


TEST t_seethe(){
  debug("debug log");
  info("informational log");
  notice("notice log");
  warning("warning log");
  error("error log");
  critical("critical log");

  // sample usage
  info("starting program");
  char *my_string;
  if (!(my_string = malloc(BUFSIZ * sizeof(char)))) {
    critical("failed to make size-%zu buffer. exiting\n", BUFSIZ);
    abort();
  }
  debug("getting input from user");
  error("fgets failed to return a proper result");

  PASS();
}


TEST t_color_boxes(){
  char *boxes = get_color_boxes();

  printf("%s", boxes);
  ASSERT_GTE(strlen(boxes), 100);
  PASS();
}


TEST t_sense_c(){
  int lang = get_lang("../");

  printf("../ lang: %s\n", get_lang_name(lang));

  lang = get_lang("./");
  printf("./ lang: %s\n", get_lang_name(lang));

  lang = get_lang("./confirm1");
  printf("./confirm1 lang: %s\n", get_lang_name(lang));


  int git = has_git("./");

  if (git) {
    printf("Is git!\n");
  } else {
    printf("Is not git.\n");
  }

  int local = is_local_git("./");

  if (local) {
    printf("Is local!\n");
  } else {
    printf("Is not local.\n");
  }

  PASS();
}


TEST t_tai64n(){
  size_t ts = tai64ts();

  printf("ts: %lu\n", ts);
  struct tai64n *now = tai64();

  printf("now sec: %lu\n", now->sec);
  printf("now nano: %lu\n", now->nano);
  ASSERT_GTE(now->sec, 999);
  ASSERT_GTE(now->nano, 999);
  ASSERT_GTE(ts, 999);
  char *msg;

  asprintf(&msg, "now: %lu | %lu | ts: %lu |",
           now->sec,
           now->nano,
           ts
           );
  PASSm(msg);
}


TEST t_tty_copy(){
  char *s;

  asprintf(&s, "tty_copy-copied-text-%lu", (size_t)timestamp());
  size_t wrote_chars = ansi_utils_tty_copy(s);
  char   *msg;

  ASSERT_GTE(wrote_chars, 3);
  asprintf(&msg, "Wrote %lu chars", wrote_chars);
  PASSm(msg);
}


TEST t_libconfuse(){
  char *cfg_s      = "\
\n\
\# this is a comment\n\
\n\
verbose=true\n\
#server = \"localhost\"\n\
user = \"joe\"\n\
debug = 17\n\
targets = {\"Fish\", \"Cat\"}\n\
#delay = 6.77712472349623E-139\n\
env {\n\
	foo = bar\n\
	baz = foo\n\
}\n\
include(/tmp/simple-inc.conf)\n\
\n";
  char *cfg_inc0_s = "\n\
bookmark baz {\n\
 machine = \"ssh://localhost\"\n\
 login = baz\n\
}\n\
\n";

  fsio_write_text_file("/tmp/simple.conf", cfg_s);
  fsio_write_text_file("/tmp/simple-inc.conf", cfg_inc0_s);
  static cfg_bool_t verbose   = cfg_false;
  static char       *server   = NULL;
  static double     delay     = 1.356e-32;
  static char       *username = NULL;
  static long int   debug     = 1;


  size_t    i;
  cfg_opt_t proxy_opts[] = {
    CFG_INT("type",         0,                        CFGF_NONE),
    CFG_STR("host",         NULL,                     CFGF_NONE),
    CFG_STR_LIST("exclude", "{localhost, .localnet}", CFGF_NONE),
    CFG_INT("port",         21,                       CFGF_NONE),
    CFG_END()
  };
  cfg_opt_t bookmark_opts[] = {
    CFG_STR("machine",       NULL,       CFGF_NONE),
    CFG_INT("port",          21,         CFGF_NONE),
    CFG_STR("login",         NULL,       CFGF_NONE),
    CFG_STR("password",      NULL,       CFGF_NONE),
    CFG_STR("directory",     NULL,       CFGF_NONE),
    CFG_BOOL("passive-mode", cfg_false,  CFGF_NONE),
    CFG_SEC("proxy",         proxy_opts, CFGF_NONE),
    CFG_END()
  };
  cfg_opt_t opts[] = {
    CFG_SIMPLE_BOOL("verbose", &verbose),
    CFG_SIMPLE_STR("server",   &server),
    CFG_SIMPLE_STR("user",     &username),
    CFG_SIMPLE_INT("debug",    &debug),
    CFG_SIMPLE_FLOAT("delay",  &delay),
    CFG_STR_LIST("targets",    0,            CFGF_MULTI),
    CFG_SEC("bookmark",        bookmark_opts,CFGF_MULTI | CFGF_TITLE),
    CFG_SEC("env",             NULL,         CFGF_KEYSTRVAL),
    CFG_FUNC("include",        &cfg_include),
    CFG_END(),
  };
  cfg_t     *cfg;

  cfg = cfg_init(opts, CFGF_NONE);
  if (cfg_parse(cfg, "/tmp/simple.conf") == CFG_PARSE_ERROR) {
    return(1);
  }

  cfg_print_indent(cfg, stdout, 1);

  printf("verbose: %s\n", verbose ? "true" : "false");
  printf("server: %s\n", server);
  printf("username: %s\n", username);
  printf("debug: %ld\n", debug);
  printf("delay: %G\n", delay);

  cfg_t *sec = cfg_getsec(cfg, "env");

  if (sec) {
    unsigned int i;

    for (i = 0; i < cfg_num(sec); i++) {
      cfg_opt_t *opt = cfg_getnopt(sec, i);

      printf(AC_RESETALL AC_YELLOW "%s = \"%s\"" AC_RESETALL "\n", cfg_opt_name(opt), cfg_opt_getstr(opt));
    }
  }

  cfg_free(cfg);

  PASS();
} /* t_libconfuse */


TEST t_dotenv(){
  fsio_write_text_file("/tmp/.env",
                       "EXTRA_VAR=\"xxxxxxxxx\""
                       "\nV1=\"v1data\""
                       "\nV2='v2data'"
                       "\nV3=v3data"
                       "\nEMPTY="
                       "\n"
                       );
  env_load("/tmp/.env", false);
  printf("EXTRA_VAR: %s\n", getenv("EXTRA_VAR"));
  printf("V1: %s\n", getenv("V1"));
  printf("V2: %s\n", getenv("V2"));
  printf("V3: %s\n", getenv("V3"));
  printf("EMPTY: %s\n", getenv("EMPTY"));
  PASS();
}


TEST t_chfreq(){
  char     *str = "110aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz102";
  uint32_t **f  = chfreq(str);
  uint32_t *cur = NULL;

  printf("str: %s\n", str);
  for (int i = 0; NULL != (cur = f[i]); ++i) {
    char c  = cur[0];
    int  cf = cur[1];
    printf("#%d> char: %c | qty: %d |\n", i, c, cf);
  }
  PASS();
}


TEST t_uptime(){
  unsigned long long u = getUptime();

  printf("Uptime: %lu\n", u);
  ASSERT_GTE(u, 0);
  PASS();
}


TEST t_semver(){
  char     current[] = "1.5.10";
  char     compare[] = "2.3.0";

  semver_t current_version = {};
  semver_t compare_version = {};

  if (semver_parse(current, &current_version)
      || semver_parse(compare, &compare_version)) {
    fprintf(stderr, "Invalid semver string\n");
    return(-1);
  }

  int resolution = semver_compare(compare_version, current_version);

  if (resolution == 0) {
    printf("Versions %s is equal to: %s\n", compare, current);
  }else if (resolution == -1) {
    printf("Version %s is lower than: %s\n", compare, current);
  }else {
    printf("Version %s is higher than: %s\n", compare, current);
  }

  // Free allocated memory when we're done
  semver_free(&current_version);
  semver_free(&compare_version);
  return(0);

  PASS();
}


TEST t_path_module(){
  char        *pathname = "/projects/path_module/path.c";
  struct Path path      = path_parse(pathname);

  printf("dirname: %.*s\n", (int)path.dirname_len, path.dirname);
  printf("basename: %s\n", path.basename);

  // copy to another buffer
  char dirname[path.dirname_len + 1];

  memset(dirname, 0, sizeof(dirname));

  memcpy(dirname, path.dirname, path.dirname_len);
  printf("your dirname: %s\n", dirname);
  PASS();
}


TEST t_pidfile(){
  char *pid_file_name = "/tmp/pid.txt";
  FILE *fp            = fopen(pid_file_name, "wt");

  if (!fp) {
    fprintf(stderr, "failed to open pid file:%s:%s\n",
            pid_file_name, strerror(errno));
    abort();
  }
  fprintf(fp, "%d\n", (int)getpid());
  fclose(fp);
  PASS();
}


TEST t_str_flatten(){
  char *arr[] = {
    "this",
    "was",
    "ripped",
    "from",
    "sphia"
  };

  char *s = str_flatten(arr, 0, 5);

  puts(s);
  int r = strcmp("this was ripped from sphia", s);

  ASSERT_EQ(r, 0);
  PASS();
}


TEST t_hashmap_h_0(){
  PASS();
}


TEST t_hashmap_h_1(){
  struct hashmap_s hashmap;
  int              x = 42;

  ASSERT_EQ(0, hashmap_create(1, &hashmap));
  ASSERT_EQ(0, hashmap_put(&hashmap, "foo", (unsigned)strlen("foo"), &x));
  ASSERT_EQ(&x, hashmap_get(&hashmap, "foo", (unsigned)strlen("foo")));
  hashmap_destroy(&hashmap);
  PASS();
}


TEST t_url_router(){
  char             *str1 = "hello world1";
  char             *str2 = "woooooooooo";
  char             *arg;
  char             *data;

  URL_ROUTER_ERROR err;
  struct Dict      *args;
  UrlRouter        *r = url_router_new();

  err = url_router_insert(r, "/a/b/c", str1);
  if (err != URL_ROUTER_E_OK) {
    printf("Insert /a/b/c failed\n");
    return(-1);
  }

  err = url_router_match(r, "/a/b/c", &args, (void **)&data);
  if (err == URL_ROUTER_E_OK) {
    printf("data:    %s\n", data);
  }
  url_router_dict_free(args);

  err = url_router_insert(r, "/r/:var/:var", str2);
  if (err != URL_ROUTER_E_OK) {
    printf("Insert /r/:var/c failed\n");
    return(-1);
  }

  err = url_router_match(r, "/r/b/c", &args, (void **)&data);
  if (err == URL_ROUTER_E_OK) {
    char *var = dict_get(args, "var");
    if (var != NULL) {
      printf("Args: %s\n", var);
    }
  }
  url_router_dict_free(args);
  url_router_free(r);

  printf("Done\n");

  PASS();
} /* t_url_router */


TEST t_c_timestamp(void){
  timestamp_t ts;

  ts.sec    = 0;
  ts.offset = 0;
  ts.nsec   = -1;
  dbg(timestamp_valid(&ts), %d);

  ts.nsec = 1000000000;
  dbg(!timestamp_valid(&ts), %d);

  ts.nsec   = 0;
  ts.offset = -23 * 60 - 60;
  dbg(!timestamp_valid(&ts), %d);

  ts.offset = +23 * 60 + 60;
  dbg(!timestamp_valid(&ts), %d);

  ts.offset = 0;
  ts.sec    = INT64_C(-62135596801);
  dbg(!timestamp_valid(&ts), %d);
  ts.sec = INT64_C(253402387140);
  timestamp_t ts1;
  struct tm   tm1;

  ts.sec    = INT64_C(-62135551755);
  ts.nsec   = 0;
  ts.offset = 0;
  memset(&tm1, 0, sizeof(tm1));
  dbg(timestamp_to_tm_utc(&ts, &tm1.tm_year), %d);
  dbg(timestamp_to_tm_utc(&ts, &tm1.tm_mon), %d);
  dbg(timestamp_to_tm_utc(&ts, &tm1.tm_hour), %d);
  dbg(timestamp_to_tm_utc(&ts, &tm1.tm_sec), %d);


  PASS();
}


TEST t_genpassword_c(void){
  int passed = true;

  srand(1337);

  int  length    = 10;
  char *password = generate_password(length);

  if (strlen(password) == length) {
  } else {
    passed = false;
    printf("\x1B[31mFirst test failed. \n");     // Print in red
    printf("Generated password: %s, at length: %i\n", password, length);
  }
  printf("\x1B[32mFirst test passed.:      '%s' \n", password);      // Print in green

  // free memory
  free(password);

  // Second test
  length   = 15;
  password = generate_password(length);
  if (strlen(password) == length) {
    printf("\x1B[32mSecond test passed. \n");     // Print in green
  } else {
    passed = false;
    printf("\x1B[31mSecond test failed. \n");     // Print in red
    printf("Generated password: %s, at length: %i\n", password, length);
  }

  printf("\x1B[32msecond test passed.:      '%s' \n", password);      // Print in green
  // Return to normal color.
  printf("\x1B[0m");

  // free memory
  free(password);
  PASS();
}


TEST t_list_iterate_reverse(void){
  list_t          *langs = list_new();

  list_node_t     *c    = list_rpush(langs, list_node_new("c"));
  list_node_t     *js   = list_rpush(langs, list_node_new("js"));
  list_node_t     *ruby = list_rpush(langs, list_node_new("ruby"));

  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(langs, LIST_TAIL);

  while ((node = list_iterator_next(it))) {
    fprintf(stderr, "\tITERATE> %s\n", (char *)node->val);
  }

  list_iterator_destroy(it);
  list_destroy(langs);
  PASS();
}


TEST t_list_iterate(void){
  list_t          *langs = list_new();

  list_node_t     *c    = list_rpush(langs, list_node_new("c"));
  list_node_t     *js   = list_rpush(langs, list_node_new("js"));
  list_node_t     *ruby = list_rpush(langs, list_node_new("ruby"));

  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(langs, LIST_HEAD);

  while ((node = list_iterator_next(it))) {
    fprintf(stderr, "\tITERATE> %s\n", (char *)node->val);
  }

  list_iterator_destroy(it);
  list_destroy(langs);
  PASS();
}


TEST t_list_find(void){
  list_t      *langs = list_new();
  list_node_t *js    = list_rpush(langs, list_node_new("js"));
  list_node_t *a     = list_find(langs, "js");
  list_node_t *c     = list_find(langs, "ABSENT");

  assert(js == a);
  assert(NULL == c);

  list_destroy(langs);

  PASS();
}


TEST t_list_indexed(void){
  list_t      *list = list_new();
  list_node_t *a    = list_node_new("a");
  list_node_t *b    = list_node_new("b");
  list_node_t *c    = list_node_new("c");

  list_rpush(list, a);
  list_rpush(list, b);
  list_rpush(list, c);

  assert(a == list_at(list, 0));
  assert(b == list_at(list, 1));
  assert(c == list_at(list, 2));
  assert(NULL == list_at(list, 3));

  assert(c == list_at(list, -1));
  assert(b == list_at(list, -2));
  assert(a == list_at(list, -3));
  assert(NULL == list_at(list, -4));

  list_destroy(list);
  PASS();
}


TEST t_list_push(void){
  list_t      *list = list_new();
  list_node_t *a    = list_node_new("a");
  list_node_t *b    = list_node_new("b");
  list_node_t *c    = list_node_new("c");

  list_rpush(list, a);
  list_rpush(list, b);
  list_rpush(list, c);

  assert(a == list->head);
  assert(c == list->tail);
  assert(3 == list->len);
  assert(b == a->next);
  assert(NULL == a->prev);
  assert(c == b->next);
  assert(a == b->prev);
  assert(NULL == c->next);
  assert(b == c->prev);

  list_destroy(list);
  PASS();
}


TEST t_list_node(void){
  char        *val  = "some value";
  list_node_t *node = list_node_new(val);

  assert(node->val == val);
  free(node);
  PASS();
}


TEST t_extname_c(void){
  assert(strcmp(extname("some/extension.ext"), ".ext") == 0);
  assert(strcmp(extname(".derp"), ".derp") == 0);
  assert(strcmp(extname("."), ".") == 0);
  assert(strcmp(extname("nothing"), "") == 0);
  PASS();
}


TEST t_container_of(void){
  account_t *acc = calloc(1, sizeof(account_t));

  acc->name = strdup("Alice");
  deposit(&acc->cash, 100);
  PASS();
}


TEST t_wildcardcmp(void){
  PASS();
}


TEST t_is_number(void){
  const char *str = "1.0";
  int        is_num;

  is_num = is_number("1.0", 3);
  assert(is_num);

  is_num = is_number_with("1.", 2, ALLOW_EMPTY_POST_DOT);
  assert(is_num);

  is_num = is_number("1.", 2);
  assert(!is_num);
  PASS();
}


TEST t_url_h(void){
  char       *gh_url = "git://git@github.com:jwerle/url.h.git";
  char       *url    = "http://user:pass@subdomain.host.com:8080/p/a/t/h?query=string#hash";

  url_data_t *parsed    = url_parse(url);
  url_data_t *gh_parsed = url_parse(gh_url);

  assert(parsed);
  assert(gh_parsed);

  url_data_inspect(parsed);
  url_data_inspect(gh_parsed);
  PASS();
}


TEST t_levenshtein(void){
  char *w1 = "aaaaaaaaaa";
  char *w2 = "aaaaaaaaaa";

  printf("%s:%s -> %zu\n", w1, w2, levenshtein(w1, w2));
  w1 = "bbbbbbbbb";
  w2 = "aaaaaaaaaa";
  printf("%s:%s -> %zu\n", w1, w2, levenshtein(w1, w2));
  PASS();
}


TEST t_querystring(void){
  char               *qs;
  struct parsed_data data = {
    .name = "Anonymous",
    .age  = -1,
    .size = -1,
  };

  asprintf(&qs, "name=%s&age=%d&aaaaaaaaaa=123&size=%d", "abc", 123, 1000);

  parse_querystring(qs, (void *)&data, querystring_parser);

  printf("name: %s, age: %d, size: %d\n", data.name, data.age, data.size);
  PASS();
}


TEST t_libtrycatch(void){
  try {
    puts("try1");
    try {
      puts("try2");
    } catch(ex) {
      puts("this should not be called");
    }

    try {
      throw(7);
    } catch(ex) {
      rethrow;
    }
    throw(5);
  } catch(ex) {
    printf("caught %d (should be 7)\n", ex);
  }

  PASS();
}


TEST t_emojis(void){
  size_t        id              = 0;
  struct Vector *emojis_names_v = get_emojis_names_v();

  printf("%lu emoji names\n", vector_size(emojis_names_v));
  for (size_t i = 0; i < 10; i++) {
    struct emojis_t *e = get_emoji_t(i);
    printf("%lu: %s -> %s [index_by_name:%d|emoji_t_by_name:%s|%s]\n",
           i,
           e->name, e->emoji,
           get_emoji_t_index_by_name(e->name),
           get_emoji_t_by_name(e->name)->name, get_emoji_t_by_name(e->name)->emoji
           );
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
SUITE(s_flingfd_client) {
  RUN_TEST(t_flingfd_client);
}
SUITE(s_flingfd_server) {
  RUN_TEST(t_flingfd_server);
}
SUITE(s_posix_tree) {
  RUN_TEST(t_posix_tree);
}
SUITE(s_seethe) {
  RUN_TEST(t_seethe);
}
SUITE(s_color_boxes) {
  RUN_TEST(t_color_boxes);
}
SUITE(s_list){
  RUN_TEST(t_list_node);
  RUN_TEST(t_list_push);
  RUN_TEST(t_list_indexed);
  RUN_TEST(t_list_find);
  RUN_TEST(t_list_iterate);
  RUN_TEST(t_list_iterate_reverse);
}

SUITE(s_sense_c) {
  RUN_TEST(t_sense_c);
}
SUITE(s_tai64n) {
  RUN_TEST(t_tai64n);
}
SUITE(s_tty_copy) {
  RUN_TEST(t_tty_copy);
}
SUITE(s_libconfuse) {
  RUN_TEST(t_libconfuse);
}
SUITE(s_subhook) {
  RUN_TEST(t_subhook1);
}
SUITE(s_dotenv) {
  RUN_TEST(t_dotenv);
}
SUITE(s_chfreq) {
  RUN_TEST(t_chfreq);
}
SUITE(s_uptime) {
  RUN_TEST(t_uptime);
}
SUITE(s_semver) {
  RUN_TEST(t_semver);
}
SUITE(s_path_module) {
  RUN_TEST(t_path_module);
}
SUITE(s_pidfile) {
  RUN_TEST(t_pidfile);
}
SUITE(s_str_flatten) {
  RUN_TEST(t_str_flatten);
}

SUITE(s_hashmap_h) {
  RUN_TEST(t_hashmap_h_0);
  RUN_TEST(t_hashmap_h_1);
  RUN_TEST(t_hashmap_h_2);
  RUN_TEST(t_hashmap_h_3);
  RUN_TEST(t_hashmap_h_4);
}
SUITE(s_url_router) {
  RUN_TEST(t_url_router);
}
SUITE(s_path_normalize) {
  RUN_TEST(t_path_normalize);
}
SUITE(s_c_timestamp) {
  RUN_TEST(t_c_timestamp);
}
SUITE(s_genpassword_c) {
  RUN_TEST(t_genpassword_c);
}
SUITE(s_extname_c) {
  RUN_TEST(t_extname_c);
}
SUITE(s_container_of) {
  RUN_TEST(t_container_of);
}
SUITE(s_wildcardcmp) {
  RUN_TEST(t_wildcardcmp);
}


SUITE(s_is_number) {
  RUN_TEST(t_is_number);
}

SUITE(s_url_h) {
  RUN_TEST(t_url_h);
}


SUITE(s_ok_file_formats) {
  RUN_TEST(t_ok_file_format_wav);
  RUN_TEST(t_ok_file_format_png);
  RUN_TEST(t_ok_file_format_jpg);
}

SUITE(s_libtinyfiledialogs) {
  RUN_TEST(t_libtinyfiledialogs);
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

SUITE(s_incbin) {
  RUN_TEST(t_incbin);
}
SUITE(s_bitfield) {
  RUN_TEST(t_bitfield);
}
SUITE(s_bench) {
  RUN_TEST(t_bench);
}
SUITE(s_minmax) {
  RUN_TEST(t_minmax);
}
SUITE(s_msgbox_client) {
  RUN_TEST(t_msgbox_udp_client);
  RUN_TEST(t_msgbox_tcp_client);
}
SUITE(s_msgbox_server) {
  RUN_TEST(t_msgbox_udp_server);
  RUN_TEST(t_msgbox_tcp_server);
}
SUITE(s_msgbox) {
  RUN_TEST(t_msgbox);
}
SUITE(s_termbox2) {
  RUN_TEST(t_termbox2);
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
SUITE(s_httpserver){
  RUN_TEST(t_httpserver);
  PASS();
}
SUITE(s_kitty){
  RUN_TEST(t_kitty);
  RUN_TEST(t_kitty_image);
  RUN_TEST(t_kitty_set_font_size);
  RUN_TEST(t_kitty_ls);
  RUN_TEST(t_kitty_set_layout_stack);
  RUN_TEST(t_kitty_set_layout_vertical);
  RUN_TEST(t_kitty_reset_tab_color);
  RUN_TEST(t_kitty_set_tab_color);
  RUN_TEST(t_kitty_set_tab_title);
  RUN_TEST(t_kitty_set_window_title);
  RUN_TEST(t_kitty_get_text);
  RUN_TEST(t_kitty_get_colors);
  RUN_TEST(t_kitty_ls_kittens);
  RUN_TEST(t_kitty_query_terminal);
  RUN_TEST(t_kitty_list_fonts);
  RUN_TEST(t_kitty_send_text);
  PASS();
}
SUITE(s_my_cwd){
  RUN_TEST(t_my_cwd);
  PASS();
}
SUITE(s_jinja2_cli){
  RUN_TEST(t_jinja2_cli);
  PASS();
}
SUITE(s_levenshtein){
  RUN_TEST(t_levenshtein);
  PASS();
}
SUITE(s_querystring){
  RUN_TEST(t_querystring);
  PASS();
}
SUITE(s_libtrycatch){
  RUN_TEST(t_libtrycatch);
  PASS();
}
SUITE(s_emojis){
  RUN_TEST(t_emojis);
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

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  char EXECUTABLE_PATH[PATH_MAX + 1] = { 0 };

  realpath(argv[0], EXECUTABLE_PATH);
  EXECUTABLE_PATH_DIRNAME = dirname(EXECUTABLE_PATH);
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
    if (getenv("HTTPSERVER") != NULL) {
      RUN_SUITE(s_httpserver);
    }
    RUN_SUITE(s_libforks);
    RUN_SUITE(s_termbox2);
    RUN_SUITE(s_libtinyfiledialogs);
    RUN_SUITE(s_msgbox);
    RUN_SUITE(s_msgbox_server);
    RUN_SUITE(s_msgbox_client);
    RUN_SUITE(s_flingfd_client);
    RUN_SUITE(s_flingfd_server);
  }
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
  RUN_SUITE(s_tempdir);
  RUN_SUITE(s_hidapi);
  RUN_SUITE(s_libusb);
  RUN_SUITE(s_miniaudio);
  RUN_SUITE(s_c89atomic);
  RUN_SUITE(s_ok_file_formats);
  RUN_SUITE(s_minmax);
  RUN_SUITE(s_bench);
  RUN_SUITE(s_bitfield);
  RUN_SUITE(s_incbin);
  RUN_SUITE(s_emojis);
  RUN_SUITE(s_libtrycatch);
  RUN_SUITE(s_querystring);
  RUN_SUITE(s_levenshtein);
  RUN_SUITE(s_jinja2_cli);
  RUN_SUITE(s_my_cwd);
  RUN_SUITE(s_kitty);
  RUN_SUITE(s_url_h);
  RUN_SUITE(s_is_number);
  RUN_SUITE(s_wildcardcmp);
  RUN_SUITE(s_container_of);
  RUN_SUITE(s_path_normalize);
  RUN_SUITE(s_extname_c);
  RUN_SUITE(s_genpassword_c);
  RUN_SUITE(s_c_timestamp);
  RUN_SUITE(s_url_router);
  RUN_SUITE(s_hashmap_h);
  RUN_SUITE(s_str_flatten);
  RUN_SUITE(s_pidfile);
  RUN_SUITE(s_path_module);
  RUN_SUITE(s_semver);
  RUN_SUITE(s_uptime);
  RUN_SUITE(s_chfreq);
  RUN_SUITE(s_dotenv);
  RUN_SUITE(s_subhook);
  RUN_SUITE(s_libconfuse);
  RUN_SUITE(s_tty_copy);
  RUN_SUITE(s_tai64n);
  RUN_SUITE(s_sense_c);
  RUN_SUITE(s_list);
  RUN_SUITE(s_color_boxes);
  RUN_SUITE(s_seethe);
  RUN_SUITE(s_posix_tree);
  GREATEST_MAIN_END();

  size_t used = do_dmt_summary();

  dbg(used, %lu);
  assert(used == 0);
} /* main */
