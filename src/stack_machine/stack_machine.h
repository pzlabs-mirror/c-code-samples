#ifndef STACK_MACHINE_H
#define STACK_MACHINE_H

#include "stack_machine/stack.h"

typedef enum opcode
{
	// Execution control
	OP_NOP, // do nothing
	OP_HALT, // stop execution

	// Stack manipulation
	OP_PUSH, // push arg0
	OP_POP, // pop
	OP_DUP, // duplicate the top stack value
	OP_SWAP, // swap top two stack values

	// Math
	OP_NEG, // pop a, push -a
	OP_INC, // pop a, push a + 1
	OP_DEC, // pop a, push a - 1
	OP_ADD, // pop b, pop a, push a + b
	OP_SUB, // pop b, pop a, push a - b
	OP_MULT, // pop b, pop a, push a * b
	OP_DIV, // pop b, pop a, push a * b

	// Logic
	OP_AND, // pop b, pop a, push a && b
	OP_OR, // pop b, pop a, push a || b
	OP_EQUAL, // pop b, pop a, push a == b
	OP_NEQUAL, // pop b, pop a, push a != b
	OP_LESS, // pop b, pop a, push a < b
	OP_GREATER, // pop b, pop a, push a > b

	// Control flow
	OP_JUMP, // jump to instruction arg0
	OP_JUMP_NZ, // pop a, jump to instructio arg0 if a != 0
	OP_JUMP_Z, // pop a, jump to instructio arg0 if a == 0

	// Input
	OP_READ, // Read a from stdin, push a

	// Output
	OP_PRINT, // pop a, print a
	OP_PRINT_ASCII, // pop a, print a as an ASCII character
	OP_PRINT_SYM // print arg0
} opcode;

typedef uint32_t instr_idx;
#define INSTR_IDX_FMT PRIu32

typedef struct instruction
{
	opcode op;
	union
	{
		stack_item num_value;
		char sym;
		instr_idx instr_id;
	};

} instruction;

typedef enum sm_state
{
	SM_HALTED,
	SM_RUNNING,
	SM_ERROR
} sm_state;

typedef struct stack_machine
{
	stack stack;
	instruction* instr_memory;
	instr_idx instr_memory_cap;
	instr_idx instr_count;
	instr_idx ip; // instruction pointer
	sm_state state;
} stack_machine;

stack_machine stack_machine_make(instr_idx instr_memory_cap);
void stack_machine_destroy(stack_machine* self);

void stack_machine_reset(stack_machine* self);
void stack_machine_add_instr(stack_machine* self, instruction instr);

void stack_machine_step(stack_machine* self);
bool stack_machine_execute(stack_machine* self);

#endif // STACK_MACHINE_H
