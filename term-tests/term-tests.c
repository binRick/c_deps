#include "term-termpaint.c"
#include "term-tests-utils.c"
#include "term-tests.h"
///////////////////////////////////////////////
///        Menus                            ///
///////////////////////////////////////////////
#define BOTTOM_MSG_ROW_O
#define TERMINAL_KEY_MENU_ROW_OFFSET    26
#define TERMINAL_KEY_MENU_COL_OFFSET    3
#define TERMINAL_KEY_MENU_ITEM(ROW, LETTER, TEXT)    { do{                                                                                                                                        \
                                                         termpaint_surface_write_with_attr(surface, TERMINAL_KEY_MENU_COL_OFFSET, TERMINAL_KEY_MENU_ROW_OFFSET + ROW, LETTER "> " TEXT, attr_ui); \
                                                       }while (0); }

#define TERMINAL_KEY_MENU()                          { do{                                                                \
                                                         TERMINAL_KEY_MENU_ITEM(0, "B", "     Toggle Border Style");      \
                                                         TERMINAL_KEY_MENU_ITEM(1, "C", "     Clear Bottom Message");     \
                                                         TERMINAL_KEY_MENU_ITEM(2, "r", "     Refresh Screen");           \
                                                         TERMINAL_KEY_MENU_ITEM(3, "T", "     Inspect Terminal");         \
                                                         TERMINAL_KEY_MENU_ITEM(4, "t", "     Toggle Title");             \
                                                         TERMINAL_KEY_MENU_ITEM(5, "v", "     Toggle Cursor Visibility"); \
                                                         TERMINAL_KEY_MENU_ITEM(6, "c", "     Toggle Cursor Style");      \
                                                         TERMINAL_KEY_MENU_ITEM(7, "❰ ❱", "   Change Select");            \
                                                         TERMINAL_KEY_MENU_ITEM(8, "Esc", "   Undo Choice ❌");            \
                                                         TERMINAL_KEY_MENU_ITEM(9, "Enter", " Follow Menu Path");         \
                                                       }while (0); }
///////////////////////////////////////////////
///        GLOBAL CONSTANTS                 ///
///////////////////////////////////////////////
static const wchar_t
*orig = L";aABcCeEgHiIjKMNoOpPsSTxXyYZëËïÏöÖ",
*repl = L";аАВϲСеЕɡНіΙϳКМΝоОрРѕЅТхХуΥΖёЁїЇӧӦ"
;
static const char
  *TITLE_CHARS[] = { "🯰", "🯱", "🯲", "🯳", "🯴", "🯵", "🯶", "🯷", "🯸", "🯹" }
;
const int
  screen_bg       = TERMPAINT_COLOR_BRIGHT_YELLOW,
  ui_fg           = TERMPAINT_COLOR_BLACK,
  win_message     = TERMPAINT_COLOR_GREEN,
  tile_border     = TERMPAINT_COLOR_BLACK,
  tile_background = TERMPAINT_COLOR_LIGHT_GREY
;
///////////////////////////////////////////////
///        GLOBAL PROTOTYPES                ///
///////////////////////////////////////////////
static void
event_callback(void *userdata, termpaint_event *tp_event),
redraw_bottom_msg(),
rgb_color_menu(termpaint_attr * attr_ui, termpaint_attr * attr_to_change, int which_color),
update_current_key_display(termpaint_attr * attr_ui, event * evt),
indexed_color_menu(termpaint_attr * attr_ui, termpaint_attr * attr_to_change, int which_color),
write_sample(termpaint_attr * attr_ui, termpaint_attr * attr_sample, int line, char const *name, int style),
write_bottom_msg(const char *BOTTOM_MSG),
repaint_samples(termpaint_attr *, termpaint_attr *),
cycle_cursor_style(),
cycle_cursor_visiblity(),
cycle_cursor_blink(),
update_cursor_profile(),
clear_bottom_msg(bool SKIP_FLUSH, bool FORCE_FLUSH),
repaint_all(termpaint_attr * attr_ui, termpaint_attr * attr_sample),
cleanup(void),
update_current_key_display(termpaint_attr * attr_ui, event * evt),
named_color_menu(termpaint_attr * attr_ui, termpaint_attr * attr_to_change, int which_color),
menu(termpaint_attr * attr_ui, termpaint_attr * attr_sample),
draw_box()
;

static event *
key_wait(void)
;

static char
*tp__basename(const char *path)
;

static int
term_init(void),
min(int a, int b)
;

int
term_tests_main(const int argc, const char **argv)
;

char
*cell_at(board_t *, int, int)
;

