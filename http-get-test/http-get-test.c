////////////////////////////////////////////

////////////////////////////////////////////
#include "http-get-test/http-get-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "http-get.c/src/http-get.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_http_get_test(){
  http_get_response_t *res = http_get("https://api.github.com/repos/clibs/clib/releases/latest");

  printf("\nok=%d\n", res->ok);
  printf("status=%lu\n", res->status);
  printf("content=%s\n\n", res->data);
  http_get_free(res);

  char *f = "./google.html";
  int  ok = http_get_file("http://google.com", f);

  printf("\nok=%d\n", ok);
  printf("file exists:%d\n\n", fsio_file_exists(f));

  PASS();
}

SUITE(s_http_get_test) {
  RUN_TEST(t_http_get_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_http_get_test);
  GREATEST_MAIN_END();
}
