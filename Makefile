CC:=gcc
CFLAGS:=-Wall -std=c99
LIBS:=-lm

# When just running "make", run "make vm" instead
default: vm

# compile the source into a binary file
vm: src/vm.c
	$(CC) $(CFLAGS) $(LIBS) -o bin/$@ src/$@.c

# Run the binary file without having to type it out
run:
	./bin/vm

clean:
	rm -rf bin/*
