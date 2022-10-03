#include "list-test.h"
#include "submodules/log/log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

//////////////////////////////////////////////
TEST t_list_iterate_reverse(void){
  list_t          *langs = list_new();

  list_node_t     *c    = list_rpush(langs, list_node_new("c"));
  list_node_t     *js   = list_rpush(langs, list_node_new("js"));
  list_node_t     *ruby = list_rpush(langs, list_node_new("ruby"));

  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(langs, LIST_TAIL);

  while ((node = list_iterator_next(it))) {
    fprintf(stderr, "\tITERATE> %s\n", (char *)node->val);
  }

  list_iterator_destroy(it);
  list_destroy(langs);
  PASS();
}

TEST t_list_iterate(void){
  list_t          *langs = list_new();

  list_node_t     *c    = list_rpush(langs, list_node_new("c"));
  list_node_t     *js   = list_rpush(langs, list_node_new("js"));
  list_node_t     *ruby = list_rpush(langs, list_node_new("ruby"));

  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(langs, LIST_HEAD);

  while ((node = list_iterator_next(it))) {
    fprintf(stderr, "\tITERATE> %s\n", (char *)node->val);
  }

  list_iterator_destroy(it);
  list_destroy(langs);
  PASS();
}

TEST t_list_find(void){
  list_t      *langs = list_new();
  list_node_t *js    = list_rpush(langs, list_node_new("js"));
  list_node_t *a     = list_find(langs, "js");
  list_node_t *c     = list_find(langs, "ABSENT");

  assert(js == a);
  assert(NULL == c);

  list_destroy(langs);

  PASS();
}

TEST t_list_indexed(void){
  list_t      *list = list_new();
  list_node_t *a    = list_node_new("a");
  list_node_t *b    = list_node_new("b");
  list_node_t *c    = list_node_new("c");

  list_rpush(list, a);
  list_rpush(list, b);
  list_rpush(list, c);

  assert(a == list_at(list, 0));
  assert(b == list_at(list, 1));
  assert(c == list_at(list, 2));
  assert(NULL == list_at(list, 3));

  assert(c == list_at(list, -1));
  assert(b == list_at(list, -2));
  assert(a == list_at(list, -3));
  assert(NULL == list_at(list, -4));

  list_destroy(list);
  PASS();
}

TEST t_list_push(void){
  list_t      *list = list_new();
  list_node_t *a    = list_node_new("a");
  list_node_t *b    = list_node_new("b");
  list_node_t *c    = list_node_new("c");

  list_rpush(list, a);
  list_rpush(list, b);
  list_rpush(list, c);

  assert(a == list->head);
  assert(c == list->tail);
  assert(3 == list->len);
  assert(b == a->next);
  assert(NULL == a->prev);
  assert(c == b->next);
  assert(a == b->prev);
  assert(NULL == c->next);
  assert(b == c->prev);

  list_destroy(list);
  PASS();
}

TEST t_list_node(void){
  char        *val  = "some value";
  list_node_t *node = list_node_new(val);

  assert(node->val == val);
  free(node);
  PASS();
}

GREATEST_MAIN_DEFS();

SUITE(t_list){
  RUN_TEST(t_list_node);
  RUN_TEST(t_list_push);
  RUN_TEST(t_list_indexed);
  RUN_TEST(t_list_find);
  RUN_TEST(t_list_iterate);
  RUN_TEST(t_list_iterate_reverse);
  PASS();
}

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(t_list);

  GREATEST_MAIN_END();
  return(0);
}
