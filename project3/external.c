/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: history.c
 *	Implementation of all the command execution/running/handling module.
 */

#include <unistd.h>
#include <sys/wait.h>
#include "external.h"

/*  Function: run
 *  Parameters: args - array of strings containing the arguments
 *  Purpose: Initialize a command history array to have all null pointers.
 *  Returns: The return status of the program.
 */
int run(char **args)
{
	pid_t pid;
	//fork, execvp(args[0], args)
	//may need to add NULL to the end of args or something?
	// ^ did that in split function, should be good but should be tested
	if((pid = fork()) == -1) //if error
	{
		//code
	}
	else if(!pid) //if child
	{
		int ret = execvp(args[0], args); //execute given command with args
		if(ret == -1) //if problem with exec
			perror("mysh");
		return ret;
	}
	else //if parent
	{
		//******************************************************
		//		    not sure if this is done..check it!
		//******************************************************
		//wait for child to finish, read exit status and return
		int status = 0;
		pid_t ret = wait(&status);
		if(ret == -1)
			perror("mysh");

		//check exit status of child
		if(WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			return exit_status;
		}
	}
}
