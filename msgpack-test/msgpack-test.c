////////////////////////////////////////////

////////////////////////////////////////////
#include "msgpack-test/msgpack-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "msgpack_c/include/msgpack.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
void print(char const *buf, size_t len){
  size_t i = 0;

  for ( ; i < len; ++i) {
    printf("%02x ", 0xff & buf[i]);
  }
  printf("\n");
}

TEST t_msgpack_simple(){
  msgpack_sbuffer sbuf;
  msgpack_packer  pk;
  msgpack_zone    mempool;
  msgpack_object  deserialized;

  /* msgpack::sbuffer is a simple buffer implementation. */
  msgpack_sbuffer_init(&sbuf);

  /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
  msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

  msgpack_pack_array(&pk, 3);
  msgpack_pack_int(&pk, 1);
  msgpack_pack_true(&pk);
  msgpack_pack_str(&pk, 7);
  msgpack_pack_str_body(&pk, "example", 7);

  print(sbuf.data, sbuf.size);

  /* deserialize the buffer into msgpack_object instance. */
  /* deserialized object is valid during the msgpack_zone instance alive. */
  msgpack_zone_init(&mempool, 2048);

  msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

  /* print the deserialized object. */
  msgpack_object_print(stdout, deserialized);
  puts("");

  msgpack_zone_destroy(&mempool);
  msgpack_sbuffer_destroy(&sbuf);
  PASS();
}

TEST t_msgpack_test(){
  msgpack_sbuffer sbuf;

  msgpack_sbuffer_init(&sbuf);

  /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
  msgpack_packer pk;

  msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

  msgpack_pack_array(&pk, 3);
  msgpack_pack_int(&pk, 1);
  msgpack_pack_true(&pk);
  msgpack_pack_str(&pk, 7);
  msgpack_pack_str_body(&pk, "example", 7);

  /* deserialize the buffer into msgpack_object instance. */
  /* deserialized object is valid during the msgpack_zone instance alive. */
  msgpack_zone mempool;

  msgpack_zone_init(&mempool, 2048);

  msgpack_object deserialized;

  msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

  /* print the deserialized object. */
  msgpack_object_print(stdout, deserialized);
  puts("");

  msgpack_zone_destroy(&mempool);
  msgpack_sbuffer_destroy(&sbuf);
  PASS();
}

SUITE(s_msgpack_test) {
  RUN_TEST(t_msgpack_test);
  RUN_TEST(t_msgpack_simple);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_msgpack_test);
  GREATEST_MAIN_END();
}
