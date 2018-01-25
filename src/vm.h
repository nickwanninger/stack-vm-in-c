// Include system libs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "opcodes.h"


typedef union stackobject_t {
	int8_t i8;   // 1 byte
	int16_t i16; // 2 bytes
	int32_t i32; // 4 bytes
	int64_t i64; // 8 bytes
	float f32;   // 4 bytes 6 decimal precision
	double d64;  // 8 bytes
} stackobject_t;

typedef struct instruction {
	uint8_t opcode;
	stackobject_t operand;
} instruction_t;

size_t sp; // Stack Pointer
size_t pc; // Program counter
long opcount; // number of ops executed


typedef struct machineinfo {
	int pc;
	int fp;
	int sp;
	int opcount;
} INFO_t;


stackobject_t stack[1024]; // Create a 1KB type-independent stack (will take up typeof(long) * 1024 bytes)

void usage();

void run(char *program);

void printstack();

// static char opcodes[] = {NOOP, HALT, POP, PUSHPC, POPPC, PUSHI, ADDI, SUBI, MULI, PRINT};
// static char oplengths[] = {1, 1, 1, 1, 1, 5, 1, 1, 1, 1};




