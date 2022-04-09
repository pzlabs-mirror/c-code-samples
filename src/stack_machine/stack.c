#include "stack_machine/stack.h"

#include <stdlib.h>
#include <math.h>
#include <stdint.h>

static const double stack_growth_factor = 1.5;

extern inline stack stack_make(void);
extern inline size_t stack_size(const stack* stack);
extern inline bool stack_is_empty(const stack* stack);
extern inline stack_item* stack_top(const stack* stack);

static bool stack_ensure_capacity(stack* self, size_t capacity);

static size_t maxsz(size_t a, size_t b)
{
	return a > b ? a : b;
}

stack stack_make_reserved(size_t capacity)
{
	if (capacity == 0)
	{
		return stack_make();
	}

	stack_item* const buffer = malloc(capacity * sizeof(stack_item));
	if (!buffer)
	{
		return stack_make();
	}

	return (stack){.data = buffer, .size = 0, .capacity = capacity};
}

void stack_destroy(stack* self)
{
	if (!self)
	{
		return;
	}

	free(self->data);
	// resetting data ensures the idempotence of stack_destroy
	*self = stack_make();
}

stack_item* stack_push(stack* self, stack_item item)
{
	assert(self);

	if (!stack_ensure_capacity(self, self->size + 1))
	{
		return NULL;
	}

	++self->size;
	self->data[self->size - 1] = item;

	return &self->data[self->size - 1];
}

static bool stack_ensure_capacity(stack* self, size_t requested_capacity)
{
	assert(self);

	if (requested_capacity <= self->capacity)
	{
		return true;
	}

	const double estimated_capacity = ceil((double)self->capacity * stack_growth_factor);
	const size_t new_capacity = estimated_capacity < (double)SIZE_MAX
		? maxsz((size_t)estimated_capacity, requested_capacity)
		: SIZE_MAX;

	stack_item* const buffer = realloc(self->data, new_capacity * sizeof(stack_item));
	if (!buffer)
	{
		return false;
	}
	self->data = buffer;
	self->capacity = new_capacity;
	return true;
}

stack_item stack_pop(stack* self)
{
	assert(self);
	assert(self->size > 0);

	--self->size;
	return self->data[self->size];
}

void stack_clear(stack* self)
{
	assert(self);

	self->size = 0;
}
