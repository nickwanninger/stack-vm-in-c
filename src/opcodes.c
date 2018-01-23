#ifndef OPCODES
#define OPCODES

#define NOOP   0x0 // None                                             - 1 byte
#define HALT   0x1 // Halt the program and kill the process            - 1 byte
#define POP    0x2 // Pop the top of the stack and delete it           - 1 byte
#define PUSHPC 0x3 // Push the current prog counter to the stack       - 1 byte
#define POPPC  0x4 // Pop into the program counter                     - 1 byte
#define PUSHI  0x5 // Push an integer to the top of the stack          - 5 bytes
#define ADDI   0x6 // Add the next and the top and push to top (int)   - 1 byte
#define SUBI   0x7 // Subtract the next and top and push to top (int)  - 1 byte
#define MULI   0x8 // Multiply the next and top and push to top (int)  - 1 byte
#define PRINT  0x9 // Pop the top of the stack and print it to stdout  - 1 byte

#include "opfuncs.c"

static char opcodes[] = {NOOP, HALT, POP, PUSHPC, POPPC, PUSHI, ADDI, SUBI, MULI, PRINT};
static char oplengths[] = {1, 1, 1, 1, 1, 5, 1, 1, 1, 1};

#endif /* OPCODES */