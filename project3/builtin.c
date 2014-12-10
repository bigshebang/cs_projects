/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.c
 *	Implementation of builtin shell functions.
 */

#include <assert.h>

#include "builtin.h"

#define EXIT_ARG_FAILURE	-1

/*  Function: initHistory
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 *  Purpose: Initialize a command history array to have all null pointers.
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
	char *temp = (char*)realloc(commands[curIndex], strlen(command) + 1);
	if(!temp)
		return EXIT_FAILURE;

	commands[curIndex] = temp;
	strcpy(commands[curIndex], command);
	return EXIT_SUCCESS;
}

/*  Function: getCommand
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 				current - current command index
 				command - command number to get
 *  Purpose: Print the command history.
 *  Returns: String containing the desired command if found successfully, NULL
 	if the command number was out of bounds.
 */
char *getCommand(char **commands, unsigned long size, unsigned long current,
				 unsigned long command)
{
	if(command >= current || command <= 0) //if invalid number
		return NULL;

	//need this check once current command index exceeds max history size
	if(current > size && command < (current - size))
		return NULL;

	return commands[(command - 1) % size]; //return requested command
}

/*  Function: printHistory
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 				current - current command index
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
		printf("\t%lu: %s\n", i, commands[(i-1) % size]);
}

/*  Function: destroyHistory
 *  Parameters: commands - array of strings containing the command history
 				size - size of the given array
 *  Purpose: Free the command history.
 *  Returns: Nothing.
 */
void destroyHistory(char **commands, unsigned long size)
{
	for(unsigned long i = 0; i < size; i++)
		free(commands[i]);
}

/*  Function: split
 *  Parameters: str - string to parse
 				dst - pointer to destination array of new, parsed args
 *  Purpose: Split the given string based on the given delimeter and reate an
 	array of strings.
 *  Returns: Size of the strings array dst when done parsing. -1 if failure to
	allocate memory
 */
int split(char *str, char ***dst)
{
	//get number of different args
	int size = countArgs(str) + 1;

	//malloc enough room to hold all args. make sure not NULL
	*dst = (char**)malloc(sizeof(char*) * size);
	if(!*dst)
		return EXIT_ARG_FAILURE;

	//vars needed for while loop
	int index = 0;
	int counter = 0;
	int last;

	while(counter < size)
	{
		//if first char is a quote, get index of next quote found
		if(str[index] == '"' || str[index] == '\'')
		{
			index++;
			index += strcspn((str + index), "\"'");
			last++;
		}
		else //if not, get index of next space
		{
			index += charAt((str + index), ' ');

			//if current index is a space, move up 1 and loop again
			if(index == last)
			{
				index++;
				last++;
				continue;
			}

			if(index < last) //if no spaces left, copy rest of the string over
				index = strlen(str) + 1;
		}

		//malloc space for new string, make sure not NULL
		int diff = index++ - last;
		(*dst)[counter] = (char*)malloc(diff + 1);
		if(!(*dst)[counter])
		{
			destroyArgs(*dst, size);
			return EXIT_ARG_FAILURE;
		}

		//copy string over, and manually add trailing NUL byte
		strncpy((*dst)[counter], (str + last), diff);
		(*dst)[counter++][diff] = '\0';

		last = index; //save last index
	}

	return size;
}

/*  Function: charAt
 *  Parameters: str - string to count in
 				c - char to find
 *  Purpose: Find the index of the first occurence of the given character c.
 *	Returns: Index of first char found, -1 if not found.
 */
int charAt(const char *str, const char c)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		if(str[i] == c)
			return (int)i; //should be positive, but cast as int
	}
	return -1;
}

/*  Function: countArgs
 *  Parameters: str - string to count in
 *  Purpose: Count how many times a space is in the given str, but not
 	counting the ones inside of single or double quotes. Done somewhat lazily
 	because there will never be nested quotes, so the function doesn't have to
 	account for a single quote inside a double and vice versa.
 *	Returns: Number of times a space is in the str excluding those in quotes.
 */
int countArgs(const char *str)
{
	short toggle = 1;
	short last = 1;
	int count = 0;
	printf("str is %s\n", str);
	for(size_t i = 0; i < strlen(str); i++)
	{
		if(last < 0 && str[i] != ' ')
			last *= -1;

		//if not inside quoted text and not a consecutive space
		if(str[i] == ' ' && toggle > 0 && last > 0)
		{
			count++;
			last *= -1;
		}
		else if(str[i] == '\'' || str[i] == '"') //if inside quoted text
			toggle *= -1;
	}

	return count;
}

/*  Function: destroyArgs
 *  Parameters: str - array of strings to be destroyed
 				size - number of strings in str array
 *  Purpose: Free all memory associated with str array.
 *	Returns: Nothing.
 */
void destroyArgs(char **str, int size)
{
	if(str) //free each string then the array itself if not NULL
	{
		for(int i = 0; i < size; i++)
			free(str[i]);

		free(str);
	}
}

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
