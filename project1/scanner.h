/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: scanner.h
 *	Header for the scanner "module" containing its function prototypes.
 */

#include "matrix.h"

#define ERROR_STATE	99 //error state

//return states for the scan function
#define ACCEPT_STATE		0
#define EOF_ACCEPT			1
#define ERROR_STATE_RET		-1
#define ERROR_STATE_EOF		2


int getClass(char);										//classify a given char
int scan(indexStruct[][N_CC], const int*, const int*);	//tokenize input
