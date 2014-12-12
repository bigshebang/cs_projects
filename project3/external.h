/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 3 - MY SHell
 *  filename: external.h
 *	Header file for the external command handling/running module.
 */

#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//fork/exec the given command with its arguments
int run(char **args);

#endif
