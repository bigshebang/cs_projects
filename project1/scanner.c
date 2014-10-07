/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: scanner.c
 *	Source file for the scanner "module" of the program. Contains functions
 *	to scan and tokenize input.
 */

#include "classes.h"
#include "scanner.h"
#include <stdio.h>
#include <ctype.h>

/*	Function: classifier
 *	Purpose: Take in a C string assuming that it is or contains integer values,
 *	and convert it to an integer.
 *	It returns an int which is the converted value from the C string.
 */
int classifier(char c)
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
