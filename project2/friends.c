/*  ljm3103 - Luke Matarazzo
 *  filename: friends.c
 *	asdf
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <stdbool.h>
// #include <assert.h>
#include "friends.h"

/*  Function: addNode
 *  Parameters: user - user who has friends list we're adding to
 *				amigo - friend to add to the linked/friends list
 *  Purpose: Add a given user to another user's friend list.
 *  Returns: Nothing.
 */
void addNode(User *user, User *amigo)
{
	if(user == NULL || amigo == NULL) //if user is null, print error and return
	{
		fprintf(stderr, "User given is null.\n");
		return;
	}

	if(user->amigos == NULL) //if user has no friends yet create new list
	{
		puts("this user has no friends yet. creating list...");
		//malloc friends list and make sure not null
		user->amigos = (FriendStruct*)malloc(sizeof(FriendStruct));
		if(user->amigos == NULL)
		{
			fprintf(stderr, "Could not allocate memory for friends list.\n");
			return;
		}

		//malloc a new node ane make sure not null
		user->amigos->firstFriend = (nodePtr)malloc(sizeof(node));
		if(user->amigos->firstFriend == NULL)
		{
			fprintf(stderr, "Could not allocate memory for friends list.\n");
			return;
		}

		//initialize data in node
		user->amigos->firstFriend->user = amigo;
		user->amigos->firstFriend->next = NULL;
	}
	else //if user already has friends, add to end of list
	{
		puts("user already has friends, adding to end...");
		//create new node and add data to it. make sure it's not null too
		nodePtr newNode = (nodePtr)malloc(sizeof(node));
		if(newNode == NULL) //if new node is null, print error and return
		{
			fprintf(stderr, "Could not allocate memory for friends list.\n");
			return;
		}

		//initialize data in node
		newNode->user = amigo;
		newNode->next = NULL;

		//node pointers used in while loop
		nodePtr curNode = user->amigos->firstFriend;
		nodePtr nextNode = curNode;

		while(nextNode != NULL)
		{
			curNode = nextNode;
			nextNode = curNode->next;
		}

		//add new node to end of linked list
		curNode->next = newNode;
	}
}

/*  Function: removeNode
 *  Parameters: user - User who has friends list
 				exAmigo - User to remove from the friends list
 *  Purpose: Remove a node/friend from one given list via a specific user.
 *  Returns: Nothing.
 */
void removeNode(User *user, User *exAmigo)
{
	//if neither user is null and they're not the same user
	if(user != exAmigo && user != NULL && exAmigo != NULL)
	{
		puts("inside if");
		nodePtr curNode = user->amigos->firstFriend;
		nodePtr nextNode = curNode;
		int ret = -1;

		//while next is not null and it's not the node we want, go to next
		while(nextNode != NULL && 
			  (ret = strcmp(nextNode->user->name, exAmigo->name)) != 0)
		{
			curNode = nextNode;
			nextNode = curNode->next;
		}

		if(ret == 0) //if it's a match, remove
		{
			nodePtr temp = nextNode->next;
			if(temp != NULL)
			{
				*nextNode = *(temp);
				free(temp);
			}
			else
				free(nextNode);

			// if(curNode == nextNode) //if first node
			// {
			// 	puts("first node");
			// 	user->amigos->firstFriend = nextNode->next;
			// }
			// else //if not first node
			// {
			// 	puts("not first node");
			// 	curNode->next = nextNode->next;
			// }
			// free(nextNode);
		}
	}
}

/*  Function: printList
 *  Parameters: friends - pointer to a friends list that should be printed
 *  Purpose: Print all members in a friends list.
 *  Returns: Nothing.
 */
void printList(FriendStruct *friends)
{
	//if friends and friend list is not null, print list
	if(friends != NULL && friends->firstFriend != NULL)
	{
		nodePtr curNode = friends->firstFriend;
		nodePtr nextNode = NULL;
		while(curNode != NULL)
		{
			nextNode = curNode->next;
			printf("%s%s", curNode->user->name,
				   (nextNode != NULL) ? " " : "");
			curNode = nextNode;
		}
	}
}

/*  Function: listDestroy
 *  Parameters: friends - pointer to a friends list that should be deleted
 *  Purpose: Free memory allocated for a friends list.
 *  Returns: Nothing.
 */
void listDestroy(FriendStruct *friends)
{
	//if friends and friend list is not null, destroy the list
	if(friends != NULL && friends->firstFriend != NULL)
	{
		nodePtr curNode = friends->firstFriend;
		nodePtr nextNode = NULL;
		if(curNode != NULL)
		{
			nextNode = curNode->next;
			free(curNode);
			curNode = nextNode;
		}

		free(friends);
	}
}
