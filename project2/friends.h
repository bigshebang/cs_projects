/*	ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *	filename: friends.h
 *	Header file for friends which is a queue/linked list data structure.
 */

#ifndef FRIENDS_H
#define FRIENDS_H
#include "amigonet.h"

typedef struct node //linked list node struct
{
	User *user;				//our user
	struct node *next;		//pointer to next node
} node;
typedef node *nodePtr;

typedef struct Friends_struct //friends list struct
{
	nodePtr firstFriend;	//current/starting friend
} FriendStruct;

//functions
void addNode(User *user, User *amigo); //add a node to another's list
void removeNode(User *user, User *exAmigo); //remove a node from another's list
void printList(FriendStruct *friends); //print a given list
void listDestroy(FriendStruct *friends); //deallocate memory for a given list

#endif
