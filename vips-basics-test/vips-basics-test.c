
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "vips-basics-test/vips-basics-test.h"
#include "vips/vips.h"
#define DINCBIN_SILENCE_BITCODE_WARNING
#include "incbin/incbin.h"
INCBIN(communist_goals, "assets/communist-goals.png");
INCBIN(kitty_icon, "assets/kitty_icon.png");
#define PROGRESS    false
static char *files[] = {
  "/tmp/communist-goals.png",
  "/tmp/kitty_icon.png",
};
static char *exts[] = { "png", "gif", "jpg", "tif", };

static int annotate_image(VipsObject *context, VipsImage *image, VipsImage **out) {
  int       page_height = vips_image_get_page_height(image);
  int       n_pages     = image->Ysize / page_height;
  VipsImage **overlay   = (VipsImage **)
                          vips_object_local_array(context, n_pages);
  VipsImage **page = (VipsImage **)
                     vips_object_local_array(context, n_pages);
  VipsImage **annotated = (VipsImage **)
                          vips_object_local_array(context, n_pages);

  /* Red as RGBA.
   */
  double red[]         = { 255, 0, 0, 255 };
  double transparent[] = { 0, 0, 0, 0 };

  int    i;

  /* Split the image into frames.
   */
  for ( i = 0; i < n_pages; i++ ) {
    if (vips_crop(image, &page[i],
                  0, page_height * i, image->Xsize, page_height, NULL)) {
      return(-1);
    }
  }

  /* Make an overlay ... a solid red square, with a transparent hole.
   */
  if (
    !(overlay[0] = vips_image_new_from_image(page[0],
                                             red, VIPS_NUMBER(red)))
    || vips_draw_rect(overlay[0],
                      transparent, VIPS_NUMBER(transparent),
                      10, 10, overlay[0]->Xsize - 20, overlay[0]->Ysize - 20,
                      "fill", TRUE,
                      NULL)) {
    return(-1);
  }

  /* Draw the overlay on every page.
   */
  for ( i = 0; i < n_pages; i++ ) {
    if (vips_composite2(page[i], overlay[0], &annotated[i],
                        VIPS_BLEND_MODE_OVER, NULL)) {
      return(-1);
    }
  }

  /* Reassemble the frames.
   */
  if (vips_arrayjoin(annotated, out, n_pages,
                     "across", 1,
                     NULL)) {
    return(-1);
  }

  return(0);
} /* annotate_image */

void preeval_callback(VipsImage *image, VipsProgress *progress, void *pdata) {
  printf("preeval_callback:\n");
}

void eval_callback(VipsImage *image, VipsProgress *progress, void *pdata) {
  printf("eval_callback: percent = %d\n", progress->percent);
}

void posteval_callback(VipsImage *image, VipsProgress *progress, void *pdata) {
  printf("posteval_callback: finished in %.3gs\n",
         g_timer_elapsed(progress->start, NULL));
}
VipsImage *image;

TEST t_vips_basics_test3(){
  for (int i = 0; i < 2; i++) {
    for (int o = 0; o < 4; o++) {
      char *outfile;
      asprintf(&outfile, "/tmp/output-%d-%d-%d.%s", i, o, 3, exts[o]);

      if (VIPS_INIT(files[i])) {
        FAIL();
      }

      if (!(image = vips_image_new_from_file(files[i],
                                             "access", VIPS_ACCESS_SEQUENTIAL,
                                             NULL))) {
        FAIL();
      }

      VipsImage *out;
      float     resize = (float)1 / (float)(i + 1);
      log_debug("%f|%s", resize, outfile);

      if (vips_resize(image, &out, resize, NULL)) {
        FAIL();
      }

      vips_image_set_progress(out, PROGRESS);
      g_signal_connect(out, "preeval",
                       G_CALLBACK(preeval_callback), NULL);
      g_signal_connect(out, "eval",
                       G_CALLBACK(eval_callback), NULL);
      g_signal_connect(out, "posteval",
                       G_CALLBACK(posteval_callback), NULL);

      if (vips_image_write_to_file(out, outfile, NULL)) {
        FAIL();
      }
      g_object_unref(out);

      g_object_unref(image);
    }
  }
  PASS();
} /* t_vips_basics_test3 */

TEST t_vips_basics_test2(){
  for (int i = 0; i < 2; i++) {
    for (int o = 0; o < 4; o++) {
      char *outfile, *infile;
      asprintf(&outfile, "/tmp/output-%d-%d-%d.%s", i, o, 2, exts[o]);
      asprintf(&infile, "%s", files[i]);

      VipsImage  *image;
      VipsObject *context;
      VipsImage  *x;

      if (VIPS_INIT(infile)) {
        FAIL();
      }

      if (!(image = vips_image_new_from_file(infile,
                                             "access", VIPS_ACCESS_SEQUENTIAL,
                                             NULL))) {
        FAIL();
      }

      vips_object_print_summary(VIPS_OBJECT(image));

      context = VIPS_OBJECT(vips_image_new());
      if (annotate_image(context, image, &x)) {
        g_object_unref(image);
        g_object_unref(context);
        FAIL();
      }
      g_object_unref(image);
      g_object_unref(context);
      image = x;

      if (vips_image_write_to_file(image, outfile, NULL)) {
        g_object_unref(image);
        FAIL();

        g_object_unref(image);
      }
    }
  }

  PASS();
} /* t_vips_basics_test2 */

TEST t_vips_basics_test1(){
  for (int i = 0; i < 2; i++) {
    for (int o = 0; o < 4; o++) {
      char *outfile, *infile;
      asprintf(&outfile, "/tmp/output-%d-%d-%d.%s", i, o, 1, exts[o]);
      asprintf(&infile, "%s", files[i]);

      gchar *buf;
      gsize len;
      int   i;

      if (VIPS_INIT(infile)) {
        FAIL();
      }

      if (!g_file_get_contents(infile, &buf, &len, NULL)) {
        FAIL();
      }

      for ( i = 0; i < 10; i++ ) {
        VipsImage *image;
        void      *new_buf;
        size_t    new_len;

        printf("loop %d ...\n", i);

        if (!(image = vips_image_new_from_buffer(buf, len, "",
                                                 "access", VIPS_ACCESS_SEQUENTIAL,
                                                 NULL))) {
          FAIL();
        }

        if (vips_image_write_to_buffer(image,
                                       ".jpg", &new_buf, &new_len,
                                       "Q", 95,
                                       NULL)) {
          FAIL();
        }

        g_object_unref(image);
        g_free(new_buf);
      }

      g_free(buf);
    }
  }

  PASS();
} /* t_vips_basics_test1 */

SUITE(s_vips_basics_test1) {
  RUN_TEST(t_vips_basics_test1);
}
SUITE(s_vips_basics_test2) {
  RUN_TEST(t_vips_basics_test2);
}
SUITE(s_vips_basics_test3) {
  RUN_TEST(t_vips_basics_test3);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  fsio_write_binary_file(files[0], gcommunist_goalsData, gcommunist_goalsSize);
  fsio_write_binary_file(files[1], gkitty_iconData, gkitty_iconSize);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_vips_basics_test1);
  RUN_SUITE(s_vips_basics_test2);
  RUN_SUITE(s_vips_basics_test3);
  GREATEST_MAIN_END();
  vips_shutdown();
}
