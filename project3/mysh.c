/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: mysh.c
 *	Main function for my shell (MYSH).
 */

#define _GNU_SOURCE

#include "builtin.h"
#include "external.h"

//return codes
#define EXIT_INVALID_ARG	-1

int main(int argc, char * argv[])
{
	//variables
	static unsigned long commHistSize = 10;
	static const char USAGE_MESS[] = "Usage: mysh [-v] [-h pos_num]";

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

		//handle if ! was given, get given command history index
		if(inputBuf[0] == '!')
		{
			//get the num after the !
			unsigned long tempNum = 0;
			ret = sscanf(inputBuf, "!%lu", &tempNum);
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
					inputBuf = temp;
					strcpy(inputBuf, tempBuf);
				}
			}
		}
		else //remove trailing newline if no ! given
			inputBuf[ret - 1] = '\0';

		if(!strncmp(inputBuf, "quit", 4))
		{
			free(inputBuf);
			break;
		}

		printf("'%s'\n", inputBuf);

		//add command to command history
		addCommand(prevCommands, commHistSize, inputBuf, curCommand);

		if(!strcmp(inputBuf, "history"))
			printHistory(prevCommands, commHistSize, curCommand);

		//tokenize input and get it in args
		char **args = NULL;
		int argSize = split(inputBuf, &args);

		if(argSize < 0) //if error found parsing args.
		{
			perror("mysh");
			return EXIT_FAILURE;
		}

		//we don't need inputBuf any more so free it
		free(inputBuf);
		inputBuf = NULL;

		//process commands and do what they ask
		if(!strcmp(args[0], "verbose")) //turn verbose on/off
		{
			if(argSize > 1)
				verbose(args[1]);
			else
				verbose("");
		}
		else if(!strcmp(args[0], "help")) //print help for mysh
			help(USAGE_MESS);
		else if(!strcmp(args[0], "echo")) //echo their given args
			echo(args, argSize - 1, 1);
		else //external command, fork dat
		{
			ret = run(args);
		}

		//free some memory and print prompt before starting again
		destroyArgs(args, argSize);
		printf("mysh[%lu]> ", ++curCommand);
	}

	//memory management
	destroyHistory(prevCommands, commHistSize);

	//if CTRL-D pressed/EOF, print newline for formatting
	if(ret < 1)
		putchar('\n');

	return EXIT_SUCCESS;
}
