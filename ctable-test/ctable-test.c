////////////////////////////////////////////
#include "ctable/src/alloc_wrappers.h"
//#include "ctable/src/constraint.h"
//#include "ctable/src/printing.h"
#include "ctable/src/string_util.h"
#include "ctable/src/table.h"
#include "ctable/src/table.h"
#include "ctable/src/vector.h"
////////////////////////////////////////////
#include "ctable-test/ctable-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_ctable_test(){
  PASS();
}

SUITE(s_ctable_test) {
  RUN_TEST(t_ctable_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_ctable_test);
  GREATEST_MAIN_END();
}
