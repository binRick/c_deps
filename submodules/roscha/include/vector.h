#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#define VEC_CAP 32

struct roscha_vector {
	size_t cap;
	size_t len;
	void **values;
};

struct roscha_vector *vector_new_with_cap(size_t cap);

#define roscha_vector_new() vector_new_with_cap(VEC_CAP)

ssize_t roscha_vector_push(struct roscha_vector *, void *val);

void *roscha_vector_pop(struct roscha_vector *);

void vector_free(struct roscha_vector *);

#define vector_foreach(vec, i, val) \
	for (i = 0, val = vec->values[i]; i < vec->len; i++, val = vec->values[i])

#endif
