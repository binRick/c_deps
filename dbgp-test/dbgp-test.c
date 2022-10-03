#define DEBUG_WORKERS      false
#define WINDOW_TITLE       "Application Title"
#define WINDOW_X_OFFSET    670
#define WINDOW_Y_OFFSET    100
#define WIN_WIDTH          800
#define WIN_HEIGHT         300
#define GLYPHS_PER_LINE    (256 / 8)
#define SDL_WINDOW_OPTIONS                        \
  SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI \
  | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP
#include "ansi-codes/ansi-codes.h"
//#include "dbgp-test.h"
#include "SDL_DBGP.h"
#include "SDL_DBGP_unscii16.h"
#include "SDL_DBGP_unscii8.h"
#include <assert.h>
#include <ctype.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <SDL.h>
//#include <SDL2/SDL.h>
#include "submodules/c_darwin/active-app/active-app.h"
#include "submodules/c_darwin/window-utils/window-utils.h"
#include <time.h>
#include <unistd.h>
#define L    log_debug
#define I    log_info
#define E    log_error
/////////////////////////////////////////////////////////////
SDL_Renderer *renderer;
int             should_quit = 0;
char            msg[1024 * 4];
volatile size_t keypresses = 0;
SDL_Event       event;
DBGP_Font       unscii8;
DBGP_Font       unscii16;
char            *iso_string;
SDL_Window      *window;
/////////////////////////////////////////////////////////////
pthread_t       worker_threads[10];
worker_t        *workers;
volatile int    processed_jobs_qty = 0, processed_qtys[1024];
chan_t          *JOBS_CHANNEL, *DONE_CHANNEL;
char            msg0[1024 * 2];
/////////////////////////////////////////////////////////////
#define BUFFER_QTY         50000
#define JOBS_QTY           45500
#define WORKER_SLEEP_MS    100

/////////////////////////////////////////////////////////////
void *worker(void *WID){
  void      *job;
  size_t    WORKER_ID = (size_t)WID;
  int       width = 1, height = -1, rw = -1, rh = -1;
  char      c[1024] = "t1";

  focused_t *fp     = get_focused_process();
  int       win_qty = get_windows_qty();

  L("%lu> Worker waing for jobs....", WORKER_ID);
  while (chan_recv(JOBS_CHANNEL, &job) == 0) {
    usleep(WORKER_SLEEP_MS * 1000 * WORKER_ID);
    processed_qtys[WORKER_ID]++;
    if ((processed_qtys[WORKER_ID] % 50) == 1) {
    }
    if ((processed_qtys[WORKER_ID] % 10) == 1) {
      //   fp = get_focused_process();
      win_qty = get_windows_qty();
//      SDL_SetCaption(c,NULL);
    }
    SDL_GetWindowSize(window, &width, &height);
    SDL_GetRendererOutputSize(renderer, &rw, &rh);
    sprintf(msg,
            "OK- %lu: %d> [window:%dx%d][renderer:%dx%d][font:%dx%d][cols:%d][rows:%d]"
            "\n"
            "[windows:%d][focus:%s|%d][mod:%d]",
            WORKER_ID,
            processed_qtys[WORKER_ID],
            width, height,
            rw, rh,
            unscii16.glyph_width, unscii16.glyph_height,
            (rw / DBGP_UNSCII16_WIDTH),
            (rh / DBGP_UNSCII16_HEIGHT),
            win_qty,
            fp->name, fp->pid,
            (processed_qtys[WORKER_ID] % 10 == 0)
            );
    sprintf(workers[WORKER_ID].msg,
            "\t"
            AC_RESETALL AC_YELLOW "<%d>" AC_RESETALL
            "\t"
            AC_RESETALL AC_YELLOW_BLACK "#" AC_RESETALL
            AC_RESETALL AC_BRIGHT_YELLOW_BLACK AC_BOLD "%lu" AC_RESETALL
            AC_RESETALL AC_YELLOW_BLACK "" AC_RESETALL
            " #%lu OK."
            " : "
            AC_RESETALL AC_UNDERLINE AC_MAGENTA_BLACK "processed %d jobs" AC_RESETALL
            AC_RESETALL AC_ITALIC AC_BLUE "(%d jobs in queue)" AC_RESETALL,
            getpid(),
            WORKER_ID,
            (size_t)job,
            processed_qtys[WORKER_ID],
            chan_size(JOBS_CHANNEL)
            );
    if (DEBUG_WORKERS) {
      I("%s", workers[WORKER_ID].msg);
    }
  }

  L(AC_RESETALL AC_GREEN_BLACK AC_ITALIC "%lu> received all jobs> " AC_RESETALL, WORKER_ID);
  chan_send(DONE_CHANNEL, (void *)WORKER_ID);
  return(NULL);
} /* worker */

void test_send_channel(void){
  char *sent_dur;

  ct_start(NULL);

  for (size_t i = 1; i <= JOBS_QTY; i++) {
    chan_send(JOBS_CHANNEL, (void *)i);
    if (DEBUG_WORKERS) {
      I(
        "          "
        AC_RESETALL AC_YELLOW AC_ITALIC "sent job "
        AC_RESETALL AC_BLUE "%3lu" AC_RESETALL,
        i
        );
    }
  }

  sent_dur = ct_stop("");

  chan_close(JOBS_CHANNEL);

  L("sent all jobs in %s. waiting for done signals......",
    sent_dur
    );
  free(sent_dur);
}

void test_setup_channels(void){
  JOBS_CHANNEL = chan_init(BUFFER_QTY);
  DONE_CHANNEL = chan_init(0);
  workers      = malloc(sizeof(worker_t) * 1);

  test_send_channel();
  processed_qtys[1] = 0;
  int res = pthread_create(&worker_threads[1], NULL, worker, (void *)1);
  ASSERT_EQ(0, res);
}

