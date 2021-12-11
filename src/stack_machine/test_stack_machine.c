#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "stack_machine/stack_machine.h"

int main(void)
{
	stack_machine vm = stack_machine_make(1000);
	if (!vm.instr_memory)
		exit(1);

	// Byte code below is equivalent to the following snippet:
	//     scanf("%d", n)
	//     while (n) {
	//         printf("%d ", n * n);
	//         --n;
	//     }

	stack_machine_add_instr(&vm, (instruction){.op = OP_READ});
	stack_machine_add_instr(&vm, (instruction){.op = OP_DUP});
	stack_machine_add_instr(&vm, (instruction){.op = OP_JUMP_Z, .instr_id = 9});
	stack_machine_add_instr(&vm, (instruction){.op = OP_DUP});
	stack_machine_add_instr(&vm, (instruction){.op = OP_DUP});
	stack_machine_add_instr(&vm, (instruction){.op = OP_MULT});
	stack_machine_add_instr(&vm, (instruction){.op = OP_PRINT});
	stack_machine_add_instr(&vm, (instruction){.op = OP_DEC});
	stack_machine_add_instr(&vm, (instruction){.op = OP_JUMP, .instr_id = 1});
	stack_machine_add_instr(&vm, (instruction){.op = OP_PRINT_SYM, .sym = 'E'});
	stack_machine_add_instr(&vm, (instruction){.op = OP_PRINT_SYM, .sym = 'N'});
	stack_machine_add_instr(&vm, (instruction){.op = OP_PUSH, .num_value = 68});
	stack_machine_add_instr(&vm, (instruction){.op = OP_PRINT_ASCII});

	stack_machine_execute(&vm);

	stack_machine_destroy(&vm);
}
