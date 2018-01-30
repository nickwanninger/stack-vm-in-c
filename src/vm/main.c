#include "main.h"
#include <unistd.h>

void printstk() {
	// size_t stacksize = sizeof(stack)/sizeof(stackobject_t);
	printf("\x1B[36mSTACK:\t");
	printf("PC: %d\t", pc);
	printf("SP: %d\t", sp);
	printf("| ");
	int i;
	for (i = 0; i < sp + 1; i++) {
		printf("%d ", stack[i].data.i16);
	}
	printf("\x1B[0m\n");
}

void clearConsole() {
	printf("\e[1;1H\e[2J");
}

void printInstruction(instruction_t *i) {
	printf("\x1b[34m");
	printf("OPCODE: 0x%02x\n", i->opcode);
	printf("\x1B[0m");
}

int halt() {
	return 0;
}

void emit(stackobject_t obj) {
	switch (obj.type) {
		case I16_T:
			printf("%d", obj.data.i16);
		break;
	}
}

void printUsage() {
	printf("Usage: vm [options] <file>\n");
}

void printHelp() {
	printUsage();
	printf("Options:\n");
	printf("  -h    Show help (this screen)\n");
	printf("  -d    Enable debug mode\n");
}

int main (int argc, char **argv) {
	// The filename will always be the last argument
	char *filename = argv[argc - 1];

	// Option parsing from K&R
	// Explained: http://www.usrsb.in/How-Old-School-C-Programmers-Process-Arguments.html
	char *s;
	while (--argc > 0 && (*++argv)[0] == '-') {
		for(s = argv[0]+1; *s != '\0'; s++) {
			switch(*s) {
				case 'h':
					printHelp();
					return 0;
					break;
				case 'd':
					debug = true;
					break;
				default:
					printf("\x1b[31mIllegal Option: %c\e[0m\n", *s);
					argc = 0;
					break;
			}
		}
	}


	if (filename[0] == '-') {
		printUsage();
		return 10;
	}

	pc = 0;
	sp = -1;
	opcount = 0;
	FILE *source_file = fopen(filename, "rb");
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
			if (op == PI16) {
				instr->operand.type = I16_T;
				instr->operand.data.i16 = *(int16_t*)(codebytes + i + 1);
				i += 2;
			}
			if (op == JUMP) {
				instr->operand.type = I16_T;
				instr->operand.data.i16 = *(int16_t*)(codebytes + i + 1);
				i += 2;
			}
			code[ic] = *instr;
			ic++;
		} else {
			break;
		}
	}


	instruction_t current = code[pc];
	while (current.opcode != HALT) {
		if (debug) {
			// clearConsole();
			printf("\x1b[31mOP #%lld\x1b[0m\n", opcount);
			printInstruction(&current);
			printf("Stack before OP:\n\t");
			printstk();
			printf("\x1B[32m");
			printf("DEBUG: press <enter> to run instruction");
			printf("\x1B[0m\n");
			getchar();
		}

		// Run the current instruction
		step(current);
		// increment opcount for debug
		opcount++;
		// Set the current instruction to
		// the one at the program counter
		current = code[pc];
	}

	return 0;
}


void step(instruction_t current) {
		data_t a;
		data_t b;

		// stackobject_t newobj;
		switch (current.opcode) {
			case PI16:
				sp += 1;
				stack[sp].type = I16_T;
				stack[sp].data.i16 = current.operand.data.i16;
				pc++;
				break;

			case ADDI:
				a.i16 = stack[sp--].data.i16;
				b.i16 = stack[sp--].data.i16;
				sp++;
				stack[sp].type = I16_T;
				stack[sp].data.i16 = a.i16 + b.i16;
				pc++;
				break;

			case EMIT:
				emit(stack[sp--]);
				pc++;
				break;

			case JUMP:
				pc = current.operand.data.i16;
				break;

			default:
				// Unknown code, do something in the future.
				pc++;
				break;

			case HALT:
				break;
		}
}

