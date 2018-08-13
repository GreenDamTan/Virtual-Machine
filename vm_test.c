#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "vm.h"

int check_if_power_of_two[] = {
	PUSH, 64,
	PUSH, 64,
	PUSH, 1,
	SUB,	
	AND,
	PRINT,
	
	HALT
};

int hello_world[] = {
	PUSH, 10,  PUSH, 33,  PUSH, 100,
	PUSH, 108, PUSH, 114, PUSH, 111,
	PUSH, 87,  PUSH, 32,  PUSH, 44,
	PUSH, 111, PUSH, 108, PUSH, 108,
   	PUSH, 101, PUSH, 72,   
	
	OUTCHAR, OUTCHAR, OUTCHAR,
	OUTCHAR, OUTCHAR, OUTCHAR,
	OUTCHAR, OUTCHAR, OUTCHAR,
	OUTCHAR, OUTCHAR, OUTCHAR,
	OUTCHAR, OUTCHAR,
	
	HALT
};

int loop[] = {
	PUSH, 15,
	GSTORE, 0,

	PUSH, 0,
	GSTORE, 1,

	GLOAD, 1,
	GLOAD, 0,
	LT,
	BRF, 24,

	GLOAD, 1,
	PUSH, 1,
	ADD,
	GSTORE, 1,
	BR, 8,

	HALT
};

int main(void){
	VM *vm = vm_create(check_if_power_of_two, sizeof(check_if_power_of_two), 0);
	vm_exec(vm, 0);
	vm_free(vm);

	printf("\n");

	vm = vm_create(hello_world, sizeof(hello_world), 0);
	vm_exec(vm, 0);
	vm_free(vm);

	printf("\n");

	float distance1 = (clock() / (CLOCKS_PER_SEC/1000));
	vm = vm_create(loop, sizeof(loop), 2);
	vm_exec(vm, 0);
	vm_print_data(vm->globals, vm->nglobals);
	vm_free(vm);
	float distance2 = (clock() / (CLOCKS_PER_SEC/1000));
	printf("Duration: %d ms\n", (distance2 - distance1));
}
