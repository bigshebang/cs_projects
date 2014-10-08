/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: tokenize.c
 *	File containing main method for reading in a transition matrix, and
 *	outputting text based upon the input text and the given transition matrix.
 */

#include "scanner.h"

//define exit statuses used in program
#define EXIT_SUCCESS	0
#define MISSING_ARG		-1
#define BAD_FILE		-2


/*	Function: main
 *	Purpose: Take a command line argument expected to be a specifically
 *	formatted transition matrix and use that to scan and tokenize data given
 *	from stdin. This will print the transition matrix received and then
 *	the results from parsing the input using the given transition matrix.
 *	Returns the exit status of the program, which would be 0 for success and
 *	non-zero for failure. Error numbers defined above.
 */
int main(int argc, char *argv[])
{
	if(argc != 2) //if no args given, print error and exit
	{
		fprintf(stderr, "usage: %s tm_file\n", argv[0]);
		return MISSING_ARG;
	}

	//open file given as command line arg and read it
	FILE *tmFile;
	tmFile = fopen(argv[1], "r");
	if(tmFile == NULL) //if file couldn't open correctly, print error and exit
	{
		perror(argv[1]);
		return BAD_FILE;
	}

	//declare state vars and read them in from the file
	int numStates = 0, startState = 0, acceptState = 0;
	fscanf(tmFile, "%*s %d %*s %d %*s %d ", &numStates, &startState,
		   &acceptState);

	//create matrix and initialize values according to tm file
	indexStruct tm[numStates][N_CC];
	initMatrix(tmFile, tm, numStates);

	fclose(tmFile);

	//print heading for tm
	printf("Scanning using the following matrix:\n ");
	for(int i = 0; i < N_CC; i++)
		printf("   %2d", i);

	printMatrix(tm, numStates); //print tm

	int status = 0; //return status of scanning function

	while(status < EOF_ACCEPT) //continue scanning until EOF is reached
	{
		status = scan(tm, &startState, &acceptState);
		if(status == ERROR_STATE_RET || status == ERROR_STATE_EOF)
			puts("rejected");
	}

	return EXIT_SUCCESS;
}
