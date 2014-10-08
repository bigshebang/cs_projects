/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: scanner.c
 *	Source file for the scanner "module" of the program. Contains functions
 *	to scan and tokenize input.
 */

#include "scanner.h"
#include <string.h>
#include <ctype.h>

/*	Function: getClass
 *	Purpose: Take in a C string assuming that it is or contains integer values,
 *	and convert it to an integer.
 *	It returns an int which is the converted value from the C string.
 */
int getClass(char c)
{
	if(c == '\t' || c == ' ')
		return CC_WS;
	else if(c == '\n')
		return CC_NEWLINE;
	else if(isalpha(c) || c == '_')
		return CC_ALPHA;
	else if(c == '0')
		return CC_DIG_0;
	else if (c > '0' && c < '8')
		return CC_DIG_1_7;
	else if (c == '8' || c == '9')
		return CC_DIG_8_9;
	else if (c == '/')
		return CC_CHAR_SLASH;
	else if (c == '*')
		return CC_CHAR_STAR;
	else if (c == '+' || c == '-' || c == '%')
		return CC_ARITH_OP;
	else if (c > 0 && c < 127)
		return CC_OTHER;
	else if (c == EOF)
		return CC_EOF;
	else
		return CC_ERROR;
}

/*	Function: classifier
 *	Purpose: Take in a C string assuming that it is or contains integer values,
 *	and convert it to an integer.
 *	It returns an int which is the converted value from the C string.
 */
int scan(indexStruct tempTm[][N_CC], const int *startState,
		 const int *acceptState)
{
	int curState = *startState;
	char buf[256]; //buffer to hold recognized tokens
	char c;

	printf("%d ", curState);

	while(1)
	{
		//get and classify next char
		c = getchar();
		int curClass = getClass(c);

		//append current char to buffer if tm says to save
		if(tempTm[curState][curClass].action == 's')
			buf[strlen(buf)] = c;

		//get and print next state
		curState = tempTm[curState][curClass].nextState;
		printf("%d ", curState);

		//if accepting state, print recognized or EOF
		if(curState == *acceptState)
		{
			int ret = (curClass == CC_EOF) ? 1 : 0; //return value

			if(strlen(buf) != 0)
				printf("recognized '%s'\n", buf);
			else if(ret) //if buffer is empty and current char is EOF
				printf("EOF\n");

			return ret;
		}
		//if error state, get next char until whitespace, then return negative
		else if(curState == ERROR_STATE)
		{
			while(getClass(getchar()) != CC_WS);
			return -1;
		}
	}
}
