////////////////////////////////////////////
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define EXTENDED_ASCII
#include "font.h"

#define SCREEN_WIDTH     5 * 30
#define SCREEN_HEIGHT    7 * 3 + 2

////////////////////////////////////////////
#include "font-test/font-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "font/font.h"
#include "timestamp/timestamp.h"

char buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void drawPixel(int x, int y) {
  buffer[y][x] = 1;
}

int printChar(int x, int y, char c) {
  // Loop to "null terminator character"
  int match = 0;

  for (int l = 0; font[l].letter != 0; l++)
    if (font[l].letter == c) {
      match = l;
      break;
    }

  // Loop through 7 high 5 wide monochrome font
  int maxLength = 0;

  for (int py = 0; py < 7; py++)
    for (int px = 0; px < 5; px++)
      if (font[match].code[py][px] == '#') {
        drawPixel(x + px, y + py);

        // Dynamix width character spacing
        if (px > maxLength)
          maxLength = px;
      }

  return(maxLength);
}

int printString(int x, int y, char *string) {
  int cx = x;
  int cy = y;

  for (int c = 0; string[c] != '\0'; c++) {
    int length;
    if (string[c] == ' ')
      length = 5;
    else
      length = printChar(cx, cy, string[c]) + 3;

    cx += length;

    // Text wrap after space
    // Fine tune this to your liking.
    if (cx > SCREEN_WIDTH - 20 && string[c] == ' ') {
      cx  = x;
      cy += 8;
    }
  }

  return(cy);
}

////////////////////////////////////////////
TEST t_font_test(){
  printf("\n");
  memset(buffer, 0, sizeof(buffer));

//	printString(1, 1, FNT_AQST"Espa"FNT_AN"ol?");
//	printString(1, 9, FNT_AI"S"FNT_AEX"!");
  printString(1, 20, "RICHARD");

  setlocale(LC_CTYPE, "");

  // Use upper half, lower half, and full to simulate graphics
  for (int y = 0; y < SCREEN_HEIGHT - 1; y += 2) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      if (buffer[y][x] && buffer[y + 1][x])
        printf("%ls", L"\u2588");
      else if (buffer[y + 1][x])
        printf("%ls", L"\u2584");
      else if (buffer[y][x])
        printf("%ls", L"\u2580");
      else
        putchar(' ');
    }

    putchar('\r');
  }
  printf("\n");

  PASS();
}

SUITE(s_font_test) {
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_font_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_font_test);
  GREATEST_MAIN_END();
}