volatile unsigned int
  title_updates_qty     = 0,
  BORDER_STYLE          = 0,
  BORDER_FG_COLOR_RED   = 255,
  BORDER_FG_COLOR_GREEN = 255,
  BORDER_FG_COLOR_BLUE  = 255,
  BORDER_BG_COLOR_RED   = 17,
  BORDER_BG_COLOR_GREEN = 0,
  BORDER_BG_COLOR_BLUE  = 255
;
///////////////////////////////////////////////
///        BOTTOM MSG COMPONENTS            ///
///////////////////////////////////////////////
#define MAX_RGB                          255
#define BORDER_STYLES_QTY                2
#define BOTTOM_MSG_BOX_HEIGHT            3
#define BOTTOM_MSG_BOX_COL_MSG_OFFSET    2
#define BOTTOM_MSG_BOX_COL               10
#define BOTTOM_MSG_BOX_TOP               BOTTOM_MSG_BOX_TOPS[BORDER_STYLE]
#define BOTTOM_MSG_BOX_BOTTOM            BOTTOM_MSG_BOX_BOTTOMS[BORDER_STYLE]
#define BOTTOM_MSG_BOX_SIDE              BOTTOM_MSG_BOX_SIDES[BORDER_STYLE]
#define BOTTOM_MSG_FG_COLOR              TERMPAINT_RGB_COLOR(BORDER_FG_COLOR_RED, BORDER_FG_COLOR_GREEN, BORDER_FG_COLOR_BLUE)
#define BOTTOM_MSG_BG_COLOR              TERMPAINT_RGB_COLOR(BORDER_BG_COLOR_RED, BORDER_BG_COLOR_GREEN, BORDER_BG_COLOR_BLUE)
#define BOTTOM_MSG_COLORS                BOTTOM_MSG_FG_COLOR, BOTTOM_MSG_BG_COLOR
#define CYCLE_BORDER_STYLE()              { do { BORDER_STYLE = BORDER_STYLE >= (BORDER_STYLES_QTY - 1) ? 0 : BORDER_STYLE + 1; } while (0); }
#define INCREASE_BOTTOM_MSG_FG_RED()      { do { BORDER_FG_COLOR_RED = BORDER_FG_COLOR_RED >= MAX_RGB ? 0 : BORDER_FG_COLOR_RED + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_FG_GREEN()    { do { BORDER_FG_COLOR_GREEN = BORDER_FG_COLOR_GREEN >= MAX_RGB ? 0 : BORDER_FG_COLOR_GREEN + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_FG_BLUE()     { do { BORDER_FG_COLOR_BLUE = BORDER_FG_COLOR_BLUE >= MAX_RGB ? 0 : BORDER_FG_COLOR_BLUE + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_BG_RED()      { do { BORDER_BG_COLOR_RED = BORDER_BG_COLOR_RED >= MAX_RGB ? 0 : BORDER_BG_COLOR_RED + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_BG_GREEN()    { do { BORDER_BG_COLOR_GREEN = BORDER_BG_COLOR_GREEN >= MAX_RGB ? 0 : BORDER_BG_COLOR_GREEN + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_BG_BLUE()     { do { BORDER_BG_COLOR_BLUE = BORDER_BG_COLOR_BLUE >= MAX_RGB ? 0 : BORDER_BG_COLOR_BLUE + 1; redraw_bottom_msg(); } while (0); }
const char
*BORDER_STYLES[]               = { "single", "double" },
BOTTOM_MSG_BOX_TOP_SINGLE[]    = "┌───────────────────────────────────────────────────────────────────────────────────────────────────────┐",
BOTTOM_MSG_BOX_SIDE_SINGLE[]   = "│                                                                                                       │",
BOTTOM_MSG_BOX_BOTTOM_SINGLE[] = "└───────────────────────────────────────────────────────────────────────────────────────────────────────┘",
BOTTOM_MSG_BOX_TOP_DOUBLE[]    = "╔═══════════════════════════════════════════════════════════════════════════════════════════════════════╗",
BOTTOM_MSG_BOX_SIDE_DOUBLE[]   = "║                                                                                                       ║",
BOTTOM_MSG_BOX_BOTTOM_DOUBLE[] = "╚═══════════════════════════════════════════════════════════════════════════════════════════════════════╝",
*BOTTOM_MSG_BOX_TOPS[]         = { BOTTOM_MSG_BOX_TOP_SINGLE, BOTTOM_MSG_BOX_TOP_DOUBLE },
*BOTTOM_MSG_BOX_SIDES[]        = { BOTTOM_MSG_BOX_SIDE_SINGLE, BOTTOM_MSG_BOX_SIDE_DOUBLE },
*BOTTOM_MSG_BOX_BOTTOMS[]      = { BOTTOM_MSG_BOX_BOTTOM_SINGLE, BOTTOM_MSG_BOX_BOTTOM_DOUBLE }
;
///////////////////////////////////////////////
///        GLOBAL VARIABLES                 ///
///////////////////////////////////////////////
volatile signed long long
  mouse_wheel_val = 0
