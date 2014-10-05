/// ljm3103 - Luke Matarazzo
/// CSCI-243 -- Project 1 - Scanner
/// filename: tokenize.c

#include "classes.h"
#include <stdio.h>

//define exit statuses used in program
#define EXIT_SUCCESS	0
#define MISSING_ARG		-1
#define BAD_FILE		-2

int main(int argc, char *argv[])
{
	if(argc != 2) //if no args given, print error and exit
	{
		fprintf(stderr, "usage: %s tm_file\n", argv[0]);
		return MISSING_ARG;
	}

	//open file given as command line arg and read it
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp == NULL) //if file couldn't open correctly, print error and exit
	{
		perror(argv[1]);
		return BAD_FILE;
	}
	
	return EXIT_SUCCESS;
}

