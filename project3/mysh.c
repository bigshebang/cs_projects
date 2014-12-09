/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: mysh.c
 *	Main function for my shell (MYSH).
 */

#define _GNU_SOURCE

#include "builtin.h"

//return codes
#define EXIT_INVALID_ARG	-1

//global variables
static short verboseMode = 0;

int main(int argc, char * argv[])
{
	//variables
	static unsigned long commHistSize = 10;
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
					commHistSize = temp;
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
	char *prevCommands[commHistSize]; //command history array
	initHistory(prevCommands, commHistSize); //initialize prevCommands array
	// static const char PROMPT[] = "mysh[%d]> ";

	//path to search for binaries/commands in
	// static const char path[] = 	"/usr/local/dcs/jdk/bin:/usr/local/dcs/bin:"
	// 							"/usr/local/sbin:/usr/local/bin:/usr/sbin:"
	// 							"/usr/bin:/sbin:/bin:/usr/games:";

	//variables needed for getting input
	char *inputBuf = NULL;
	size_t lineLen = 0;
	int ret = -1;

	printf("mysh[%lu]> ", curCommand); //print prompt
	//get line, process while we have actually read bytes
	while((ret = getline(&inputBuf, &lineLen, stdin)) > 0)
	{
		if(ret == 1) //if only a new line given, prompt and start again
		{
			printf("mysh[%lu]> ", curCommand);
			continue;
		}

		short resetBuf = 0;
		//handle if ! was given, get given command history index
		if(inputBuf[0] == '!')
		{
			//get the num after the !
			unsigned long tempNum = 0;
			int ret = sscanf(inputBuf, "!%lu", &tempNum);
			char *tempBuf = NULL;

			if(ret > 0) //if no number found there was an error. keep it NULL
				tempBuf = getCommand(prevCommands, commHistSize, curCommand,
									 tempNum);

			if(!tempBuf) //if null, there was an error
			{
				fprintf(stderr, "Invalid command index number given.\n");
				printf("mysh[%lu]> ", curCommand);
				continue;
			}
			else //if not null, realloc and copy string to inputBuf
			{
				char *temp = (char*)realloc(inputBuf, strlen(tempBuf) + 1);
				if(temp)
				{
					resetBuf = 1;
					inputBuf = temp;
					strcpy(inputBuf, tempBuf);
				}
			}
		}
		else //remove trailing newline if no ! given
			inputBuf[ret - 1] = '\0';

		if(!strcmp(inputBuf, "quit"))
			break;

		//add command to history
		addCommand(prevCommands, commHistSize, inputBuf, curCommand);

		printf("'%s'\n", inputBuf);

		if(!strcmp(inputBuf, "history"))
			printHistory(prevCommands, commHistSize, curCommand);

		//split input by spaces - grab code from project 1 using the tok function or whatever
		char ** args = NULL;
		size_t argSize = split(inputBuf, args);

		if(!strcmp(args[1], "echo"))
			echo(args[1], argSize - 1);
		else if(true)
			puts("temporary");

		//free the input buf here to prevent errors in getline if we got a !
		if(resetBuf)
		{
			free(inputBuf);
			inputBuf = NULL;
		}

		printf("mysh[%lu]> ", ++curCommand);
	}

	//memory management
	free(inputBuf);
	destroyHistory(prevCommands, commHistSize);

	//if CTRL-D pressed/EOF, print newline for formatting
	if(ret < 1)
		putchar('\n');

	return EXIT_SUCCESS;
}
