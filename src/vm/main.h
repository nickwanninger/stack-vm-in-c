// Include system libs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "datatypes.h"

#include "opcodes.h"

#define true 1
#define false 0

typedef union {
	char i8;   // 1 byte
	short i16; // 2 bytes
	// int32_t i32; // 4 bytes
	// int64_t i64; // 8 bytes
	// float f32;   // 4 bytes 6 decimal precision
	// double d64;  // 8 bytes
} data_t;

typedef struct stackobject_t {
	char type;
	data_t data;
} stackobject_t;

typedef struct instruction {
	unsigned char opcode;
	stackobject_t operand;
} instruction_t;

int16_t sp; // Stack Pointer
int16_t pc; // Program counter
int64_t opcount; // number of ops executed

char debug = false;

stackobject_t stack[4098];

void usage();

void run(char *program);
void emit(stackobject_t obj);
void step(instruction_t current);
void printstack();
