/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: mysh.c
 *	Main function for my shell (MYSH).
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "builtin.h"

//return codes
#define EXIT_INVALID_ARG	-1

//global variables
static short verboseMode = 0;


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

	//initialize all necessary variables
	static unsigned long commandHistory = 10;
	static unsigned long curCommand = 1;
	static const char PROMPT[] = "mysh[%s]> ";
	static const char USAGE_MESS[] = "usage: mysh [-v] [-h pos_num]";

	//path to search for binaries/commands in
	static const char path[] = 	"/usr/local/dcs/jdk/bin:/usr/local/dcs/bin:"
								"/usr/local/sbin:/usr/local/bin:/usr/sbin:"
								"/usr/bin:/sbin:/bin:/usr/games:";

	char *prevCommands[commandHistory]; //command history array

	char *inputBuf = NULL;

	//get line while we have actually read bytes
	while((size_t ret = getline(&inputBuf, 0, stdin)) >= 0)
	{
		if(strcmp(inputBuf, EOF) == 0 || strcmp(inputBuf, "quit"))
			break;

		printf("you entered '%s'", inputBuf);
	}

	return EXIT_SUCCESS;
}
