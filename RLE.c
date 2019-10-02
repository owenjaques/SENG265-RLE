#include <stdio.h>
#include <stdlib.h>

#define STRING_MAX 41
#define ZERO_ASCII 48
#define NINE_ASCII 57
#define A_ASCII 65
#define Z_ASCII 90

int main(int argc, char *argv[]){
	if(argc < 3 || argv[2][0] != 'e' && argv[2][0] != 'd'){
		printf("Invalid Usage, expected: RLE{filename}[e|d]\n");
		exit(4);
	}

	if(argv[1][0] == '\0'){
		printf("Error: No input file specified!\n");
		exit(1);
	}

	FILE * input_file = fopen(argv[1], "r");

	if(input_file == NULL){
		printf("Read error: file not found or cannot be read\n");
		exit(2);
	}

	char string[STRING_MAX];
	fgets(string, STRING_MAX, input_file);
	
	//checks string
	int white_space_flag = 0;
	int i = 0;
	while(string[i] != '\0'){
		//sees if the string characters are valid and if there has been no white space so far
		if(!(((string[i] >= ZERO_ASCII && string[i] <= NINE_ASCII) || (string[i] >= A_ASCII && string[i] <= Z_ASCII)) && !white_space_flag)){
			//checks to see if the potentially invalid char is white space
			if(string[i] == ' ' || string[i] == '\t' || string[i] == '\n' || string[i] == '\r' || string[i] == '\v'){
				white_space_flag = 1;
			}
			else {
				printf("Error: Invalid format\n");
				exit(3);
			}	
		}
		//if the white space flag has been set this will signify the string containing something other than white space after white space
		else {
			if(white_space_flag){
				printf("Error: Invalid format\n");
				exit(3);
			}
		}
		i++;
	}
	
	fclose(input_file);
		
	return 0;
}
