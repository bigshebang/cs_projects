/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: parse.h
 *	Header file for the argument parsing module.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//split args found in a string and add to array of strings
int split(char *str, char ***dst);

//find the index at which a given character is found in a string
int charAt(const char *str, const char c);

//count the number of valid arguments for a given string
int countArgs(const char *str);

//deallocate dynamic memory needed for creating the args string array.
void destroyArgs(char **str, int size);