TEST test_dbgp(void){
  dbgp_main();
  PASS();
}

SUITE(dbgp) {
  test_dbgp();
  PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  //RUN_SUITE(dbgp);
  GREATEST_MAIN_END();
  return(0);
}

void screenshot(SDL_Renderer *renderer, const char *filename) {
  int width  = 0;
  int height = 0;

  SDL_GetRendererOutputSize(renderer, &width, &height);

  SDL_Surface *screenshot = SDL_CreateRGBSurface(
    0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

  SDL_RenderReadPixels(
    renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels,
    screenshot->pitch);
  SDL_SaveBMP(screenshot, filename);
  SDL_FreeSurface(screenshot);
}

void render_screen(void){
  SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xff);
  SDL_RenderClear(renderer);

  if (strlen(msg0) > 0) {
    DBGP_Print(&unscii16, renderer, 0, 15 * 16, DBGP_DEFAULT_COLORS, msg0);
  }
  if (strlen(msg) > 0) {
    DBGP_Print(&unscii16, renderer, 0, 13 * 16, DBGP_DEFAULT_COLORS, msg);
  }

  DBGP_Print(
    &unscii16, renderer, 40 * 8, 0 * 16, 0x0f,
    "$00    $10    $20    $30    $40    $50    $60    $70");
  DBGP_Print(
    &unscii16, renderer, 40 * 8, 1 * 16, 0x0f,
    "$80    $90    $A0    $B0    $C0    $D0    $E0    $F0");

  DBGP_Print(&unscii16, renderer, 0, 0, 0x5f, "@ SDL_DBGP! @");
  DBGP_Print(
    &unscii16, renderer, 0, 1 * 16, 0x0f,
    "Color can be changed with\n"
    "$09e$0As$0Bc$0Ca$0Dp$0Ee$0F"
    " codes too.");
  DBGP_Print(
    &unscii16, renderer, 0 * 8, 3 * 16, 0x1f, "abcdefghijkl0123456789");
  DBGP_Print(
    &unscii16, renderer, 0 * 8, 4 * 16, 0x3f, "Something $F3somethinG");

  DBGP_Printf(
    &unscii16, renderer, 0, 5 * 16, DBGP_DEFAULT_COLORS,
    "A string with accents: $74%s", iso_string);

  DBGP_Printf(
    &unscii8, renderer, 0, 7 * 16, DBGP_DEFAULT_COLORS,
    "Default fonts include the entire ISO-8859-1 charset:");
  for (int i = 0; i < 256; i++) {
    int x = (8 * 1) + (i % 32) * DBGP_UNSCII8_WIDTH;
    int y = (8 * 16) + (i / 32) * DBGP_UNSCII8_HEIGHT;
    DBGP_Printf(&unscii8, renderer, x, y, DBGP_DEFAULT_COLORS, "%c", i);
  }

  SDL_RenderPresent(renderer);
} /* render_screen */

int dbgp_main(void) {
  pthread_t th;

  pthread_create(&th, NULL, test_setup_channels, NULL);
  iso_string = SDL_iconv_string("ISO-8859-1", "UTF-8", "Ébène", sizeof("Ébène"));
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialise SDL2: %s", SDL_GetError());
    return(1);
  }
  SDL_SetHint(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, "1");
//  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  window = SDL_CreateWindow(
    WINDOW_TITLE,
    WINDOW_X_OFFSET, WINDOW_Y_OFFSET,
    WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPTIONS
    );

  if (window == NULL) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return(1);
  }
  renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    SDL_Log("unable to create renderer: %s", SDL_GetError());
    return(1);
  }
  SDL_RenderSetLogicalSize(renderer, WIN_WIDTH, WIN_HEIGHT);

  if (DBGP_OpenFont(
        &unscii16, renderer, DBGP_UNSCII16, sizeof(DBGP_UNSCII16),
        DBGP_UNSCII16_WIDTH, DBGP_UNSCII16_HEIGHT) != 0) {
    SDL_Log("Unable to initialise DBGP_UNSCII16: %s", SDL_GetError());
    return(1);
  }

  if (DBGP_OpenFont(
        &unscii8, renderer, DBGP_UNSCII8, sizeof(DBGP_UNSCII8),
        DBGP_UNSCII8_WIDTH, DBGP_UNSCII8_HEIGHT) != 0) {
    SDL_Log("Unable to initialise DBGP_UNSCII8: %s", SDL_GetError());
    return(1);
  }

  fprintf(stderr,
          "\n**OPTIONS**\n\n"
          "Screenshot: s\n"
          "\n"
          );
  while (!should_quit) {
    while (SDL_PollEvent(&event)) {
      keypresses++;
      sprintf(msg0,
              "keypress %s%s$0F%s%lu$0F: |%stype$0F:%d$0F|"
              "     "
              " %sWHITE$0F "
              " %sBLUE$0F "
              " %sGREEN$0F "
              " %sRED$0F "
              " %sCYAN$0F "
              " %sYELLOW$0F "
              " %sTEST$0F ",
              "$20", "#",
              "$E0", keypresses,
              "$04", event.type,
              "$F0",
              "$10",
              "$20",
              "$40",
              "$A0",
              "$E0",
              "$3F"
              );
      fprintf(stderr, "%s\n", msg0);

      switch (event.type) {
      case SDL_QUIT: should_quit = 1; break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_s) {
          screenshot(renderer, "screenshot.bmp");
        }
        break;
      }
    }
    render_screen();
  }

  SDL_free(iso_string);
  DBGP_CloseFont(&unscii8);
  DBGP_CloseFont(&unscii16);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return(0);
} /* dbgp_main */
