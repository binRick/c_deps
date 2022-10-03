////////////////////////////////////////////

////////////////////////////////////////////
#include "url-test/url-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
#include "url.h/url.h"

////////////////////////////////////////////
TEST t_url_test(){
  char       *gh_url = "git://git@github.com:jwerle/url.h.git";
  char       *url    = "http://user:pass@subdomain.host.com:8080/p/a/t/h?query=string#hash";

  url_data_t *parsed    = url_parse(url);
  url_data_t *gh_parsed = url_parse(gh_url);

  assert(parsed);
  assert(gh_parsed);

  url_data_inspect(parsed);
  url_data_inspect(gh_parsed);
  PASS();
}

SUITE(s_url_test) {
  RUN_TEST(t_url_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_url_test);
  GREATEST_MAIN_END();
}
