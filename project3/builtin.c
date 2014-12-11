/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.c
 *	Implementation of builtin shell functions.
 */

#include "builtin.h"

/*  Function: echo
 *  Parameters: args - string array of arguments to print
 *  Purpose: Print the given arguments to stdout.
 *  Returns: Nothing.
 */
void echo(char **args, size_t size, size_t start)
{
	size_t i;
	for(i = start; i < (size - 1); i++)
		printf("%s ", args[i]);

	printf("%s\n", args[i]);	
}

/*  Function: help
 *  Parameters: Nothing.
 *  Purpose: Print help containing internal commands for this shell.
 *  Returns: Nothing.
 */
void help()
{
	//code
}

/*  Function: verbose
 *  Parameters: Not sure yet. probably verbose flag?
 *  Purpose: Handle verbose command, toggle verbose flag? Do all output stuffz.
 *  Returns: Not sure yet, probz void.
 */
void verbose()
{
	//code
}
