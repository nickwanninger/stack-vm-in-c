#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"
#include <stdint.h>

int main(int argc, char **argv) {
	FILE *inputfile;
	FILE *outputfile;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	char opcode[8];
	char arg1[24];
	char arg2[24];

	inputfile = fopen(argv[1], "r");
	outputfile = fopen("output", "wb");
	// check if the file exists or not
	if (!inputfile) {
		exit(EXIT_FAILURE);
	}

	// Loop over each line and write data to the binary file as needed.
	while ((read = getline(&line, &len, inputfile)) != -1) {
		size_t parsecount = sscanf(line, "%s %s %s", opcode, arg1, arg2);
		if (parsecount > 0) {

			// Handle NOOP
			if (strcmp(opcode, "NOOP") == 0) {
				uint8_t op = NOOP;
				fwrite(&op, sizeof(op), 1, outputfile);
			}

			// Handle HALT
			if (strcmp(opcode, "HALT") == 0) {
				uint8_t op = HALT;
				fwrite(&op, sizeof(op), 1, outputfile);
			}

			// Handle EMIT
			if (strcmp(opcode, "EMIT") == 0) {
				uint8_t op = EMIT;
				fwrite(&op, sizeof(op), 1, outputfile);
			}

			// Handle PI16
			if (strcmp(opcode, "PI16") == 0) {
				uint8_t op = PI16;
				int16_t a = atoi(arg1);
				fwrite(&op, sizeof(op), 1, outputfile);
				fwrite(&a, sizeof(a), 1, outputfile);
			}

			// Handle ADDI
			if (strcmp(opcode, "ADDI") == 0) {
				uint8_t op = ADDI;
				fwrite(&op, sizeof(op), 1, outputfile);
			}
			// Handle JUMP
			if (strcmp(opcode, "JUMP") == 0) {
				uint8_t op = JUMP;
				int16_t a = (int16_t)atol(arg1);
				fwrite(&op, sizeof(op), 1, outputfile);
				fwrite(&a, sizeof(a), 1, outputfile);
			}
		}
	}

	// Close the files
	fclose(inputfile);
	fclose(outputfile);

	return 0;
}
