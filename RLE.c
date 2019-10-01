#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, int *argv[]){
	if(argc < 3 || strcmp(argv[2], "e") != 0 && strcmp(argv[2], "d") != 0){
		printf("Invalid Usage, expected: RLE{filename}[e|d]\n");
		exit(4);
	}
	//should also check if there is no input file specified but wont the first error a few lines up be fired first??
	FILE * input_file = fopen(argv[1], "r");

	if(input_file == NULL){
		printf("Read error: file not found or cannot be read\n");
		exit(2);
	}

	
	fclose(input_file);
		
	return 0;
}
