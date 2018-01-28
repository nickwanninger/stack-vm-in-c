CC:=gcc
CFLAGS:=-Wall -std=c99
LIBS:=-lm


all:
	@$(MAKE) vm
	@$(MAKE) asm


vm: src/vm.c src/vm.h
	$(CC) $(CFLAGS) $(LIBS) -o vm src/vm.c
	@echo "Built\n"

asm: src/assembler.c
	$(CC) $(CFLAGS) $(LIBS) -o asm src/assembler.c
	@echo "Built\n"

clean:
	rm vm
	rm asm


run:
	@$(MAKE) clean
	@$(MAKE) asm
	@$(MAKE) vm
	./asm test.asm
	./vm output