;
volatile int
  field[5][5],
  x, y,
  current_start_x,
  current_start_y;
volatile bool
  quit
;
volatile unsigned int
  cursor_x = 0, cursor_y = 1
;
volatile char
  MSG[1024],
  CACHED_BOTTOM_MSG[1024]
;
volatile size_t
  surface_updates_qty = 0
;
termpaint_terminal
*terminal
;
termpaint_surface
*surface
;
termpaint_integration
*integration
;
termpaint_attr
*attr_ui,
*attr_sample,
*attr_bottom_msg
;
event
*event_current
;
cursor_profile_t
*cursor_profile
;

///////////////////////////////////////////////
static void logging_func(termpaint_integration *integration, const char *data, int length){
  fprintf(stderr, AC_RESETALL AC_GREEN "[logging_func] len:%d|data:'%s'\n" AC_RESETALL "\n", length, data);
}

int term_tests_main(const int argc, const char **argv) {
  if (term_init() != EXIT_SUCCESS)
    return(1);

  repaint_all(attr_ui, attr_sample);
  menu(attr_ui, attr_sample);

  termpaint_attr_free(attr_bottom_msg);
  attr_bottom_msg = NULL;
  termpaint_attr_free(attr_sample);
  attr_sample = NULL;
  termpaint_attr_free(attr_ui);
  attr_ui = NULL;
  cleanup();
  return(0);
}

static void draw_box() {
  const int screen_width     = termpaint_surface_width(surface),
            screen_height    = termpaint_surface_height(surface),
            top_left_x       = (screen_width / 2) - 12,
            top_left_y       = (screen_height / 2) - 2;
  bool TITLE_RESTORE_CAPABLE = termpaint_terminal_capable(terminal, TERMPAINT_CAPABILITY_TITLE_RESTORE);

  termpaint_terminal_set_title(terminal, "🔥💣💥🔫💊", TERMPAINT_TITLE_MODE_PREFER_RESTORE);

  termpaint_surface_write_with_colors(surface, top_left_x, top_left_y,
                                      "┌───────────────────────┐",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2 - 1,
                                      "│        OK!            │",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2,
                                      "│                       │",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2 + 1,
                                      "│ Press x to do it      │",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2 + 2,
                                      "└───────────────────────┘",
                                      ui_fg, win_message);
  termpaint_terminal_flush(terminal, false);
  // repaint_all(attr_ui, attr_sample);
} /* popup_box */

static void update_cursor_profile(){
  termpaint_terminal_set_cursor_position(terminal, cursor_profile->x, cursor_profile->y);
  termpaint_terminal_set_cursor_visible(terminal, cursor_profile->visible);
  termpaint_terminal_set_cursor_style(terminal, cursor_profile->style, cursor_profile->blink);
}

static void cycle_cursor_blink(){
  if (cursor_profile->blink)
    cursor_profile->blink = false;
  else
    cursor_profile->blink = true;
  update_cursor_profile();
}

static void cycle_cursor_visiblity(){
  if (cursor_profile->visible)
    cursor_profile->visible = false;
  else
    cursor_profile->visible = true;
  update_cursor_profile();
}

static void cycle_cursor_style(){
  if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BAR)
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_BLOCK;
  else if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BLOCK)
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_UNDERLINE;
  else
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_BAR;

  update_cursor_profile();
}

