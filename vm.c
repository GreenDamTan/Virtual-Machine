#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "vm.h"

void vm_init(VM *vm, int *code, int code_size, int nglobals){
	vm->code = code;
	vm->code_size = code_size;
	vm->globals = calloc(nglobals, sizeof(int));
	vm->nglobals = nglobals;
}

void vm_free(VM *vm){
	free(vm->globals);
	free(vm);
}

VM *vm_create(int *code, int code_size, int nglobals){
	VM *vm = calloc(1, sizeof(VM));
	vm_init(vm, code, code_size, nglobals);
	return vm;
}

void vm_exec(VM *vm, int start){
	int sp;
	int ip;
	
	int a;
	int b;
	
	a = b = 0;
	int addr;
	ip = start;
	sp = -1;	
	int opcode = vm->code[ip];

	while(opcode != HALT && ip < vm->code_size){
		ip++;
		switch(opcode){
			case ADD:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a + b;
				break;
			case SUB:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a - b;
				break;
			case MUL:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a * b;
				break;
			case AND:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a & b;
				break;
			case OR:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a | b;
				break;
			case XOR:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = a ^ b;
				break;		
			case NOT:
				a = vm->stack[sp--];
				vm->stack[++sp] = a ? false : true;
				break;
	 		case LT:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = (a < b) ? true : false;
				break;
			case EQ:
				b = vm->stack[sp--];
				a = vm->stack[sp--];
				vm->stack[++sp] = (a == b) ? true : false;
				break;
			case PRINT:
				printf("%d\n", vm->stack[sp--]);
				break;
			case OUTCHAR:
				printf("%c", vm->stack[sp--]);
				break;
			case PUSH:
				vm->stack[++sp] = vm->code[ip++];
				break;				
			case BR:
				ip = vm->code[ip++];
				break;
		        case BRF:
				addr = vm->code[ip++];
				if(vm->stack[sp--] == false) ip = addr;	
				break;
			case DROP:
				--sp;
				break;
			case GLOAD:
				addr = vm->code[ip++];
				vm->stack[++sp] = vm->globals[addr]; 
				break;
			case GSTORE:
				addr = vm->code[ip++];
				vm->globals[addr] = vm->stack[sp--];
				break;
			default:
				printf("Invalid opcode");
				exit(1);
		}
		opcode = vm->code[ip];
	}
}

void vm_print_data(int *globals, int count){
	printf("Data memory\n");
	REP(i, count)
		printf("%04d: %d\n", i, globals[i]);
}
