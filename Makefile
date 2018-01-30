CC:=gcc
CFLAGS:=-Wall -std=c99
LIBS:=-lm


all:
	@$(MAKE) vm
	@$(MAKE) asm


vm: src/vm/*
	$(CC) $(CFLAGS) $(LIBS) -o vm src/vm/main.c
	@echo "Built\n"

asm: src/assembler.c
	$(CC) $(CFLAGS) $(LIBS) -o asm src/assembler/assembler.c
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