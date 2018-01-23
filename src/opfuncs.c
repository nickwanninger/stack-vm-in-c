#ifndef OPFUNCS
#define OPFUNCS
#include "opcodes.c"

void opNOOP(unsigned char *program, struct machineinfo *info) {
	unsigned char op = program[info->pc];
	printf("%d", op);
}

#endif /* OPFUNCS */