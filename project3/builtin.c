/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.c
 *	Implementation of builtin shell functions.
 */

#include <assert.h>

#include "builtin.h"

/*  Function: initHistory
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 *  Purpose: Initialize a command history array to have all null pointers
 *  Returns: Nothing.
 */
void initHistory(char **commands, unsigned long size)
{
	for(unsigned long i = 0; i < size; i++)
		commands[i] = NULL;
}

/*  Function: addCommand
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 				command - string containing the last command issued
 				current - current command index
 *  Purpose: Add given command to the command history list.
 *  Returns: 0 if successful, nonzero if failure.
 */
int addCommand(char **commands, unsigned long size, const char *command,
			   unsigned long current)
{
	if(!commands)
		return EXIT_FAILURE;

	unsigned long curIndex = (current - 1) % size; //current index in the array

	//realloc a temp pointer, have array point there, copy string over
	char *temp = (char*)realloc(commands[curIndex], sizeof(command));
	if(!temp)
		return EXIT_FAILURE;

	commands[curIndex] = temp;
	strcpy(commands[curIndex], command);
	return EXIT_SUCCESS;
}

/*  Function: printHistory
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 *  Purpose: Print the command history.
 *  Returns: Nothing.
 */
void printHistory(char **commands, unsigned long size, unsigned long current)
{
	assert(commands != NULL);

	//get relative command number, start at 1 if not more than given size
	unsigned long i = 1;
	if(current > size)
		i = current - size + 1;

	//(i-1) % size will get the proper index, because the command history is a
	//circular array/buffer
	for(; i <= current; i++)
		printf("\t%zu: %s\n", i, commands[(i-1) % size]);
}

/*  Function: destroyHistory
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 *  Purpose: Print the command history.
 *  Returns: Nothing.
 */
void destroyHistory(char **commands, unsigned long size)
{
	for(unsigned long i = 0; i < size; i++)
		free(commands[i]);
}
