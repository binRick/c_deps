////////////////////////////////////////////
#define LAY_IMPLEMENTATION
////////////////////////////////////////////
#include "layout-test/layout-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "layout/layout.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_layout_test(){
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

SUITE(s_layout_test) {
  RUN_TEST(t_layout_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_layout_test);
  GREATEST_MAIN_END();
}
