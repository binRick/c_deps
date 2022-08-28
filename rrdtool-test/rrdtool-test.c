////////////////////////////////////////////

////////////////////////////////////////////
#include "rrdtool-test/rrdtool-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "rrdtool/src/rrd.h"

////////////////////////////////////////////
TEST t_rrdtool_test(){
  struct timeval      tv;
  char                *val;
  size_t              updates_qty = 100;

  const unsigned long pdp_step   = 30;
  const time_t        time_start = tv.tv_sec - (pdp_step * updates_qty);
  const char          *filename  = "/tmp/d.rrd";
  const char          *argv[]    = {
    "DS:energy:GAUGE:240:0:U",
    "RRA:LAST:0.5:1:1",
    "RRA:AVERAGE:0.5:1:144",
    "RRA:AVERAGE:0.5:1:1440",
    "RRA:AVERAGE:0.5:1:10080",
    "RRA:AVERAGE:0.5:1:43800",
    "RRA:AVERAGE:0.5:10:52596",
    "RRA:MAX:0.5:1:144",
    "RRA:MAX:0.5:1:1440",
    "RRA:MAX:0.5:1:10080",
    "RRA:MAX:0.5:1:43800",
    "RRA:MAX:0.5:10:52596",
    "RRA:MIN:0.5:1:144",
    "RRA:MIN:0.5:1:1440",
    "RRA:MIN:0.5:1:10080",
    "RRA:MIN:0.5:1:43800",
    "RRA:MIN:0.5:10:52596"
  };
  int                 argc = sizeof(argv) / sizeof(argv[0]);

  if (gettimeofday(&tv, NULL)) {
    perror("gettimeofday");
    FAIL();
  }

  if (fsio_file_exists(filename) == true) {
    fsio_remove(filename);
  }

  rrd_clear_error();
  if (rrd_create_r(filename, pdp_step, time_start, argc, (void *)argv) != 0) {
    log_error("rrdtool plugin: rrd_create_r (%s) failed: %s", filename, rrd_get_error());
    FAIL();
  }
  for (size_t i = 0; i < updates_qty; i++) {
    const time_t process_time = time_start + (pdp_step * i) + 1;

    if (asprintf(&val, "%ld:%lu", process_time, i) < 0) {
      log_error("ERROR: Could not create string 'val'.");
      FAIL();
    }
    const char *argv_update[] = { val };

    rrd_update_r(filename, NULL, 1, argv_update);

    if (rrd_test_error()) {
      log_error("ERROR: RRD_update (%s): %s", filename, rrd_get_error());
      FAIL();
    }
    log_debug("#%lu/%lu> Updated rrd %s with value %s", i + 1, updates_qty, filename, val);
  }
  if (val) {
    free(val);
  }

  rrd_info_t *i = rrd_info_r(filename);

  if (i == NULL) {
    log_error("rrdtool plugin: rrd_info_r (%s) failed: %s", filename, rrd_get_error());
    FAIL();
  }
  rrd_info_print(i);
  PASS();
} /* t_rrdtool_test */

SUITE(s_rrdtool_test) {
  RUN_TEST(t_rrdtool_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_rrdtool_test);
  GREATEST_MAIN_END();
}
