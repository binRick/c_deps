////////////////////////////////////////////

////////////////////////////////////////////
#include "url-router-test/url-router-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "timestamp/timestamp.h"
#include "url_router/include/url_router/url_router.h"

////////////////////////////////////////////
TEST t_url_router_test(){
  char             *str1 = "hello world1";
  char             *str2 = "woooooooooo";
  char             *arg;
  char             *data;

  URL_ROUTER_ERROR err;
  struct Dict      *args;
  UrlRouter        *r = url_router_new();

  err = url_router_insert(r, "/a/b/c", str1);
  if (err != URL_ROUTER_E_OK) {
    printf("Insert /a/b/c failed\n");
    return(-1);
  }

  err = url_router_match(r, "/a/b/c", &args, (void **)&data);
  if (err == URL_ROUTER_E_OK)
    printf("data:    %s\n", data);
  url_router_dict_free(args);

  err = url_router_insert(r, "/r/:var/:var", str2);
  if (err != URL_ROUTER_E_OK) {
    printf("Insert /r/:var/c failed\n");
    return(-1);
  }

  err = url_router_match(r, "/r/b/c", &args, (void **)&data);
  if (err == URL_ROUTER_E_OK) {
    char *var = dict_get(args, "var");
    if (var != NULL)
      printf("Args: %s\n", var);
  }
  url_router_dict_free(args);
  url_router_free(r);

  printf("Done\n");
  PASS();
} /* t_url_router_test */

SUITE(s_url_router_test) {
  RUN_TEST(t_url_router_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_url_router_test);
  GREATEST_MAIN_END();
}
