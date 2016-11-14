//Scanner for the Oberon-S compiler, Arly Mathiasen and Eric Gelinas
#include <stdio.h>
#include <stdlib.h>

const int IDENTIFIER_MAX_LENGTH = 16;

FILE *input;//the input file
FILE *output;//the output file for tokens
const int lnBuffSize = 256;//size of line buffer
char lnBuff[256];//buffer to store read inputs
int BuffPos;//current position in the lnBuff
int lnNum;//current line number
char ch;//current character

typedef enum bool
{
false,
true
}bool;

typedef enum POS//part of speech
{
NOTOK,
//ADD OPS
PLUS,
MINUS,
OR,
//MUL OPS
MUL,
DIV,
MOD,
AND,
//RELATIONS
EQU,
NEQ,
LT,
LE,
GT,
GE,
//PREDEFINED WORDS
ABS,
BOOLEAN,
FALSE,
INTEGER,
ODD,
READ,
READLN,
TRUE,
WRITE,
WRITELN,
//CONTROL STRUCTURES
FOR,
WHILE,
REPEAT,
DO,
UNTIL,
END,
IF,
ELSIF,
ELSE,
THEN,
LOOP,
RETURN,
BY,
BEGIN,
MODULE,
PROCEDURE,
EXIT,
//DATA STRUCTURES
RECORD,
OF,
ARRAY,
//DECLS
VAR,
TYPE,
CONST,
//other
RSQUAREBRACKET,
LSQUAREBRACKET,
LPAREN,
RPAREN,
VERTBAR,
COMMA,
COLON,
SEMICOLON,
PERIOD,
IDENT,
INT,
ASSIGNMENT
}POS;






typedef struct Token 
{
	int spellingLength;
	char spelling[256];
	POS partOfSpeech;
}Token;//token struct
 
Token tok;
const Token emptyTok;



int idLength = 16;//identifier max length length
char spellingBuff[256];

void nextLine()
{
	int i;
	for(i = 0; i < lnBuffSize; i++)
	{
		lnBuff[i] = fgetc(input);
	}
	BuffPos = 0;
}

//function puts the next character from the input file into the token buffer after the most recent 
void nextCh()
{
	BuffPos++;
	if(BuffPos > lnBuffSize)
	{
		nextLine();
	}
	ch = lnBuff[BuffPos];
	puts("curren char ");
	char temp[2] = { ch,'\0'};
	puts(temp);
	puts("\n");
}

void addToSpelling()
{
	tok.spelling[tok.spellingLength] = ch;
	tok.spellingLength++;
}
void Error(int errNum)
{
	switch(errNum)
	{
		char str[15];
		case 0:
			puts("Illegal char found at line ");
			sprintf(str, "%d", lnNum);
			puts(" char ");
			sprintf(str,"%d",BuffPos);
			puts("\n");
			break;
		case 1:
			puts("Reached end of file while traversing comment\n");
			break;
		case 2:
			puts("Malformed hex number, expected H at line ");
			sprintf(str,"%d",lnNum);
			puts(" at char ");
			sprintf(str,"%d",BuffPos);
			break;
		case 3:
			puts("identifier exceeds max length 16");
			break;

	}
	exit(errNum);
}
void comment()
{
	int depth = 1;
	while(depth > 0)
	{
		nextCh();
		if(ch == '*')
		{
			nextCh();
			if(ch == ')')
			{
				depth--;
			}
		}
		else if(ch == '(')
		{
			nextCh();
			if(ch == '*')
			{
				depth++;
			}
		}
		else if(ch == EOF)
		{
			Error(1);
		}
	}
}

