/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: matrix.c
 *	File containing source code of functions of the matrix "module". These are
 *	functions to help create and print transition matrices.
 */

#include "matrix.h"
#include <string.h>
#include <ctype.h>

/*	Function: strToInt
 *	Parameters: str - array of characters that needs to be converted.
 *	Purpose: Take in a C string assuming that it is or contains integer values,
 *	and convert it to an integer.
 *	Returns: An int which is the converted value from the C string.
 */
int strToInt(char str[])
{
	int ret = 0;
	    for(unsigned int i = 0; i < strlen(str); i++)
	    {
	        if(isdigit(str[i]))
	            ret = ret * 10 + str[i] - '0';
	        else
	            break;
	    }
	return ret;
}

/*	Function: initMatrix
 *	Parameters: fp - file pointer to read from.
 *				tempTm - 2d array of indexStructs
 *				numStates - number of states in the 2d array
 *	Purpose: Take a transition matrix file and create a 2d array containing
 *	that information.
 *	Returns: Nothing.
 */
void initMatrix(FILE *fp, indexStruct tempTm[][N_CC], int numStates)
{
	for(int i = 0; i < numStates; i++) //initialize to default values
	{
		for(int j = 0; j < N_CC; j++)
		{
			tempTm[i][j].nextState = 99;
			tempTm[i][j].action = 'd';
		}
	}

	char *ptr, buf[256]; //pointer from fgets, buffer for fgets

	//read and parse the rest of the lines in the file
	while((ptr = fgets(buf, 256, fp)) != NULL)
	{
		char *temp;
		temp = strtok(buf, " "); //split by spaces

		int stateNum = 0;
		stateNum = strToInt(temp); //get state number of the line

		temp = strtok(NULL, " ");
		while(temp != NULL) //split by spaces until no more spaces
		{
			int col = 0, next = 0;
			char c = ' ';

			//get next state and action and add to the tm
			sscanf(temp, "%d/%d%c ", &col, &next, &c);
			tempTm[stateNum][col].nextState = next;
			tempTm[stateNum][col].action = c;

			temp = strtok(NULL, " ");
		}
	}

}

/*	Function: printMatrix
 *	Parameters: tempTm - 2d array of indexStructs
 *				numStates - number of states of the 2d array given
 *	Purpose: Print a given 2d array of indexStructs.
 *	Returns: Nothing.
 */
void printMatrix(indexStruct tempTm[][N_CC], int numStates)
{
	for(int i = 0; i < numStates; i++)
	{
		printf("\n%2d", i);
		for(int j = 0; j < N_CC; j++)
			printf("  %2d%c", tempTm[i][j].nextState, tempTm[i][j].action);
	}

	putchar('\n');
}
