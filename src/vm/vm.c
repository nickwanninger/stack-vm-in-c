#include "vm.h"

int main () {

	unsigned char program[] = {
		PUSHI, 0, 0, 0, 1
	};

	pc = 0;
	sp = 0;
	opcount = 0;

	unsigned char currentop = program[sp];
	
	do {
		opcount++;
		currentop = program[sp];
	} while (currentop != HALT);

	return 0;
}
