#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: asm <file>");
		return 0;
	}



	while (1) {
		printf("\a");
	}
	FILE *output = fopen("out.vm", "wb");




	// fwrite(output);
	fclose(output);

	return 0;
}