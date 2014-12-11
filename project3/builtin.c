/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.c
 *	Implementation of builtin shell functions.
 */

#include "builtin.h"

/*  Function: echo
 *  Parameters: args - string array of arguments to print
 				size - size of given string array
 				start - what index to start printing from
 *  Purpose: Print the given arguments to stdout.
 *  Returns: Nothing.
 */
void echo(char **args, size_t size, size_t start)
{
	if(size == start) //if no args to print, print a newline and exit
	{
		putchar('\n');
		return;
	}

	size_t i;
	for(i = start; i < (size - 1); i++)
		printf("%s ", args[i]);

	printf("%s\n", args[i]);
}

/*  Function: help
 *  Parameters: usageMess - A usage message to print out.
 *  Purpose: Print help containing internal commands and usage for this shell.
 *  Returns: Nothing.
 */
void help(const char *usageMess)
{
	//print header and usage message
	puts("mysh help menu");
	printf("%s\n", usageMess);

	//info about builtins
	puts("\necho [args]");
	puts("\tThis command will print any arguments the user gives it. If no");
	puts("\targuments are given, just a new line is printed.");

	puts("\nhelp");
	puts("\tPrint this history.");

	puts("\nhistory");
	puts("\tThe history command will print a numbered list of the previously");
	puts("\tentered commands. By default mysh will store the 10 previous");
	puts("\tcommands, but this number can be changed using the -h option.");
	puts("\tTo run any of these commands again, just type !x, where x is");
	puts("\tthe number of the command you want. This number must be within");
	puts("\tthe valid range of current commands being stored to be");
	puts("\tsuccessful.");

	puts("\nquit");
	puts("\tThis will gracefully exit the shell.");

	puts("\nverbose [on|off]");
	puts("\tThis command allows the user to enable or disable verbose mode.");
}

/*  Function: verbose
 *  Parameters: str - the argument given. Should be on or off.
 *  Purpose: Change the verbose flag according to given argument.
 *  Returns: Nothing.
 */
void verbose(char *str)
{
	if(!strcmp(str, "on"))
		verboseMode = 1;
	else if(!strcmp(str, "off"))
		verboseMode = 0;
	else
		fprintf(stderr, "Usage: verbose [on|off]\n");
}