void numTok()
{
	bool hexFlag = false;
	while(((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F')))
	{
		if(ch >= 'A' && ch <= 'F')
		{
			hexFlag = true;		
		}
		addToSpelling();
		nextCh();	
	}
	if(hexFlag && ch == 'H')
	{
		addToSpelling();
		nextCh();	
	}
	else if(hexFlag && ch != 'H')
	{
		Error(2);
	}

}

void strTok()
{
	while(((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	{
		addToSpelling();
		nextCh();
		if(tok.spellingLength > IDENTIFIER_MAX_LENGTH)
		{
			Error(3);
		}
	}
	
	tok.spelling[tok.spellingLength] = '\0';
	char *ptr = &tok.spelling[0];

	if(strcmp(ptr,"OR") == 0)
	{
		tok.partOfSpeech = OR;
	}
	else if (strcmp(ptr,"DIV") == 0)
	{
		tok.partOfSpeech = DIV;
	}
	else if (strcmp(ptr,"MOD") == 0)
	{
		tok.partOfSpeech = MOD;
	}
	else if (strcmp(ptr,"ABS") == 0)
	{
		tok.partOfSpeech = ABS;
	}
	else if (strcmp(ptr,"BOOLEAN") == 0)
	{
		tok.partOfSpeech = BOOLEAN;
	}
	else if (strcmp(ptr,"FALSE") == 0)
	{
		tok.partOfSpeech = FALSE;
	}
	else if (strcmp(ptr,"INTEGER") == 0)
	{
		tok.partOfSpeech = INTEGER;
	}
	else if (strcmp(ptr,"ODD") == 0)
	{
		tok.partOfSpeech = ODD;
	}
	else if (strcmp(ptr,"READ") == 0)
	{
		tok.partOfSpeech = READ;
	}
	else if (strcmp(ptr,"READLN") == 0)
	{
		tok.partOfSpeech = READLN;
	}
	else if (strcmp(ptr,"TRUE") == 0)
	{
		tok.partOfSpeech = TRUE;
	}
	else if (strcmp(ptr,"WRITE") == 0)
	{
		tok.partOfSpeech = WRITE;
	}
	else if (strcmp(ptr,"WRITELN") == 0)
	{
		tok.partOfSpeech = WRITELN;
	}
	else if (strcmp(ptr,"FOR") == 0)
	{
		tok.partOfSpeech = FOR;
	}
	else if (strcmp(ptr,"WHILE") == 0)
	{
		tok.partOfSpeech = WHILE;
	}
	else if (strcmp(ptr,"REPEAT") == 0)
	{
		tok.partOfSpeech = REPEAT;
	}
	else if (strcmp(ptr,"DO") == 0)
	{
		tok.partOfSpeech = DO;
	}
	else if (strcmp(ptr,"UNTIL") == 0)
	{
		tok.partOfSpeech = UNTIL;
	}
	else if (strcmp(ptr,"END") == 0)
	{
		tok.partOfSpeech = END;
	}
	else if (strcmp(ptr,"IF") == 0)
	{
		tok.partOfSpeech = IF;
	}
	else if (strcmp(ptr,"ELSIF") == 0)
	{
		tok.partOfSpeech = ELSIF;
	}
	else if (strcmp(ptr,"ELSE") == 0)
	{
		tok.partOfSpeech = ELSE;
	}
	else if (strcmp(ptr,"THEN") == 0)
	{
		tok.partOfSpeech = THEN;
	}
	else if (strcmp(ptr,"LOOP") == 0)
	{
		tok.partOfSpeech = LOOP;
	}
	else if (strcmp(ptr,"RETURN") == 0)
	{
		tok.partOfSpeech = RETURN;
	}
	else if (strcmp(ptr,"BEGIN") == 0)
	{
		tok.partOfSpeech = BEGIN;
	}
	else if (strcmp(ptr,"MODULE") == 0)
	{
		tok.partOfSpeech = MODULE;
	}
	else if (strcmp(ptr,"PROCEDURE") == 0)
	{
		tok.partOfSpeech = PROCEDURE;
	}
	else if (strcmp(ptr,"EXIT") == 0)
	{
		tok.partOfSpeech = EXIT;
	}
	else if (strcmp(ptr,"RECORD") == 0)
	{
		tok.partOfSpeech = RECORD;
	}
	else if (strcmp(ptr,"OF") == 0)
	{
		tok.partOfSpeech = OF;
	}
	else if (strcmp(ptr,"ARRAY") == 0)
	{
		tok.partOfSpeech = ARRAY;
	}
	else if (strcmp(ptr,"VAR") == 0)
	{
		tok.partOfSpeech = VAR;
	}
	else if (strcmp(ptr,"TYPE") == 0)
	{
		tok.partOfSpeech = TYPE;
	}
	else if (strcmp(ptr,"CONST") == 0)
	{
		tok.partOfSpeech = CONST;
	}
	else if (strcmp(ptr,"INT") == 0)
	{
		tok.partOfSpeech = INT;
	}
	else
	{
		tok.partOfSpeech = IDENT;
	}	

}

void getToken(){
	puts("ingettoken()");
	tok = emptyTok;
	puts("beforedowhile");
	do
	{
		if(ch == 'o'){
			puts("o");
		}
		switch(ch)
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
				puts("incaseabc");
				addToSpelling();
				nextCh();
				strTok(); 
			break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				addToSpelling();
				nextCh();
				numTok();
				break;
			case '(':
				addToSpelling();
				nextCh();
				if(ch == '*')
				{
					nextCh();
					comment();
				}
				else
				{
					tok.partOfSpeech = LPAREN;	
				}
				break;
			case ')':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = RPAREN;
				break;
			case '+':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = PLUS;
				break;
	
			case '-':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = MINUS;
				break;
			case '=':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = EQU;
				break;
			case '#':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = NEQ;
				break;
			case '<':
				addToSpelling();
				nextCh();
	
				if(ch == '=')
				{
					addToSpelling();
					nextCh();
					tok.partOfSpeech = LE;
				}
				else
				{
					tok.partOfSpeech = LT;
				}
				break;
			case '>':
				addToSpelling();
				nextCh();
				if(ch == '=')
				{
					addToSpelling();
					nextCh();
					tok.partOfSpeech = GE;
				}
				else
				{
					tok.partOfSpeech = GT;
				}
				break;
			case '*':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = MUL;
				break;
			case '&':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = AND;
				break;
			case '[':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = LSQUAREBRACKET;
				break;
			case ']':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = RSQUAREBRACKET;
				break;
			case ':':
				addToSpelling();
				nextCh();
				if(ch == '=')
				{
					addToSpelling();
					nextCh();
					tok.partOfSpeech = ASSIGNMENT;
				}
				else
				{
					tok.partOfSpeech = COLON;
				}
				break;
			case ';':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = SEMICOLON;
				break;
			case ',':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = COMMA;
				break;
			case '.':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = PERIOD;
				break;
			case '|':
				addToSpelling();
				nextCh();
				tok.partOfSpeech = VERTBAR;
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
			case '\v':
			case '\f':
				break;
			default:
				puts("defaultcase");
				Error(0);
				break;
		}
	}
	while(tok.partOfSpeech == NOTOK);
	tok.spelling[tok.spellingLength] = '\0';
}



void parse()
{
	while(ch != EOF)
	{
		getToken();
		puts("gettokenend");
		puts(tok.spelling);
		puts("\n");
		char str[15];
		sprintf(str, "%d", tok.partOfSpeech);
	}

}



int main(int argc, char *argv[])
{
	if((argc > 3)||(argc == 0))
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
			BuffPos = 0;
			nextCh();
			puts("parsestart");
			parse();
		}
	}
}
