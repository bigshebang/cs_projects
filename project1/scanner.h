/*	ljm3103 - Luke Matarazzo
 *	CSCI-243 -- Project 1 - Scanner
 *	filename: scanner.h
 *	Header for the scanner "module" containing its function prototypes.
 */

#include "matrix.h"

#define ERROR_STATE	99 //error state

int getClass(char);										//classify a given char
int scan(indexStruct[][N_CC], const int*, const int*);	//tokenize input
