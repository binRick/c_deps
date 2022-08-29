////////////////////////////////////////////
#define PANIC_UNWIND_SUPPORT    1
////////////////////////////////////////////
#include "panic-test/panic-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "panic/sources/panic.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////

double divide(const double dividend, const double divisor) {
  panic_when(0 == divisor);
  return(dividend / divisor);
}

int main(const int argc, const char **argv) {
//    printf("%lf\r\n", divide(8, 0));
}
