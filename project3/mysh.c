/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: mysh.c
 *	DESCRIPTION
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//return codes
#define EXIT_INVALID_ARG	-1

//global variables
static short verboseMode = 0; //verbose mode boolean
static unsigned long commandHistory = 10;
char USAGE_MESS[] = "usage: mysh [-v] [-h pos_num]"; //usage message

int main(int argc, char * argv[])
{
	if(argc > 1) //parse options if any given
	{
		if(strcmp("-v", argv[1]) == 0) //if verbose option given
			verboseMode = 1;
		else if(strcmp("-h", argv[1]) == 0) //if history option given
		{
			if(argc > 2) //convert to long and update if number given
			{
				long temp = strtol(argv[2], NULL, 10);
				if(temp > 0) //if positive num, update command history
					commandHistory = temp;
				else
				{
					fprintf(stderr, "%s\n", USAGE_MESS);
					return EXIT_INVALID_ARG;
				}
			}
			else //no number given
			{
				fprintf(stderr, "%s\n", USAGE_MESS);
				return EXIT_INVALID_ARG;
			}
		}
		else //if unrecognized argument
		{
			fprintf(stderr, "%s\n", USAGE_MESS);
			return EXIT_INVALID_ARG;
		}
	}

	printf("verboseMode is %d\n", verboseMode);
	printf("commandHistory is %ld\n", commandHistory);
	return EXIT_SUCCESS;
}

