////////////////////////////////////////////

////////////////////////////////////////////
#include "logy-test/logy-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "logy/include/logy/logger.h"

////////////////////////////////////////////
TEST t_logy_test(){
  Logger     logger;

  LogyResult logyResult = createLogger("logs", INFO_LOG_LEVEL, true, 0.0, false, &logger);

  if (logyResult != SUCCESS_LOGY_RESULT)
    FAIL();

  int someValue = 123;

  logMessage(logger, INFO_LOG_LEVEL, "Logged value: %d", someValue);

  destroyLogger(logger);

  PASS();
}

SUITE(s_logy_test) {
  RUN_TEST(t_logy_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_logy_test);
  GREATEST_MAIN_END();
}
