
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "ck-test/ck-test.h"
#include "ck/include/ck_array.h"
#include "ck/include/ck_backoff.h"
#include "ck/include/ck_bitmap.h"
#include "ck/include/ck_cohort.h"
#include "ck/include/ck_epoch.h"
#include "ck/include/ck_hp.h"
#include "ck/include/ck_hs.h"
#include "ck/include/ck_ht.h"
#include "ck/include/ck_malloc.h"
#include "ck/include/ck_pr.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#define LEN    10
static struct ck_malloc alloc = {
  .malloc  = malloc,
  .free    = free,
  .realloc = realloc
};

TEST t_ck_bitmap(){
  bool                 r;
  unsigned int         length = 1024 * 1024 * 16;
  ck_bitmap_t          *g_bits;
  unsigned int         i;
  bool                 initial = false;
  unsigned int         bytes, base;
  ck_bitmap_iterator_t iter;

  base  = ck_bitmap_base(length);
  bytes = ck_bitmap_size(length);
  log_info("Configuration: %s", bytes_to_string(bytes));

  g_bits = malloc(bytes);
  ck_bitmap_init(g_bits, length, initial);

  for (i = 0; i < length; i++)
    if (ck_bitmap_test(g_bits, i) == !initial)
      FAILm("bm err");

  for (i = 0; i < length; i++)
    ck_bitmap_set(g_bits, i);

  for (i = 0; i < length; i++)
    if (ck_bitmap_test(g_bits, i) == initial)
      FAILm("bm err");

  for (i = 0; i < length; i++)
    ck_bitmap_reset(g_bits, i);

  PASSm("bitmap tests ok");
}

TEST t_ck_array(){
  size_t              len = 0;
  void                **items;
  ck_array_t          array;
  ck_array_iterator_t iterator;
  void                *p;
  int                 i = 0;

  if (!ck_array_init(&array, CK_ARRAY_MODE_SPMC, &alloc, LEN))
    FAILm("array init failed");

  if (!ck_array_initialized(&array))
    FAILm("init err");

  for (i = 0; i < LEN; i++)
    if (!ck_array_put(&array, (void *)(size_t)timestamp()))
      FAILm("ck_error_put");

  for (i = 0; i < LEN; i++)
    if (!ck_array_put(&array, (void *)(size_t)i))
      FAILm("ck_error_put");

  for (i = 0; i < LEN; i++)
    if (!ck_array_remove(&array, (void *)(size_t)i))
      FAILm("ck_error_remove");

  for (i = 0; i < LEN; i++)
    ck_array_put_unique(&array, (void *)(size_t)i);

  if (!ck_array_commit(&array))
    FAILm("commit err");

  items = ck_array_buffer(&array, &len);
  log_info("Array buffer len: %lu", len);
  ASSERT_EQ(len, LEN * 2);

  for (i = 0; i < len; i++)
    log_info("item- %lu", (size_t)(items[i]));

  ASSERT_EQ(ck_array_length(&array), LEN * 2);
  log_info("Array len: %d", ck_array_length(&array));

  i = 0;
  CK_ARRAY_FOREACH(&array, &iterator, &p) {
    log_info("item #%d- %lu", i, (size_t)p);
    i++;
  }

  ck_array_deinit(&array, true);
  if (ck_array_initialized(&array))
    FAILm("init err");

  PASSm("Array Tests OK");
} /* t_ck_array */

TEST t_ck_atomic(){
  int a;

  ck_pr_store_int(&a, 10);
  for (int i = 0; i < 100; i++)
    ck_pr_inc_int(&a);

  Dbg(ck_pr_load_int(&a), %d);

  PASS();
}

TEST t_ck_hash(){
  const char       *test[] = { "Samy", "Al", "Bahra", "dances", "in", "the", "wind.", "Once" };
  size_t           i, l;
  ck_ht_t          ht;
  ck_ht_entry_t    entry;
  ck_ht_hash_t     h;
  ck_ht_iterator_t iterator = CK_HT_ITERATOR_INITIALIZER;
  ck_ht_entry_t    *cursor;
  unsigned int     mode = CK_HT_MODE_BYTESTRING;

  if (ck_ht_init(&ht, mode, NULL, &alloc, 2, 6602834) == false)
    FAIL();

  for (i = 0; i < sizeof(test) / sizeof(*test); i++) {
    l = strlen(test[i]);
    ck_ht_hash(&h, &ht, test[i], l);
    ck_ht_entry_set(&entry, h, test[i], l, test[i]);
    ck_ht_put_spmc(&ht, h, &entry);
  }

  ck_ht_iterator_init(&iterator);
  while (ck_ht_next(&ht, &iterator, &cursor) == true) {
    Dbg((char *)ck_ht_entry_key(cursor), %s);
    Dbg((char *)ck_ht_entry_value(cursor), %s);
  }

  PASSm("Hash Tests OK");
}

SUITE(s_ck) {
  RUN_TEST(t_ck_array);
  RUN_TEST(t_ck_bitmap);
  RUN_TEST(t_ck_hash);
  RUN_TEST(t_ck_atomic);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_ck);
  GREATEST_MAIN_END();
}
