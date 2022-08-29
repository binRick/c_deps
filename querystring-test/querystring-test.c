////////////////////////////////////////////

////////////////////////////////////////////
#include "querystring-test/querystring-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log.h/log.h"
#include "querystring.c/querystring.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
struct parsed_data {
  char *name;
  int  age;
  int  size;
};

void querystring_parser(void *data, char *fst, char *snd) {
  struct parsed_data *parsed_data = (struct parsed_data *)data;

  if (strcmp(fst, "name") == 0) {
    parsed_data->name = snd;
  }else if (strcmp(fst, "age") == 0) {
    parsed_data->age = atoi(snd);
  }
}

TEST t_querystring_test(){
  char               *qs;
  struct parsed_data data = {
    .name = "Anonymous",
    .age  = -1,
    .size = -1,
  };

  asprintf(&qs, "name=%s&age=%d&aaaaaaaaaa=123&size=%d", "abc", 123, 1000);

  parse_querystring(qs, (void *)&data, querystring_parser);

  printf("name: %s, age: %d, size: %d\n", data.name, data.age, data.size);
  PASS();
}

SUITE(s_querystring_test) {
  RUN_TEST(t_querystring_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_querystring_test);
  GREATEST_MAIN_END();
}
