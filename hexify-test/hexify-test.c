////////////////////////////////////////////

////////////////////////////////////////////
#include "hexify-test/hexify-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "hexify_c/hexify.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

char hexTab[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', };

char nibbleToHex(unsigned char n){
  return(hexTab[n]);
}

void byteToHex(unsigned char n, char *hex){
  *hex++ = hexTab[n >> 4];
  *hex++ = hexTab[n & 0xf];
}

char *byteToHexString(unsigned char n){
  char hex[3];

  byteToHex(n, hex);
  hex[2] = 0;
  return(strdup(hex));
}

char hexToNibble(char n){
  return(n - (n <= '9' ? '0' : ('a' - 10)));
}

unsigned char hexToByte(char *hex){
  unsigned char n = hexToNibble(*hex++);

  n <<= 4;
  n  += hexToNibble(*hex++);
  return(n);
}

void hexBinaryString(unsigned char *in, int inSize, char *out, int outSize){
  assert(inSize * 2 + 1 <= outSize);
  while (--inSize >= 0) {
    unsigned char c = *in++;
    *out++ = hexTab[c >> 4];
    *out++ = hexTab[c & 0xf];
  }
  *out = 0;
}

////////////////////////////////////////////
struct person_t {
  char *name;
  int  age;
};

TEST t_hexify_test_vector(){
  struct person_t *x = calloc(1, sizeof(struct person_t));

  x->name = "richard";
  x->age  = 40;
  struct person_t x1 = {
    .name = "rich",
    .age  = 666,
  };
  struct Vector   *v = vector_new();

  vector_push(v, (void *)"abc123");
  vector_push(v, (void *)timestamp());
  vector_push(v, (void *)x);
  vector_push(v, (void *)&x1);
  log_debug("capacity: %lu", vector_capacity(v));
  log_debug("size: %lu", vector_size(v));
  void **arr = vector_to_array(v);

  log_debug("sizeof arr: %lu", sizeof(arr));
  PASS();
}

TEST t_hexify_test_str(){
  char *s1 = fsio_read_text_file("/etc/passwd");

  s1 = "abc def";
  char hex[strlen(s1) * 2 + 1];

  hexBinaryString(s1, strlen(s1), &hex, sizeof(hex));

  for (size_t i = 0; i < strlen(hex); i += 2) {
    char *h = stringfn_substring(hex, i, 2);
    char b  = hexToByte(h);
    log_debug("#%lu/%lu> %s => %c", i, strlen(hex), h, b);
  }
  PASS();
}

TEST t_hexify_test(){
  unsigned char binary[4];

  binary[0] = 0xde;
  binary[1] = 0xad;
  binary[2] = 0xbe;
  binary[3] = 0xef;

  char hex[8 + 1];

  hexify(binary, sizeof(binary), hex, sizeof(hex));
  log_debug("hex:      %s", hex);

  PASS();
}

SUITE(s_hexify_test) {
  RUN_TEST(t_hexify_test);
  RUN_TEST(t_hexify_test_str);
  RUN_TEST(t_hexify_test_vector);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_hexify_test);
  GREATEST_MAIN_END();
}
