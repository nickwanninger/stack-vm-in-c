CC:=gcc
CFLAGS:=-Wall -std=c99 -O2
LIBS:=-lm

vm: src/vm/vm.c
	$(CC) $(CFLAGS) $(LIBS) -o vm src/vm/vm.c
	@echo "Built\n"


asm: src/asm/asm.c
	$(CC) $(CFLAGS) $(LIBS) -o asm src/asm/asm.c
	@echo "Built\n"


# Run the binary file without having to type it out
run:
	@./bin/vm

clean:
	rm vm
