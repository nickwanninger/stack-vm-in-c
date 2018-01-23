#include<stdio.h>
#include "machineinfo.c"
#include "opcodes.c"

int run(unsigned char *program, struct machineinfo *info) {

	opNOOP(program, info);
	return 0; // Return 0, nothing went wrong!
}

int main () {


	unsigned char program[] = {PUSHI, 1, PUSHI, 1, PRINT, HALT};
	struct machineinfo info;
	info.pc = 0;
	info.fp = -1;

	int programstatuscode = run(program, &info);
	return programstatuscode;
}


