## Spec

* All opcodes are a single byte

## Numeric References

* Use `#n` to reference the raw integer value (32 bit) `n`
* Use `*n` to reference the raw float value (32 bit) `n`
* Use `@n` to reference the value at memory location `n`
* Use `^n` to reference a single byte or a character `n`

## Opcodes:

```c
- NOOP (0x0): No operation, move onto the next instruction
- HALT (0x1): Halt the program and exit the process
- PUSH (0x2 - 0x5): Push a value to the top of the stack and move the stack pointer up by one.
  - 0x2: Push integer
  - 0x3: Push float
  - 0x4: Push value at memory location
  - 0x5: Push single byte
  `
- ADDI  (0xa): Adds integers
- ADDF  (0xb): Adds floats
- ADDC  (0xc): Adds characters

- MULI  (0xe): Multiplies Integers
- MULF  (0xf): Multiplies Floats
- MULC  (0x10): Multiplies characters

- SUBI  (0x11): Subtracts Integers
- SUBF  (0x12): Subtracts Floats
- SUBC  (0x13): Subtracts characters

- DIVI  (0x14): Divides Integers
- DIVF  (0x15): Divides Floats
- DIVC  (0x16): Divides characters

- MODI  (0x17): MOD operator for Integers
- MODF  (0x18): MOD operator for Floats
- MODC  (0x19): MOD operator for characters

- TOI   (0x1a): Converts the top of the stack to integer
- TOF   (0x1b): Converts the top of the stack to float
- TOC   (0x1c): Converts the top of the stack to character

- STOD  (0x1d): Pop the top value into some memory location
- STOA  (0x1e): Pop the top value into the accumulator

- LODD  (0x1f): Push the value from a memory location into the stack
- LODA  (0x20): Push the value from the accumulator into the stack
```
