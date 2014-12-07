/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.h
 *	Header file for builtin shell functions.
 */

int addCommand(char **commands, unsigned long size, char *command
			   unsigned long current);
void printHistory(char **commands, unsigned long size);
void destroyHistory(char **commands, unsigned long size);
