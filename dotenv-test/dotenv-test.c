////////////////////////////////////////////

////////////////////////////////////////////
#include "dotenv-test/dotenv-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "dotenv-c/src/dotenv.h"
#include "log/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_dotenv_test(){
  fsio_write_text_file("/tmp/.env",
                       "EXTRA_VAR=\"xxxxxxxxx\""
                       "\nV1=\"v1data\""
                       "\nV2='v2data'"
                       "\nV3=v3data"
                       "\nEMPTY="
                       "\n"
                       );
  env_load("/tmp/.env", false);
  printf("EXTRA_VAR: %s\n", getenv("EXTRA_VAR"));
  printf("V1: %s\n", getenv("V1"));
  printf("V2: %s\n", getenv("V2"));
  printf("V3: %s\n", getenv("V3"));
  printf("EMPTY: %s\n", getenv("EMPTY"));
  PASS();
}

SUITE(s_dotenv_test) {
  RUN_TEST(t_dotenv_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_dotenv_test);
  GREATEST_MAIN_END();
}
