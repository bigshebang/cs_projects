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
 *  Purpose: Print the command history.
 *  Returns: Nothing.
 */
void destroyHistory(char **commands, unsigned long size)
{
	for(unsigned long i = 0; i < size; i++)
		free(commands[i]);
}

/*  Function: split
 *  Parameters: str - string to parse
 				dst - destination array of new, parsed args
 *  Purpose: Split the given string based on the given delimeter and reate an
 	array of strings.
 *  Returns: Size of the strings array dst when done parsing.
 */
int split(char *str, char **dst)
{
	//get number of different args, then allocate space for that many strings
	int size = countSpaces(str);
	dst = (char**)malloc(size);
	// char *copy = str;

	//create copy of given string
	// char *copy = (char*)malloc(strlen(str) + 1);
	// strcpy(copy, str);
	// char *backup = copy;

	//strtok first to get command, then handle args in for loop
	// char *temp = strtok(str, " ");
	int index = 0;
	int counter = 0;
	// char *temp = str;
	// size_t tempSize = 0;
	int last;
	// char delim[3] = " "; //size of three so it can hold "\"'" or a space + NUL
	int quotes, space;
	short needQuote = -1;

	while(counter < size) //loop while we can still tokenize
	{
		last = index; //save last index

		//if first char is a quote, get index of next quote found
		if(str[index] == '"' || str[index] == "\'")
		{
			index += strcspn(str[++index], "\"'");
			last++;
		}
		else //if not, get index of next space
		{
			index += charAt(str[index], ' ');

			if(index < last) //if no spaces found, that's a problem...exit
			{
				free(dst);
				return -1;
			}

			//if current index is a space, move up 1 and try again
			while(index == last)
			{
				index += charAt(str[++index], ' ');
				last++;
			}
		}

		// if(needQuote > 0) //if we need another quote to match
		// {
		// 	index += quotes;
		// 	needQuote = -1;
		// }
		// else //if we don't need to find a matching quote
		// {
		// 	space = charAt(str[index], ' '); //get space index
		// 	if(quotes < space) //if we found a quote first
		// 	{
		// 		index += quotes;
		// 		needQuote = 1;
		// 	}
		// 	else //if we found a space first
		// 		index += space;
		// }

		// if(index < 0) //if no more spaces
		// 	break;

		//malloc space for new string and copy it to dst
		// dst[counter] = (char*)malloc(++index - last);
		int diff = index++ - last;
		dst[counter] = (char*)malloc(diff + 1);
		strncpy(dst[counter], str[last], diff);
		dst[counter++][diff] = '\0'; //add trailing NUL byte
	}

	//tokenize once then loop
	// temp = strtok(str[tempSize], delim);
	// while(temp)
	// {
	// 	//get size and copy to dst.
	// 	// tempSize += strlen(temp) + 1;
	// 	dst[counter] = (char*)malloc(tempSize);
	// 	strcpy(dst[counter++], temp);

	// 	//get quotes and space index and determine delim
	// 	quotes = strcspn(str[tempSize], "\"'");
	// 	space = charAt(str[tempSize], ' ');
	// 	// delim = (quotes > space) ? "\"'" : " " ;

	// 	//tokenize again
	// 	// temp = strtok(str[tempSize], delim);
	// }

	// //tokenize once then loop
	// temp = strtok(str[tempSize], delim);
	// while(temp)
	// {
	// 	//get size and copy to dst.
	// 	tempSize += strlen(temp) + 1;
	// 	dst[counter] = (char*)malloc(tempSize);
	// 	strcpy(dst[counter++], temp);

	// 	//get quotes and space index and determine delim
	// 	quotes = strcspn(str[tempSize], "\"'");
	// 	space = charAt(str[tempSize], ' ');
	// 	delim = (quotes > space) ? "\"'" : " " ;

	// 	//tokenize again
	// 	temp = strtok(str[tempSize], delim);
	// }

	// do
	// {
	// 	size_t tempSize = strlen(temp) + 1;
	// 	// int single = charAt(str[tempSize], '\'');
	// 	// int dub = charAt(str[tempSize], '"');
	// 	int quotes = strcspn(str[tempSize], "\"'");
	// 	int space = charAt(str[tempSize], ' ');
	// 	char delim[] = (quotes > space) ?  "\"'": " ";

	// 	temp = strtok(str[tempSize], delim);
	// }
	// while(temp); //while temp isn't null
	// while((c = str[index++]) != '\0') //while not a null byte
	// {
	// 	int single = charAt(str, '\'');
	// 	int dub = charAt(str, '"');

	// 	// int space = charAt(str, ' ');
	// }
	// for(int i = 0; i < strlen(str); i++)
	// {
		// if
		//code
	// }
	// for(size_t i = 0; i < size; i++)
	// {
	// 	int index = 0;
	// 	for(size_t j = 0; j < strlen(str); j++)
	// 	{
	// 		//keep track of last
	// 		// index = strcspn(str, " '\"");
	// 		//probz better to just make a charAt function and use that instead
	// 		if(str[j] == '\'') //look for the end '
	// 		{
	// 			//code
	// 		}
	// 		else if(str[j] == '"') //look for the end "
	// 		{
	// 			//code
	// 		}
	// 		else //look for a space
	// 		{
	// 			index = charAt(str, ' ', j);
	// 		}
	// 	}
		// int single = charAt();
		// int dub = charAt();
		// if
	// }
/*	while(temp) //while not null, keep tokenizing
	{
		//realloc dst to hold new number of strings we have
		char *tempBuf = (char*)realloc(dst, ++size);
		if(tempBuf) //if not null, realloc the current string
		{
			dst = tempBuf
			tempBuf = (char*)realloc(dst[size], strlen(temp) + 1);
		}
		// temp = strtok(NULL, " \""); //<- not right delim
	}
*/
	// free(backup);
	return size;
}

