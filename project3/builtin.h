/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.h
 *	Header file for builtin shell functions.
 */
#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"	//history module
#include "parse.h"		//parsing args module

//echo the given arguments to the screen with a space between each one
void echo(char **args, size_t size, size_t start);

//print the help for builtin functions
void help(const char *usageMess);

//handle the verbose command; turn verbose mode on or off
void verbose(char *str);

#endif