static void event_callback(void *userdata, termpaint_event *tp_event) {
  (void)userdata;
  event *my_event = NULL;

  if (tp_event->type == TERMPAINT_EV_CHAR) {
    my_event           = malloc(sizeof(event));
    my_event->type     = tp_event->type;
    my_event->modifier = tp_event->c.modifier;
    my_event->string   = strndup(tp_event->c.string, tp_event->c.length);
    my_event->next     = NULL;
    fprintf(stderr, AC_RESETALL AC_YELLOW AC_REVERSED "[TERMPAINT_EV_CHAR]   |%d|%s|" AC_RESETALL "\n", my_event->modifier, my_event->string);
  } else if (tp_event->type == TERMPAINT_EV_MISC) {
    if (strcmp(tp_event->misc.atom, "FocusIn") == 0)
      fprintf(stderr, AC_RESETALL AC_GREEN "Focus In" AC_RESETALL "\n");
    else if (strcmp(tp_event->misc.atom, "FocusOut") == 0)
      fprintf(stderr, AC_RESETALL AC_RED "Focus Out" AC_RESETALL "\n");
    else
      fprintf(stderr, "TERMPAINT_EV_MISC:%s\n", tp_event->misc.atom);
  } else if (tp_event->type == TERMPAINT_EV_KEY) {
    fprintf(stderr, AC_RESETALL AC_YELLOW AC_REVERSED "tp_event->type:%d|%s" AC_RESETALL "\n", tp_event->type, (char *)tp_event->key.atom);
    my_event           = malloc(sizeof(event));
    my_event->type     = tp_event->type;
    my_event->modifier = tp_event->key.modifier;
    my_event->string   = strdup(tp_event->key.atom);
    my_event->next     = NULL;
    fprintf(stderr, "TERMPAINT_EV_KEY:  |%d|%s|\n", my_event->modifier, my_event->string);
    if (strcmp(my_event->string, "ArrowUp") == 0) {
//        termpaint_image_load(terminal,"/tmp/me");
    }
  } else if (tp_event->type == TERMPAINT_EV_MOUSE) {
    if ((tp_event->mouse.action == TERMPAINT_MOUSE_PRESS && tp_event->mouse.button == 0)
        || tp_event->mouse.action == TERMPAINT_MOUSE_MOVE) {
      cursor_x = tp_event->mouse.x;
      cursor_y = tp_event->mouse.y;
    }

    //SCROLL WHEEL
    switch (tp_event->mouse.button) {
    case 4: mouse_wheel_val++; break;
    case 5: mouse_wheel_val--; break;
    }
    sprintf(MSG, "Mouse Event>     "
            "but:%1d|"
            "act:%1d|"
            "loc:%d3x%d3|"
            "sfc:%3dx%d3|"
            "wheel:%lld|"
            "updates:%4lu|",
            tp_event->mouse.button,
            tp_event->mouse.action,
            cursor_x, cursor_y,
            termpaint_surface_width(surface), termpaint_surface_height(surface),
            mouse_wheel_val,
            surface_updates_qty
            );
    write_bottom_msg(MSG);
    //termpaint_image_save(surface,"/tmp/me");
  }

  if (my_event) {
    event *prev = event_current;
    while (prev->next)
      prev = prev->next;
    prev->next = my_event;
  }
} /* event_callback */

static int term_init(void) {
  attr_ui         = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);
  attr_sample     = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);
  attr_bottom_msg = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);

  cursor_profile        = malloc(sizeof(cursor_profile_t));
  event_current         = malloc(sizeof(event));
  event_current->next   = NULL;
  event_current->string = NULL;

  integration = termpaint_full_integration_setup_terminal_fullscreen("+kbdsigint +kbdsigtstp", event_callback, NULL, &terminal);
  surface     = termpaint_terminal_get_surface(terminal);

//  bool ok = termpaint_surface_resize_mustcheck(surface, 50, 10);
  termpaint_integration_set_logging_func(integration, logging_func);

  if (termpaint_terminal_self_reported_name_and_version(terminal)) {
    char *self_reported_name_and_version = termpaint_terminal_self_reported_name_and_version(terminal);
    fprintf(stderr, AC_RESETALL AC_GREEN "[self_reported_name_and_version] %s\n" AC_RESETALL "\n", self_reported_name_and_version);
  }

  //termpaint_terminal_set_log_mask(terminal, TERMPAINT_LOG_AUTO_DETECT_TRACE | TERMPAINT_LOG_TRACE_RAW_INPUT);

  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_CLICKS);
  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_DRAG);
  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_MOVEMENT);
  termpaint_terminal_request_focus_change_reports(terminal, true);

  cursor_profile->visible = true;
  update_cursor_profile();

  char *d = "B";
  termpaint_terminal_add_input_data(terminal, d, strlen(d));

  clear_bottom_msg(false, false);
  return(EXIT_SUCCESS);
}

static void cleanup(void) {
  termpaint_terminal_free_with_restore(terminal);
  while (event_current) {
    free((void *)event_current->string);
    event *next = event_current->next;
    free(event_current);
    event_current = next;
  }
}

static event *key_wait(void) {
  while (!event_current->next) {
    redraw_bottom_msg();
    /*
     * if (!termpaint_full_integration_do_iteration(integration)) {
     * cleanup();
     * exit(1);
     * }
     */
  }

  free((void *)event_current->string);
  event *next = event_current->next;

  free(event_current);
  event_current = next;
  return(next);
}

