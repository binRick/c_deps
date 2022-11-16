
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
#include "qoi-ci-test/qoi-ci-test.h"
#include "qoi_ci/QOI-stdio.h"
#include "qoi_ci/transpiled/QOI.h"
#include "timestamp/timestamp.h"
#include <png.h>
INCBIN(communist_goals, "assets/communist-goals.png");
INCBIN(fedora_logo, "assets/fedora_logo.png");
INCBIN(kitty_icon, "assets/kitty_icon.png");
INCBIN(preview, "assets/preview.png");
INCBIN(screenshot, "assets/screenshot.png");
#define QTY(X)    (sizeof(X) / sizeof(X[0]))
static char          *files[] = {
  "/tmp/communist-goals.png",
  "/tmp/fedora_logo.png",
  "/tmp/kitty_icon.png",
  "/tmp/preview.png",
  "/tmp/screenshot.png",
};
static size_t        files_qty = QTY(files);
static unsigned long id;

TEST t_qoi_ci_test_qoi_to_png(){
  for (size_t i = 0; i < files_qty; i++) {
    unsigned long started = timestamp();
    char          *fn = files[i];
    char          *input_file, *output_file;
    asprintf(&output_file, "%s-%ld.png", stringfn_substring(fn, 0, strlen(fn) - 4), id);
    asprintf(&input_file, "%s-%ld.qoi", stringfn_substring(fn, 0, strlen(fn) - 4), id);
    FILE *f = fopen(input_file, "rb");
    if (f == NULL) {
      perror(input_file);
      FAIL();
      return(false);
    }
    QOIDecoder *qoi = QOIDecoder_LoadStdio(f);
    fclose(f);
    if (qoi == NULL)
      FAILm("Invalid QOI Decoder result");
    png_image png = { 0 };
    png.version = PNG_IMAGE_VERSION;
    png.width   = QOIDecoder_GetWidth(qoi);
    png.height  = QOIDecoder_GetHeight(qoi);
    png.format  = PNG_FORMAT_BGRA;
    unsigned long _s      = timestamp();
    unsigned char *pixels = QOIDecoder_GetPixels(qoi);
    log_info("Decoded %dx%d qoi %s %s (alpha:%s|linear colorspace:%s) in %s",
             png.width, png.height,
             bytes_to_string(fsio_file_size(input_file)), input_file,
             QOIDecoder_HasAlpha(qoi)?"Yes":"No",
             QOIDecoder_IsLinearColorspace(qoi)?"Yes":"No",
             milliseconds_to_string(timestamp() - _s)
             );
    if (png_image_write_to_file(&png, output_file, 0, pixels, 0, NULL) == 0) {
      QOIDecoder_Delete(qoi);
      FAIL();
    }
    QOIDecoder_Delete(qoi);
    char *m;
    asprintf(&m, "Wrote %s %s from %dx%d %s %s in %s",
             bytes_to_string(fsio_file_size(output_file)), output_file,
             png.width, png.width, bytes_to_string(fsio_file_size(input_file)), input_file,
             milliseconds_to_string(timestamp() - started)
             );
    log_debug("%s", m);
  }

  PASS();
} /* t_qoi_ci_test_qoi_to_png */

TEST t_qoi_ci_test_png_to_qoi(){
  for (size_t i = 0; i < files_qty; i++) {
    char *input_file = files[i];
    char *output_file;
    asprintf(&output_file, "%s-%ld.qoi", stringfn_substring(input_file, 0, strlen(input_file) - 4), id);

    unsigned long started = timestamp();

    FILE          *f = fopen(input_file, "rb");
    if (f == NULL) {
      perror(input_file);
      FAIL();
      return(false);
    }
    uint8_t magic[8];
    if (fread(magic, 1, sizeof(magic), f) != sizeof(magic))
      FAIL();
    if (!png_check_sig(magic, sizeof(magic)))
      FAIL();

    if (fseek(f, 0, SEEK_SET) != 0) {
      perror(input_file);
      fclose(f);
      FAIL();
    }
    png_image png;
    png.opaque  = NULL;
    png.version = PNG_IMAGE_VERSION;
    if (png_image_begin_read_from_stdio(&png, f) == 0) {
      fclose(f);
      FAIL();
    }
    bool alpha = (png.format & PNG_FORMAT_FLAG_ALPHA) != 0;
    png.format = PNG_FORMAT_BGRA;
    void *pixels = malloc(PNG_IMAGE_SIZE(png));
    if (pixels == NULL)
      FAIL();
    if (png_image_finish_read(&png, NULL, pixels, 0, NULL) == 0) {
      free(pixels);
      fclose(f);
      FAIL();
    }
    fclose(f);

    QOIEncoder *qoi = QOIEncoder_New();
    if (!QOIEncoder_Encode(qoi, png.width, png.height, pixels, alpha, false)) {
      QOIEncoder_Delete(qoi);
      free(pixels);
      FAIL();
    }
    free(pixels);

    if (!QOIEncoder_SaveFile(qoi, output_file)) {
      perror(output_file);
      QOIEncoder_Delete(qoi);
      FAIL();
    }
    QOIEncoder_Delete(qoi);

    char *m;
    asprintf(&m, "Wrote %s %s from %dx%d %s %s (encoded size:%s) in %s",
             bytes_to_string(fsio_file_size(output_file)), output_file,
             png.width, png.width, bytes_to_string(fsio_file_size(input_file)), input_file,
             bytes_to_string(QOIEncoder_GetEncodedSize(qoi)),
             milliseconds_to_string(timestamp() - started)
             );

    log_debug("%s", m);
  }
  PASS();
} /* t_qoi_ci_test_png_to_qoi */

SUITE(s_qoi_ci_png_to_qoi) {
  RUN_TEST(t_qoi_ci_test_png_to_qoi);
}
SUITE(s_qoi_ci_qoi_to_png) {
  RUN_TEST(t_qoi_ci_test_qoi_to_png);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  id = timestamp();
  fsio_write_binary_file(files[0], gcommunist_goalsData, gcommunist_goalsSize);
  fsio_write_binary_file(files[1], gfedora_logoData, gfedora_logoSize);
  fsio_write_binary_file(files[1], gkitty_iconData, gkitty_iconSize);
  fsio_write_binary_file(files[3], gpreviewData, gpreviewSize);
  fsio_write_binary_file(files[4], gscreenshotData, gscreenshotSize);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_qoi_ci_png_to_qoi);
  RUN_SUITE(s_qoi_ci_qoi_to_png);
  GREATEST_MAIN_END();
}
