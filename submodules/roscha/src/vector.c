#include "vector.h"

static inline bool
vector_grow(struct roscha_vector *vec)
{
	vec->cap *= 2;
	vec->values = realloc(vec->values, sizeof(vec->values) * vec->cap);
	return vec->values != NULL;
}

struct roscha_vector *
vector_new_with_cap(size_t cap)
{
	struct roscha_vector *vec = malloc(sizeof(*vec));
	if (!vec) return NULL;
	vec->values = malloc(sizeof(vec->values) * cap);
	if (!vec->values) {
		free(vec);
		return NULL;
	}
	vec->cap = cap;
	vec->len = 0;

	return vec;
}

ssize_t
vector_push(struct roscha_vector *vec, void *val)
{
	if (vec->len >= vec->cap && !vector_grow(vec)) return -1;
	vec->values[vec->len] = val;
	vec->len++;

	return vec->len - 1;
}

void *
vector_pop(struct roscha_vector *vec)
{
	if (vec->len == 0) return NULL;
	return vec->values[--vec->len];
}

void
vector_free(struct roscha_vector *vec)
{
	free(vec->values);
	free(vec);
}
