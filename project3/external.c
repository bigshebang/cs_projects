/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: history.c
 *	Implementation of the command execution/running/handling module.
 */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "external.h"
#include "parse.h"

#define	EXIT_WAIT_FAIL	-1
#define EXIT_CHILD_FAIL	-2

/*  Function: run
 *  Parameters: args - array of strings containing the arguments
 *  Purpose: Fork then exec and run given command with args.
 *  Returns: The return status of the program. -1 if waiting fails, -2 if the
	child fails during the exec.
 */
int run(char **args)
{
	//fork; if child, exec; if parent wait and return child's exit status
	pid_t pid;
	if((pid = fork()) == -1) //if error
	{
		perror("mysh");
		return pid;
	}
	else if(!pid) //if child
	{
		if(verboseMode)
			printf("\texecvp: %s\n", args[0]);

		int ret = execvp(args[0], args); //execute given command with args
		if(ret == -1) //if problem with exec
			perror(args[0]);

		return EXIT_CHILD_FAIL;
	}
	else //if parent
	{
		if(verboseMode)
			printf("\tWait for pid %d: %s\n", pid, args[0]);

		//wait for child to finish, read exit status and return
		int status = 0;
		pid_t ret = waitpid(pid, &status, 0);

		if(ret == -1) //if error waiting
		{
			perror("mysh");
			return ret;
		}

		//check exit status of child and return if it's finished
		if(WIFEXITED(status))
			return WEXITSTATUS(status);

		return EXIT_WAIT_FAIL;
	}
}
