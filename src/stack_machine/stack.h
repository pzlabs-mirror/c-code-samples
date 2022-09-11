#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

typedef int64_t stack_item;
#define STACK_ITEM_FMT PRId64

typedef struct
{
	stack_item* data;
	size_t size;
	size_t capacity;
} stack;

inline stack stack_make(void)
{
	return (stack){.data = NULL, .size = 0, .capacity = 0};
}

stack stack_make_reserved(size_t capacity);
void stack_destroy(stack* stack);

inline size_t stack_size(const stack* self)
{
	assert(self);
	return self->size;
}

inline bool stack_is_empty(const stack* self)
{
	assert(self);
	return self->size == 0;
}

inline stack_item* stack_top(const stack* self)
{
	assert(self);
	assert(self->data);
	assert(self->size > 0);

	return &self->data[self->size - 1];
}

stack_item* stack_push(stack* self, stack_item item);
stack_item stack_pop(stack* self);

void stack_clear(stack* self);

#endif // STACK_H
