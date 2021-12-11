#include "stack_machine/stack_machine.h"

#include <stdlib.h>
#include <stdio.h>

stack_machine stack_machine_make(instr_idx instr_memory_cap)
{
	assert(instr_memory_cap > 0);

	instruction* instr_buffer = calloc(instr_memory_cap, sizeof(instruction));
	if (!instr_buffer)
	{
		return (stack_machine){0};
	}

	return (stack_machine){
		.instr_memory = instr_buffer,
		.instr_memory_cap = instr_memory_cap,
	};
}

void stack_machine_destroy(stack_machine* self)
{
	if (!self)
	{
		return;
	}

	stack_destroy(&self->stack);
	free(self->instr_memory);
	*self = (stack_machine){0};
}

void stack_machine_step(stack_machine* self)
{
	assert(self->state != SM_ERROR);

	if (self->ip == self->instr_count)
	{
		self->state = SM_HALTED;
		return;
	}

#define ENSURE_STACK_SIZE(op, size) \
	if (stack_size(&self->stack) < (size)) \
	{ \
		self->state = SM_ERROR; \
		fprintf(stderr, "Error: " #op " expects at least %d values on the stack\n", (size)); \
		break; \
	}

#define ENSURE_INSTR_ID(op, instr_id) \
	if ((instr_id) >= self->instr_count) \
	{ \
		self->state = SM_ERROR; \
		fprintf(stderr, "Error: invalid " #op " destination %" PRIu32 "\n", (instr_id)); \
		break; \
	}

#define TRY_PUSH(stack, item) \
	if (!stack_push((stack), (item))) \
	{ \
		self->state = SM_ERROR; \
		break; \
	}

	const instruction instr = self->instr_memory[self->ip];
	switch (instr.op)
	{
		// Execution control
		case OP_NOP:
			++self->ip;
			break;
		case OP_HALT:
			self->state = SM_HALTED;
			++self->ip;
			break;
		// Stack manimulation
		case OP_PUSH:
			TRY_PUSH(&self->stack, instr.num_value);
			++self->ip;
			break;
		case OP_POP:
			ENSURE_STACK_SIZE(OP_POP, 1);
			stack_pop(&self->stack);
			++self->ip;
			break;
		case OP_DUP:
			ENSURE_STACK_SIZE(OP_DUP, 1);
			TRY_PUSH(&self->stack, *stack_top(&self->stack));
			++self->ip;
			break;
		case OP_SWAP:
		{
			ENSURE_STACK_SIZE(OP_SWAP, 2);
			stack_item a = stack_pop(&self->stack);
			stack_item b = stack_pop(&self->stack);
			TRY_PUSH(&self->stack, b);
			TRY_PUSH(&self->stack, a);
			break;
		}
		// Math
		case OP_NEG:
			ENSURE_STACK_SIZE(OP_NEG, 1);
			TRY_PUSH(&self->stack, -stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_INC:
			ENSURE_STACK_SIZE(OP_INC, 1);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) + 1);
			++self->ip;
			break;
		case OP_DEC:
			ENSURE_STACK_SIZE(OP_DEC, 1);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) - 1);
			++self->ip;
			break;
		case OP_ADD:
			ENSURE_STACK_SIZE(OP_ADD, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) + stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_SUB:
		{
			ENSURE_STACK_SIZE(OP_SUB, 2);
			const stack_item b = stack_pop(&self->stack);
			const stack_item a = stack_pop(&self->stack);
			TRY_PUSH(&self->stack, a - b);
			++self->ip;
		}
		break;
		case OP_MULT:
			ENSURE_STACK_SIZE(OP_MULT, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) * stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_DIV:
			ENSURE_STACK_SIZE(OP_DIV, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) / stack_pop(&self->stack));
			++self->ip;
			break;
		// Logic
		case OP_AND:
			ENSURE_STACK_SIZE(OP_AND, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) && stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_OR:
			ENSURE_STACK_SIZE(OP_OR, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) || stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_EQUAL:
			ENSURE_STACK_SIZE(OP_EQUAL, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) == stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_NEQUAL:
			ENSURE_STACK_SIZE(OP_NEQUAL, 2);
			TRY_PUSH(&self->stack, stack_pop(&self->stack) != stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_LESS:
		{
			ENSURE_STACK_SIZE(OP_LESS, 2);
			const stack_item b = stack_pop(&self->stack);
			const stack_item a = stack_pop(&self->stack);
			TRY_PUSH(&self->stack, a < b);
			++self->ip;
			break;
		}
		case OP_GREATER:
		{
			ENSURE_STACK_SIZE(OP_GREATER, 2);
			const stack_item b = stack_pop(&self->stack);
			const stack_item a = stack_pop(&self->stack);
			TRY_PUSH(&self->stack, a > b);
			++self->ip;
			break;
		}
		// Control flow
		case OP_JUMP:
			ENSURE_INSTR_ID(OP_JUMP, instr.instr_id);
			self->ip = instr.instr_id;
			break;
		case OP_JUMP_NZ:
			ENSURE_INSTR_ID(OP_JUMP_NZ, instr.instr_id);
			ENSURE_STACK_SIZE(OP_JUMP_NZ, 1);
			if (stack_pop(&self->stack) != 0)
			{
				self->ip = instr.instr_id;
			}
			else
			{
				++self->ip;
			}
			break;
		case OP_JUMP_Z:
			ENSURE_INSTR_ID(OP_JUMP_Z, instr.instr_id);
			ENSURE_STACK_SIZE(OP_JUMP_Z, 1);
			if (stack_pop(&self->stack) == 0)
			{
				self->ip = instr.instr_id;
			}
			else
			{
				++self->ip;
			}
			break;
		// Input
		case OP_READ:
		{
			stack_item value;
			if (!scanf("%"STACK_ITEM_FMT, &value))
			{
				self->state = SM_ERROR;
				fprintf(stderr, "Error: OP_READ failed to read value\n");
				break;
			}
			TRY_PUSH(&self->stack, value);
			++self->ip;
		}
		break;
		// Output
		case OP_PRINT:
			ENSURE_STACK_SIZE(OP_PRINT, 1);
			printf("%"STACK_ITEM_FMT" ", stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_PRINT_ASCII:
			ENSURE_STACK_SIZE(OP_PRINT, 1);
			putchar((int)stack_pop(&self->stack));
			++self->ip;
			break;
		case OP_PRINT_SYM:
			putchar(instr.sym);
			++self->ip;
			break;
		default:
			self->state = SM_ERROR;
			fprintf(stderr, "Error: Unknown opcode %d\n", instr.op);
			break;
	}
#undef ENSURE_STACK_SIZE
#undef ENSURE_INSTR_ID
#undef TRY_PUSH
}

void stack_machine_reset(stack_machine* self)
{
	stack_clear(&self->stack);
	self->ip = 0;
	self->state = SM_HALTED;
}

void stack_machine_add_instr(stack_machine* self, instruction instr)
{
	assert(self);
	assert(self->instr_memory);
	assert(self->instr_count != self->instr_memory_cap);

	self->instr_memory[self->instr_count++] = instr;
}

bool stack_machine_execute(stack_machine* self)
{
	assert(self->state != SM_ERROR);

	self->state = SM_RUNNING;
	while (self->state == SM_RUNNING)
	{
		stack_machine_step(self);
	}
	putchar('\n');

	if (stack_size(&self->stack) > 1)
	{
		printf("Warning: %zu items left in the stack\n", stack_size(&self->stack));
	}
	return self->state != SM_ERROR;
}