static void write_sample(termpaint_attr *attr_ui, termpaint_attr *attr_sample, int line, char const *name, int style) {
  termpaint_surface_write_with_attr(surface, 0, line, name, attr_ui);
  termpaint_attr_reset_style(attr_sample);
  termpaint_attr_set_style(attr_sample, style);
  termpaint_surface_write_with_attr(surface, 11, line, "Sample", attr_sample);
}

static void repaint_samples(termpaint_attr *attr_ui, termpaint_attr *attr_sample){
  write_sample(attr_ui, attr_sample, 3, "No Style:", 0);
  write_sample(attr_ui, attr_sample, 4, "Bold:", TERMPAINT_STYLE_BOLD);
  write_sample(attr_ui, attr_sample, 5, "Italic:", TERMPAINT_STYLE_ITALIC);
  write_sample(attr_ui, attr_sample, 6, "Blinking:", TERMPAINT_STYLE_BLINK);
  write_sample(attr_ui, attr_sample, 7, "Underline:", TERMPAINT_STYLE_UNDERLINE);
  write_sample(attr_ui, attr_sample, 8, "Strikeout:", TERMPAINT_STYLE_STRIKE);
  write_sample(attr_ui, attr_sample, 9, "Inverse:", TERMPAINT_STYLE_INVERSE);

  write_sample(attr_ui, attr_sample, 11, "Overline:", TERMPAINT_STYLE_OVERLINE);
  write_sample(attr_ui, attr_sample, 12, "Dbl under:", TERMPAINT_STYLE_UNDERLINE_DBL);
  write_sample(attr_ui, attr_sample, 13, "curly:", TERMPAINT_STYLE_UNDERLINE_CURLY);

  termpaint_attr *attr_url = termpaint_attr_clone(attr_sample);

  termpaint_attr_set_patch(attr_url, true, "\e]8;;http://example.com\a", "\e]8;;\a");
  write_sample(attr_ui, attr_url, 14, "url:", 0);
  termpaint_attr_free(attr_url);
  char *st = malloc(32);
  sprintf(st, "%d", cursor_profile->style);
  termpaint_surface_write_with_attr(surface, 0, 15, "Cursor:", attr_ui);
  termpaint_attr_reset_style(attr_sample);
  termpaint_surface_write_with_attr(surface, 11, 15, " ", attr_sample);
  cursor_profile->x = 11;
  cursor_profile->y = 15;
  free(st);
  update_cursor_profile();
}

static void repaint_all(termpaint_attr *attr_ui, termpaint_attr *attr_sample){
  termpaint_surface_clear_with_attr(surface, attr_ui);
  termpaint_surface_write_with_attr(surface, 1, 0, "Terminal UI", attr_ui);
  repaint_samples(attr_ui, attr_sample);

  termpaint_surface_write_with_attr(surface, 25, 2, "Select Color", attr_ui);

  termpaint_surface_write_with_attr(surface, 2, 20, "q: Quit", attr_ui);
} /* repaint_all */

static void update_current_key_display(termpaint_attr *attr_ui, event *evt) {
  if (evt->type == TERMPAINT_EV_CHAR || evt->type == TERMPAINT_EV_KEY) {
    char buff[100];
    snprintf(buff, 100, "%-20.20s mod: %d", evt->string, evt->modifier);
    termpaint_surface_write_with_attr(surface, 0, 23, "Last key: ", attr_ui);
    termpaint_surface_write_with_attr(surface, 11, 23, buff, attr_ui);
  }
}

static void named_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
  int color = 0;

  while (!quit) {
    surface_updates_qty++;
    {
      termpaint_attr *preview = termpaint_attr_new(0, TERMPAINT_INDEXED_COLOR + color);
      termpaint_surface_write_with_attr(surface, 50, 7, "  ", preview);
      termpaint_attr_free(preview);
    }
    termpaint_surface_write_with_attr(surface, 25, 7, "  Black", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 8, "  Red", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 9, "  Green", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 10, "  Yellow", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 11, "  Blue", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 12, "  Magenta", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 13, "  Cyan", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 14, "  Light Grey", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 15, "  Dark Grey", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 16, "  Bright Red", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 17, "  Bright Green", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 18, "  Bright Yellow", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 19, "  Bright Blue", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 20, "  Bright Magenta", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 21, "  Bright Cyan", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 22, "  White", attr_ui);

    termpaint_surface_write_with_attr(surface, 25, 7 + color, "*", attr_ui);

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);
    HANDLE_EVENTS();

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
      color = color - 1;
      if (color < 0)
        color = 15;
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0)
      color = (color + 1) % 16;

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
      int tp_color = TERMPAINT_NAMED_COLOR + color;
      if (which_color == 0)
        termpaint_attr_set_fg(attr_to_change, tp_color);
      else if (which_color == 1)
        termpaint_attr_set_bg(attr_to_change, tp_color);
      else
        termpaint_attr_set_deco(attr_to_change, tp_color);
      return;
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Escape") == 0)
      return;
  }
} /* named_color_menu */

