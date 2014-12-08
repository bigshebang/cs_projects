/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.h
 *	Header file for builtin shell functions.
 */

void initHistory(char **commands, unsigned long size);
int addCommand(char **commands, unsigned long size, const char *command,
			   unsigned long current);
void printHistory(char **commands, unsigned long size, unsigned long current);
void destroyHistory(char **commands, unsigned long size);
