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
	//variables
	static unsigned long commandHistory = 10;
	static const char USAGE_MESS[] = "usage: mysh [-v] [-h pos_num]";

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
	static unsigned long curCommand = 1; //current command index
	char *prevCommands[commandHistory]; //command history array
	static const char PROMPT[] = "mysh[%d]> ";

	//path to search for binaries/commands in
	static const char path[] = 	"/usr/local/dcs/jdk/bin:/usr/local/dcs/bin:"
								"/usr/local/sbin:/usr/local/bin:/usr/sbin:"
								"/usr/bin:/sbin:/bin:/usr/games:";

	//variables needed for getting input
	char *inputBuf = NULL;
	size_t lineLen = 0;
	int ret = -1;

	printf("%s", PROMPT, curCommand); //print prompt
	//get line while we have actually read bytes
	while((ret = getline(&inputBuf, &lineLen, stdin)) > 0)
	{
		if(ret == 1) //if only a new line given, prompt and start again
		{
			printf("%s", PROMPT, curCommand);
			continue;
		}

		inputBuf[ret - 1] = '\0'; //get rid of newline
		if(strcmp(inputBuf, "quit"))
			break;

		printf("you entered '%s'", inputBuf);

		printf("%s", PROMPT, curCommand);
	}

	return EXIT_SUCCESS;
}