//gets more complicated to do it my way
// char *myStrTok(char *str, const char *delim)
// {
// 	if(!str)
// 		return NULL;

// 	//create a temp buf and copy str to it
// 	char *temp = (char*)malloc(strlen(str) + 1);
// 	strcpy(temp, str);
// 	char c;

// 	// do //increase temp until it hits null or matches the delim
// 	// {
// 	// 	str++;
// 	// 	if((c = *temp++) == '\0')
// 	// 		return NULL;
// 	// } while(strchr(delim, c));

// 	// //decrement temp to not include delim, get rest of the string in str
// 	// temp--;
// 	// str = temp + strcspn(str, delim);

// 	// if(*s != 0)
// 	// 	*s++ = 0;

// 	return temp;
// }

/*  Function: countSpaces
 *  Parameters: str - string to count in
 				c - char to find
 *  Purpose: Count how many times the char c is present in the given string.
 *	Returns: Number of occurences of the char c in str.
 */
int charAt(const char *str, const char c)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		if(str[i] == c)
			return i;
	}
	return -1;
}

/*  Function: countSpaces
 *  Parameters: str - string to count in
 *  Purpose: Count how many times a space is in the given str, but not
 	counting the ones inside of single or double quotes. Done somewhat lazily
 	because there will never be nested quotes, so the function doesn't have to
 	account for a single quote inside a double and vice versa.
 *	Returns: Number of times a space is in the str excluding those in quotes.
 */
size_t countSpaces(const char *str)
{
	short toggle = 1;
	for(size_t i, count = 0; i < strlen(str); i++)
	{
		if(str[i] == ' ' && toggle > 0) //if not inside quoted text
			count++;
		else if(str[i] == '\'' || str[i] == '"')
			toggle *= -1;
	}

	return count;
}

/*  Function: echo
 *  Parameters: args - string array of arguments to print
 *  Purpose: Print the given arguments to stdout.
 *  Returns: Nothing.
 */
void echo(const char **args, size_t size)
{
	size_t i;
	for(i = 0; i < (size - 1); i++)
		printf("%s ", args[i])

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
