/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: parse.c
 *	Implementation of argument parsing. Not command line arguments, but input
 	that needs to be parsed into separate arguments.
 */

#include "parse.h"

#define EXIT_ARG_FAILURE	-1

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
	*dst = (char**)malloc(sizeof(char*) * (size + 1));
	if(!*dst)
		return EXIT_ARG_FAILURE;

	//vars needed for while loop
	int index = 0;
	int counter = 0;
	int last = 0;

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

	(*dst)[counter] = (char*)0; //terminate array with null pointer

	return ++size;
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
