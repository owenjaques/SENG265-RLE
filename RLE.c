#include <stdio.h>
#include <stdlib.h>

#define STRING_MAX 41
#define ZERO_ASCII 48
#define NINE_ASCII 57
#define A_ASCII 65
#define Z_ASCII 90

/*
 *purpose: check if c is an upper case letter
 *param: (char) c
 *returns: 1 if uppercase letter 0 otherwise
 */
int isUppercase(char c){
	return (c >= A_ASCII && c <= Z_ASCII);
}

/*
 *purpose: check if c is a number char 
 *param: (char) c
 *returns: 1 if a number 0 otherwise
 */
int isNumber(char c){
	return (c >= ZERO_ASCII && c <= NINE_ASCII);
}

/*
 *purpose: check if c is white space
 *param: (char) c
 *returns: 1 if white space 0 otherwise
 */
int isWhiteSpace(char c){
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

void encode(char input[STRING_MAX]){
	int i = 0;//an index for the input string
	int j = 0;//an index for the output string
	int num_letters = 1;
	char output[STRING_MAX];
	while(input[i] != '\0' && !isWhiteSpace(input[i])){
		if(isNumber(input[i])){
			printf("Error: String could not be encoded\n");
			exit(5);
		}
		if(input[i] == input[i+1])
			num_letters++;
		else {
			output[j] = input[i];
			output[j+1] = num_letters + 48;//increments by 48 to transform from int to char (ASCII)
			num_letters = 1;
			j += 2;
		}	
		i++;
	}
	output[j] = '\0';
	printf("%s\n", output);
	exit(0);
}

void decode(char input[STRING_MAX]){
	int i = 0;//an index for the input string
	int j = 0;//an index for the output string
	int number;
	char letter;
	char output[STRING_MAX];
	while(input[i] != '\0' && !isWhiteSpace(input[i])){
		letter = input[i];
		number = input[i+1];//actually still the char code for a number
		if(isNumber(letter) || isUppercase(number)){
			printf("Error: String could not be encoded\n");
			exit(5);
		}
		number -= 48;//makes it the actual number
		int k;
		for(k = 0; k < number; k++){
			output[j] = letter;
			j++;
		}
		i += 2;
	}
	output[j] = '\0';
	printf("%s\n", output);
	exit(0);
}

int main(int argc, char *argv[]){
	if(argc < 3 || argv[2][0] != 'e' && argv[2][0] != 'd'){
		printf("Invalid Usage, expected: RLE{filename}[e|d]\n");
		exit(4);
	}

	if(argv[1][0] == '\0' || isWhiteSpace(argv[1][0])){
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
		if(!((isNumber(string[i]) || isUppercase(string[i])) && !white_space_flag)){
			//checks to see if the potentially invalid char is white space
			if(isWhiteSpace(string[i])){
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

	//sees what mode it is in
	if(argv[2][0] == 'e')
		encode(string);
	else
		decode(string); 
		
	return 0;
}
