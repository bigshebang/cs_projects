/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: tokenize.c
 *	File containing main method for reading in a transition matrix, and
 *	outputting text based upon the input text and the given transition matrix.
 */

#include "classes.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//define exit statuses used in program
#define EXIT_SUCCESS	0
#define MISSING_ARG		-1
#define BAD_FILE		-2

//prototypes
int strToInt(char[]);

struct indexStruct //struct to contain values for each spot in the matrix
{
	int nextState; //next state to go to
	char action; //char representing action to take, (s)ave or (d)elete
};

/*	Function: main
 *	Purpose: Take a command line argument expected to be a specifically
 *	formatted transition matrix and use that to scan and tokenize data given
 *	from stdin. This will print the transition matrix received and then
 *	the results from parsing the input using the given transition matrix.
 *	The exit status of the program, which would be 0 for success and non-zero
 *	for failure.
 */
int main(int argc, char *argv[])
{
	if(argc != 2) //if no args given, print error and exit
	{
		fprintf(stderr, "usage: %s tm_file\n", argv[0]);
		return MISSING_ARG;
	}

	//open file given as command line arg and read it
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp == NULL) //if file couldn't open correctly, print error and exit
	{
		perror(argv[1]);
		return BAD_FILE;
	}

	//declare state vars and read them in from the file
	int numStates = 0, startState = 0, acceptState = 0;
	fscanf(fp, "%*s %d %*s %d %*s %d ", &numStates, &startState, &acceptState);

	struct indexStruct tm[numStates][N_CC]; //transition matrix
	char *ptr, buf[256]; //pointer from fgets, buffer for fgets

	for(int i = 0; i < numStates; i++) //initialize to default values
	{
		for(int j = 0; j < N_CC; j++)
		{
			tm[i][j].nextState = 99;
			tm[i][j].action = 'd';
		}
	}

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
			tm[stateNum][col].nextState = next;
			tm[stateNum][col].action = c;

			temp = strtok(NULL, " ");
		}
	}

	fclose(fp);

	putchar(' '); //add extra space at beginning for proper spacing
	for(int i = 0; i < N_CC; i++) //print heading
	{
		printf("   %2d", i);
	}
	for(int i = 0; i < numStates; i++) //print values in tm
	{
		printf("\n%2d", i);
		for(int j = 0; j < N_CC; j++)
			printf("  %2d%c", tm[i][j].nextState, tm[i][j].action);
	}
	
	putchar('\n');
	return EXIT_SUCCESS;
}

/*	Function: str_to_int
 *	Purpose: Take in a C string assuming that it is or contains integer values,
 *	and convert it to an integer.
 *	It returns an int which is the converted value from the C string.
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

