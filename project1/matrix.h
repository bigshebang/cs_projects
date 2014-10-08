/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: matrix.h
 *	Matrix header file, containing indexStruct struct and function prototypes
 *	for the matrix "module".
 */

#include "classes.h"
#include <stdio.h>

typedef struct indexStruct //struct to contain values for each spot in the tm
{
	    int nextState; 	//next state to go to
	    char action; 	//char representing action to take, (s)ave or (d)elete
} indexStruct;

int strToInt(char[]);								//convert ascii to int
void initMatrix(FILE*, indexStruct[][N_CC], int);	//initialize tm
void printMatrix(indexStruct[][N_CC], int);			//print a given tm