static void indexed_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
  int color = 0;

  termpaint_surface_write_with_attr(surface, 25, 7, "  0", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 8, " 16", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 9, " 32", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 10, " 48", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 11, " 64", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 12, " 80", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 13, " 96", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 14, "112", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 15, "128", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 16, "144", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 17, "160", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 18, "176", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 19, "192", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 20, "208", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 21, "224", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 22, "240", attr_ui);

  termpaint_surface_write_with_attr(surface, 29, 6, "  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15", attr_ui);
  while (!quit) {
    surface_updates_qty++;
    {
      termpaint_attr *preview = termpaint_attr_new(0, TERMPAINT_INDEXED_COLOR + color);
      termpaint_surface_write_with_attr(surface, 28, 6, "  ", preview);
      termpaint_attr_free(preview);
    }
    termpaint_surface_clear_rect_with_attr(surface, 29, 7, 50, 16, attr_ui);
    char buff[11];
    sprintf(buff, "%3d", color);
    termpaint_surface_write_with_attr(surface, 29 + (color % 16) * 3, 7 + (color / 16), buff, attr_ui);

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);

    if (evt->type == TERMPAINT_EV_CHAR) {
      if (strcmp(evt->string, "q") == 0)
        quit = true;
    } else if (evt->type == TERMPAINT_EV_KEY) {
      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0) {
        color -= 1;
        if (color < 0)
          color = 255;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0)
        color = (color + 1) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
        color -= 16;
        if (color < 0)
          color += 256;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0)
        color = (color + 16) % 256;

      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
        int tp_color = TERMPAINT_INDEXED_COLOR + color;
        if (which_color == 0)
          termpaint_attr_set_fg(attr_to_change, tp_color);
        else if (which_color == 1)
          termpaint_attr_set_bg(attr_to_change, tp_color);
        else
          termpaint_attr_set_deco(attr_to_change, tp_color);
        return;
      }

      if (strcmp(evt->string, "Escape") == 0)
        return;
    }
  }
} /* indexed_color_menu */

static void rgb_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
  int red   = 0;
  int green = 0;
  int blue  = 0;

  int *selected = &red;

  termpaint_surface_write_with_attr(surface, 29, 11, "up/down: adjust value", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 12, "page up/page down: adjust value (16 increments)", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 13, "esc: abort", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 14, "enter: activate color", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 15, "+: activate cursor visiblity", attr_ui);

  while (!quit) {
    char buff[40];
    sprintf(buff, "R: %3d G: %3d B: %3d", red, green, blue);
    termpaint_surface_write_with_attr(surface, 29, 7, buff, attr_ui);
    termpaint_surface_write_with_attr(surface, 29, 8, "                    ", attr_ui);

    {
      termpaint_attr *preview = termpaint_attr_new(0, TERMPAINT_RGB_COLOR(red, green, blue));
      termpaint_surface_write_with_attr(surface, 52, 7, "  ", preview);
      termpaint_attr_free(preview);
    }

    if (selected == &red)
      termpaint_surface_write_with_attr(surface, 32, 8, "^^^", attr_ui);
    else if (selected == &green)
      termpaint_surface_write_with_attr(surface, 39, 8, "^^^", attr_ui);
    else if (selected == &blue)
      termpaint_surface_write_with_attr(surface, 46, 8, "^^^", attr_ui);

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);

    if (evt->type == TERMPAINT_EV_CHAR) {
      if (strcmp(evt->string, "q") == 0)
        quit = true;
      else if (strcmp(evt->string, "q") == 0) {
        if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BAR)
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_BLOCK;
        else if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BLOCK)
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_UNDERLINE;
        else
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_BAR;
        update_cursor_profile();
      }
    } else if (evt->type == TERMPAINT_EV_KEY) {
      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0) {
        if (selected == &green)
          selected = &red;
        else if (selected == &blue)
          selected = &green;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "b") == 0)
        cycle_cursor_blink();
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "v") == 0)
        cycle_cursor_visiblity();
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "c") == 0)
        cycle_cursor_style();
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0) {
        if (selected == &red)
          selected = &green;
        else if (selected == &green)
          selected = &blue;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0)
        *selected = (256 + *selected - 1) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0)
        *selected = (*selected + 1) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageUp") == 0)
        *selected = (256 + *selected - 16) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageDown") == 0)
        *selected = (*selected + 16) % 256;

      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
        int tp_color = TERMPAINT_RGB_COLOR(red, green, blue);
        if (which_color == 0)
          termpaint_attr_set_fg(attr_to_change, tp_color);
        else if (which_color == 1)
          termpaint_attr_set_bg(attr_to_change, tp_color);
        else
          termpaint_attr_set_deco(attr_to_change, tp_color);
        return;
      }

      if (strcmp(evt->string, "Escape") == 0)
        return;
    }
  }
} /* rgb_color_menu */

