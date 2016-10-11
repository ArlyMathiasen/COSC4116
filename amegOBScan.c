//Scanner for the Oberon-S compiler, Arly Mathiasen and Eric Gelinas
#include <stdio.h>


const int INPUT_BUFFER_LENGTH = 256;
const int IDENTIFIER_MAX_LENGTH = 16;


FILE *input;//the input file
FILE *output;//the output file for tokens
char tokenBuffer [256];//buffer to store read inputs
int BuffPos;//current position in the tokenBuffer



int main(int argc, char *argv[])
{
	if((argc > 2)||(argc == 0))
	{
		printf("Usage: %s source [target]\n", argv[0]);
	}
	else
	{
		//open the input file to be read
		input = fopen( argv[1], "r");

		//determine if we need to use the default value for output file
		char *outFileName;
		if(argc = 2)
		{
			outFileName = argv[2];
		}
		else
		{
			outFileName = "a.out";
		}

		//open the outputfile for writing tokens to
		output = fopen(outFileName, "w");
		if((input == 0)||(output == 0))
		{
			puts("Failed to open files for reading/writing.\nCheck file paths, and folder permisisions, then try again.");
		}
		else
		{
			
		}
	}
}
