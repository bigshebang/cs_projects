/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: builtin.h
 *	Header file for builtin shell functions.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initHistory(char **commands, unsigned long size);
int addCommand(char **commands, unsigned long size, const char *command,
			   unsigned long current);
char *getCommand(char **commands, unsigned long size, unsigned long current,
				 unsigned long command);
void printHistory(char **commands, unsigned long size, unsigned long current);
void destroyHistory(char **commands, unsigned long size);

size_t split(char *str, char **dst);
int charAt(const char *str, const char c);
int countSpaces(const char *str);
void destroyArgs(char **str, int size);
void echo(const char **args, size_t size);
void help();
void verbose();