static void clear_bottom_msg(bool SKIP_FLUSH, bool FORCE_FLUSH){
  bool cursor_visible = cursor_profile->visible;

  if (cursor_visible)
    cursor_profile->visible = false;
  termpaint_surface_clear_rect_with_attr(surface,
                                         0,
                                         termpaint_surface_height(surface) - BOTTOM_MSG_BOX_HEIGHT + 1,
                                         termpaint_surface_width(surface),
                                         BOTTOM_MSG_BOX_HEIGHT,
                                         attr_bottom_msg
                                         );
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL,
                                      termpaint_surface_height(surface) - 3,
                                      BOTTOM_MSG_BOX_TOP,
                                      BOTTOM_MSG_COLORS
                                      );
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL,
                                      termpaint_surface_height(surface) - 2,
                                      BOTTOM_MSG_BOX_SIDE,
                                      BOTTOM_MSG_COLORS
                                      );
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL,
                                      termpaint_surface_height(surface) - 1,
                                      BOTTOM_MSG_BOX_BOTTOM,
                                      BOTTOM_MSG_COLORS
                                      );
  if (!SKIP_FLUSH)
    termpaint_terminal_flush(terminal, FORCE_FLUSH);
  cursor_profile->visible = cursor_visible;
}

void redraw_bottom_msg(){
  clear_bottom_msg(true, false);
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL + BOTTOM_MSG_BOX_COL_MSG_OFFSET,
                                      termpaint_surface_height(surface) - 2,
                                      CACHED_BOTTOM_MSG,
                                      BOTTOM_MSG_COLORS
                                      );
  termpaint_terminal_flush(terminal, false);
}

static void write_bottom_msg(const char *BOTTOM_MSG){
  sprintf(CACHED_BOTTOM_MSG, "%s", BOTTOM_MSG);
  redraw_bottom_msg();
}

