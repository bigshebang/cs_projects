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
 *	Paremeters: c - a character to classify
 *	Purpose: Classify a character based on the character classes in classes.h
 *	and return the integer value for that class.
 *	Returns: An int representing the character class of the given char.
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

/*	Function: scan
 *	Parameters: tempTm - 2d array of indexStructs, the tm
 *				startState - const int pointer to the starting state
 *				acceptState - const int pointer to the accepting state
 *	Purpose: Scan or tokenize data from stdin based upon the tm passed as the
 *	parameter. Start at the given starting state until reaching the accepting
 *	state.
 *	Returns: An int which indicates the result of the scan. 0 means we reached
 *	the accepting state but did not get an EOF so there is more input to be
 *	processed. A positive number means an EOF was found. A negative number
 *	means that the given input was rejected and not recognized according to the
 *	given tm. More specifically than that, a 1 means that EOF was found and
 *	we ended in the accepting state, whereas a 2 means that EOF was found but
 *	we ended in the error state. Also, a -1 indicates that the input was
 *	rejected, but we did not reach EOF.
 */
int scan(indexStruct tempTm[][N_CC], const int *startState,
		 const int *acceptState)
{
	int curState = *startState;
	char buf[256] = ""; //buffer to hold recognized tokens
	char c;

	printf("%d ", curState);

	while(1)
	{
		//get and classify next char
		c = getchar();
		int curClass = getClass(c);

		//append current char to buffer if tm says to save
		if(tempTm[curState][curClass].action == 's')
			strncat(buf, &c, sizeof(c));

		//get and print next state
		curState = tempTm[curState][curClass].nextState;
		printf("%d ", curState);

		//if accepting state, print recognized or EOF
		if(curState == *acceptState)
		{
			int ret = (curClass == CC_EOF) ? EOF_ACCEPT : ACCEPT_STATE;

			if(strlen(buf) != 0)
			{
				printf("recognized '%s'\n", buf);
			}
			else if(ret) //if buffer is empty and current char is EOF
				printf("EOF\n");

			return ret;
		}
		//if error state, get next char until whitespace, then return negative
		else if(curState == ERROR_STATE)
		{
			while(getClass((c = getchar())) > CC_NEWLINE)
			{
				if(c == EOF) //if EOF, return different num (2)
					return ERROR_STATE_EOF;
			}
			return ERROR_STATE_RET;
		}
	}
}
