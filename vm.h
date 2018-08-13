#ifndef VM_H_
#define VM_H_

#ifdef __cpluplus
extern "C"{
#endif

#define MAX_STACK_SIZE 1024
#define REP(i, n) for(int i=0; i<n; i++)

typedef enum{
	NOP = 0,
	ADD = 1,
	SUB = 2,
	AND = 3,
	OR = 4,
	XOR = 5,
	IN = 6,
	NOT = 7,
	SWAP = 8,
	MUL = 9,
	LT = 10,
	EQ = 11,
	PUSH = 12,
	LOAD = 13,
	GLOAD = 14,
	STORE = 15,
	GSTORE = 16,
	PRINT = 17,
	DROP = 18,
	BR = 19,
	BRF = 20,	
	OUTCHAR = 21,
	HALT = 22
} CODES;

typedef struct{
	int *code;
	int code_size;
	
	int *globals;
	int nglobals;

	int stack[MAX_STACK_SIZE];
} VM;

VM *vm_create(int *code, int code_size, int nglobals);
void vm_init(VM *vm, int *code, int code_size, int nglobals);
void vm_free(VM *vm);
void vm_exec(VM *vm, int start);
void vm_print_data(int *globals, int count);

#ifdef __cpluplus
}
#endif

#endif
