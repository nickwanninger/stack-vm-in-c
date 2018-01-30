#ifndef OPCODES
#define OPCODES

#define NOOP   0x0 // None                                                  - 1 byte
#define HALT   0x1 // HALT the program and kill the process                 - 1 byte
#define EMIT   0x2 // Pop and PRINT the value at the top of the stack       - 1 byte
#define PI16   0x3 // PUSH and integer constant to the top of the stack     - 3 bytes
#define ADDI   0x4 // POP the top vals, add them, and push their sum        - 1 byte
#define JUMP   0x5 // JUMP the PC to the first argument                     - 5 bytes

#endif /* OPCODES */