static void menu(termpaint_attr *attr_ui, termpaint_attr *attr_sample) {
  bool sample = true;
  bool reset  = true;

  while (!quit) {
    if (reset) {
      repaint_all(attr_ui, attr_sample);
      TERMINAL_KEY_MENU();

      reset = false;
    }

    if (sample) {
      termpaint_surface_write_with_attr(surface, 25, 3, "* Sample", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 3, "  UI", attr_ui);
    } else {
      termpaint_surface_write_with_attr(surface, 25, 3, "  Sample", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 3, "* UI", attr_ui);
    }

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);

    if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0)
      quit = true;
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "b") == 0)
      cycle_cursor_blink();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "v") == 0)
      cycle_cursor_visiblity();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "t") == 0) {
      title_updates_qty++;

      char *NEW_TITLE   = malloc(1024);
      char *title_chars = TITLE_CHARS[title_updates_qty < 10 ? title_updates_qty : title_updates_qty % 10];
      fwprintf(stderr,
               L""
               AC_RESETALL AC_RED AC_ITALIC "title chars size" AC_RESETALL ": "
               AC_RESETALL AC_REVERSED AC_BLUE AC_BOLD "%lu" AC_RESETALL
               "\n",
               wcslen(title_chars)
               );

      sprintf(NEW_TITLE,
              "|\t%d\t|"
              "\t%s\t|",
              title_updates_qty,
              title_chars
              );
      sprintf(MSG, "%s",
              NEW_TITLE
              );
      write_bottom_msg(MSG);
      termpaint_terminal_set_title(terminal, NEW_TITLE, TERMPAINT_TITLE_MODE_PREFER_RESTORE);
      free(NEW_TITLE);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "5") == 0)
      INCREASE_BOTTOM_MSG_BG_RED();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "6") == 0)
      INCREASE_BOTTOM_MSG_BG_GREEN();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "7") == 0)
      INCREASE_BOTTOM_MSG_BG_BLUE();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "8") == 0)
      INCREASE_BOTTOM_MSG_FG_RED();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "9") == 0)
      INCREASE_BOTTOM_MSG_FG_GREEN();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "0") == 0)
      INCREASE_BOTTOM_MSG_FG_BLUE();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "C") == 0) {
      sprintf(MSG, "");
      write_bottom_msg(MSG);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "r") == 0) {
      sprintf(MSG, "%llu", timestamp());
      write_bottom_msg(MSG);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "B") == 0) {
      CYCLE_BORDER_STYLE();
      sprintf(MSG, "Border Style: #%d | %s", BORDER_STYLE, BORDER_STYLES[BORDER_STYLE]);
      write_bottom_msg(MSG);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "T") == 0)
      draw_box();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "c") == 0)
      cycle_cursor_style();
    else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && !sample)
      sample = true;
    else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && sample)
      sample = false;
    else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
      int which_color = 0;
      termpaint_surface_write_with_attr(surface, 25, 4, "* Foreground", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
      termpaint_surface_write_with_attr(surface, 54, 4, "  Deco", attr_ui);

      while (!quit && !reset) {
        event *evt = key_wait();
        update_current_key_display(attr_ui, evt);

        if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0)
          quit = true;

        if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && which_color == 1) {
          termpaint_surface_write_with_attr(surface, 25, 4, "* Foreground", attr_ui);
          termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
          which_color = 0;
        } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && which_color == 2) {
          termpaint_surface_write_with_attr(surface, 40, 4, "* Background", attr_ui);
          termpaint_surface_write_with_attr(surface, 54, 4, "  Deco", attr_ui);
          which_color = 1;
        }

        if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && which_color == 0) {
          termpaint_surface_write_with_attr(surface, 25, 4, "  Foreground", attr_ui);
          termpaint_surface_write_with_attr(surface, 40, 4, "* Background", attr_ui);
          which_color = 1;
        } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && which_color == 1) {
          termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
          termpaint_surface_write_with_attr(surface, 54, 4, "* Deco", attr_ui);
          which_color = 2;
        }

        if (evt->type == TERMPAINT_EV_KEY && (strcmp(evt->string, "ArrowUp") == 0 || strcmp(evt->string, "Escape") == 0)) {
          termpaint_surface_clear_rect_with_attr(surface, 25, 4, 35, 1, attr_ui);
          break;
        }

        if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
          int type = 0;

          termpaint_surface_write_with_attr(surface, 25, 5, "* Named", attr_ui);
          termpaint_surface_write_with_attr(surface, 40, 5, "  Indexed", attr_ui);
          termpaint_surface_write_with_attr(surface, 53, 5, "  RGB", attr_ui);
          while (!quit && !reset) {
            event *evt = key_wait();
            update_current_key_display(attr_ui, evt);

            if (evt->type == TERMPAINT_EV_CHAR) {
              if (strcmp(evt->string, "q") == 0)
                quit = true;
            } else {
              if (strcmp(evt->string, "ArrowLeft") == 0 && type == 1) {
                type = 0;
                termpaint_surface_write_with_attr(surface, 25, 5, "* Named", attr_ui);
                termpaint_surface_write_with_attr(surface, 40, 5, "  Indexed", attr_ui);
              } else if (strcmp(evt->string, "ArrowLeft") == 0 && type == 2) {
                type = 1;
                termpaint_surface_write_with_attr(surface, 40, 5, "* Indexed", attr_ui);
                termpaint_surface_write_with_attr(surface, 53, 5, "  RGB", attr_ui);
              } else if (strcmp(evt->string, "ArrowRight") == 0 && type == 0) {
                type = 1;
                termpaint_surface_write_with_attr(surface, 25, 5, "  Named", attr_ui);
                termpaint_surface_write_with_attr(surface, 40, 5, "* Indexed", attr_ui);
              } else if (strcmp(evt->string, "ArrowRight") == 0 && type == 1) {
                type = 2;
                termpaint_surface_write_with_attr(surface, 40, 5, "  Indexed", attr_ui);
                termpaint_surface_write_with_attr(surface, 53, 5, "* RGB", attr_ui);
              } else if (strcmp(evt->string, "ArrowUp") == 0 || strcmp(evt->string, "Escape") == 0) {
                termpaint_surface_clear_rect_with_attr(surface, 25, 5, 35, 1, attr_ui);
                break;
              } else if (strcmp(evt->string, "Enter") == 0) {
                termpaint_surface_clear_rect_with_attr(surface, 29, 14, 25, 3, attr_ui);

                termpaint_attr *to_change = sample ? attr_sample : attr_ui;
                if (type == 0)
                  named_color_menu(attr_ui, to_change, which_color);
                else if (type == 1)
                  indexed_color_menu(attr_ui, to_change, which_color);
                else
                  rgb_color_menu(attr_ui, to_change, which_color);
                reset = true;
              }
            }
          }
        }
      }
    }
  }
} /* menu */
