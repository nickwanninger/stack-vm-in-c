#include "vm.h"



void printstk() {
	// size_t stacksize = sizeof(stack)/sizeof(stackobject_t);
	printf("\x1B[36mSTACK:\t");
	
	int i;
	for (i = 0; i < sp + 1; i++) {
		printf("0x%04x ", stack[i].data.i32);
	}

	printf("\x1B[0m\n");
}


void emit(stackobject_t *obj) {

	switch (obj->type) {
		case I32_T:
			printf("%d\n", obj->data.i32);
		break;
	}
	
}

int halt() {
	return 0;
}


int main (int argc, char **argv) {

	
	pc = 0;
	sp = -1;
	opcount = 0;
	FILE *source_file = fopen(argv[1], "rb");
	// instruction_t *code;
	char *codebytes;

	// seek to the end of the source file
	fseek(source_file, 0, SEEK_END);
	// get the position (size)
	long fsize = ftell(source_file);
	// Check if teh filesize is a valid number of bits
	if (fsize % sizeof(uint8_t) != 0) {
		printf("error: malformed bitpattern in source\n");
		return 1;
	}
	// move back to the start
	rewind(source_file);
	// allocate enough space for the entire file
	codebytes = malloc(fsize + 1);
	// read the entire file into the codebytes string
	fread(codebytes, fsize, 1, source_file);
	// close the file
	fclose(source_file);


	unsigned long bytecount = fsize * sizeof(uint8_t);
	// Allocate memory for the code struct array
	// To be safe, I'll allocate enough for each byte
	// of code. This *may* get stripped down later.
	// code = calloc(bytecount, sizeof(instruction_t));
	instruction_t code[bytecount];
	uint32_t ic = 0;

	for (size_t i = 0; i < bytecount; i++) {
		// Guard against out of bounds errors
		// Allow equals because HALT or other
		// OPS are only 1 byte
		if (i <= bytecount) {
			// Allocate memory for each instruction
			instruction_t *instr = calloc(1, sizeof(instruction_t));
			uint8_t op = codebytes[i];
			instr->opcode = op;
			// only argument based instructions will be handled as
			// all other instructions need only contain the opcode
			if (op == PI32) {
				instr->operand.type = I32_T;
				instr->operand.data.i32 = *(int*)(codebytes + i + 1);
				i += 4;
			}

			code[ic] = *instr;
			ic++;
		} else {
			break;
		}
	}


	instruction_t current = code[pc];
	while (current.opcode != HALT) {

		data_t a;
		data_t b;
		// stackobject_t newobj;
		switch (current.opcode) {
			case PI32:
				sp++;
				pc++;
				stack[sp].type = I32_T;
				stack[sp].data.i32 = current.operand.data.i32;
				break;

			case ADDI:
				a.i64 = stack[sp--].data.i64;
				b.i64 = stack[sp--].data.i64;
				sp++;
				stack[sp].type = I32_T;
				stack[sp].data.i32 = a.i64 + b.i64;
				pc++;
				break;

			case EMIT:
				// Pop and emit the value at the pointer pointer
				emit(&stack[sp--]);
				pc++;
				break;
			
			
			default:
				// Unknown code, do something in the future.
				pc++;
				break;


			case HALT:
				return halt();
		}

		printstk();
		opcount++;
		current = code[pc];
	}
	

	return 0;
}
