#include <stdio.h>
#include "machineinfo.c"
#include "opcodes.c"

int run(unsigned char *program, struct machineinfo *info) {

	return 0; // Return 0, nothing bad happened. (or at least we hope nothing did...)
}

int main () {
	// Hardcoded program for now.
	// TODO: Read from either stdin or as a parameter
	unsigned char program[] = {PUSHI, 1, PUSHI, 1, PRINT, HALT};
	// Create the struct to store the machine's information
	struct machineinfo info;
	// initialize the program counter to the "main" pointer location
	// Eventually this will be read from the top of a file from a header of sorts,
	//    but for now, it's hard coded.
	info.pc = 0;
	// initialize the frame pointer at -1 so everything is in
	// the currently active scope.
	info.fp = -1;
	// Run the program and return the status-code from the execution
	return run(program, &info);
}


