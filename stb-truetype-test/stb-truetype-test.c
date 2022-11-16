#include <math.h>
#define INCBIN_STYLE     INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX    inc_
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "ms/ms.h"
#include "stb-truetype-test/stb-truetype-test.h"
#include "stb/stb_truetype.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
INCBIN(glass_tty_vt220, "assets/glass_tty_vt220.ttf");

unsigned char screen[20][79];
char          buffer[24 << 20];

TEST t_stb_truetype_test1(){
  char *file;

  asprintf(&file, "%s%s-%lld.ttf", gettempdir(), "glass_tty_vt220", timestamp());
  bool ok = false;

  ok = fsio_write_binary_file(file, inc_glass_tty_vt220_data, inc_glass_tty_vt220_size);
  ASSERT_EQ(ok, true);

  stbtt_fontinfo font;
  int            i, j, ascent, baseline, ch = 0;
  float          scale, xpos = 2;
  char           *text = "HELLO";

  fread(buffer, 1, 1000000, fopen(file, "rb"));
  stbtt_InitFont(&font, buffer, 0);
  int qty = stbtt_GetNumberOfFonts(buffer);

  log_info("qty:%d", qty);

  scale = stbtt_ScaleForPixelHeight(&font, 15);
  stbtt_GetFontVMetrics(&font, &ascent, 0, 0);
  baseline = (int)(ascent * scale);

  while (text[ch]) {
    int   advance, lsb, x0, y0, x1, y1;
    float x_shift = xpos - (float)floor(xpos);
    stbtt_GetCodepointHMetrics(&font, text[ch], &advance, &lsb);
    stbtt_GetCodepointBitmapBoxSubpixel(&font, text[ch], scale, scale, x_shift, 0, &x0, &y0, &x1, &y1);
    stbtt_MakeCodepointBitmapSubpixel(&font, &screen[baseline + y0][(int)xpos + x0], x1 - x0, y1 - y0, 79, scale, scale, x_shift, 0, text[ch]);
    xpos += (advance * scale);
    if (text[ch + 1])
      xpos += scale * stbtt_GetCodepointKernAdvance(&font, text[ch], text[ch + 1]);
    ++ch;
  }

  for (j = 0; j < 20; ++j) {
    for (i = 0; i < 78; ++i)
      putchar(" .:ioVM@"[screen[j][i] >> 5]);
    putchar('\n');
  }
  fsio_remove(file);
  PASS();
} /* t_stb_truetype_test1 */

SUITE(s_stb_truetype_test) {
  RUN_TEST(t_stb_truetype_test1);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_stb_truetype_test);
  GREATEST_MAIN_END();
}
