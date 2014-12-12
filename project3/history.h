/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: history.h
 *	Header file for command history module. Circle buffer is used to store the
 	command history.
 */

#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//initialize the history buffer
void initHistory(char **commands, unsigned long size);

//add a command to the history buffer
int addCommand(char **commands, unsigned long size, const char *command,
			   unsigned long current);

//get a command from the history buffer using a given index
char *getCommand(char **commands, unsigned long size, unsigned long current,
				 unsigned long command);

//print the contents of history buffer
void printHistory(char **commands, unsigned long size, unsigned long current);

//deallocate dynamic memory needed for history buffer
void destroyHistory(char **commands, unsigned long size);

#endif
