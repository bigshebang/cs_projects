/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *  filename: amigonet.c
 *  File containing the amigonet API which can create/destroy an amigonet
 *	add and find users, friend and unfriend users, find degrees of seperation
 *	between users, and dump all data about users and their friends.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

#define MAX_DEPTH		50		//max search depth for separation
#define USER_FOUND		1		//return value for when we found the user
#define USER_NOT_FOUND	0		//for when we haven't found the user

static TreeNode *users;	//pointer to our users

/*  Function: create_amigonet
 *  Parameters: None.
 *  Purpose: Initialize users treenode to NULL. Memory will be allocated
 *	when actually adding users to the tree.
 *  Returns: Nothing.
 */
void create_amigonet()
{
	users = NULL;
}

/*  Function: destroy_amigonet
 *  Parameters: None.
 *  Purpose: Free all memory allocated for users and their friends list.
 *  Returns: Nothing.
 */
void destroy_amigonet()
{
	cleanupTree(users);
}

/*  Function: addUser
 *  Parameters: name - Name of user to add.
 *  Purpose: Add a user to our list using the given name.
 *  Returns: Nothing.
 */
void addUser(const char *name)
{
	buildTree(&users, name);
}

/*  Function: findUser
 *  Parameters: name - Name of user to find.
 *  Purpose: Find a user based on a given name. Use function in bst module.
 *  Returns: Pointer to the user that we found, null if not found.
 */
User *findUser(const char *name)
{
	return locateUser(users, name);
}

/*  Function: addAmigo
 *  Parameters: user - one user to add to friend list
 *				amigo - second user to add to list
 *  Purpose: Add two users to each other's friends list.
 *  Returns: Nothing.
 */
void addAmigo(User *user, User *amigo)
{
	if(addNode(user, amigo)) //if successful, add amigo the other way around
		addNode(amigo, user);
}

/*  Function: removeAmigo
 *  Parameters: user - first user of removal
 *				ex_amigo - second user of removal
 *  Purpose: Remove two friends from each other's friends list.
 *  Returns: Nothing.
 */
void removeAmigo(User *user, User *ex_amigo)
{
	if(removeNode(user, ex_amigo)) //if successful, remove the other way around
		removeNode(ex_amigo, user);
}

/*  Function: dls
 *  Parameters: user1 - first user who has the friends list to search
 *				user2 - second user to find in the list
 *				max - int which is the max depth
 *  Purpose: Perform a depth limited search based on the given max value.
 *  Returns: int, which is 1 if we find what we want and 0 if we don't.
 */
int dls(const User *user1, const User *user2, int max)
{
	if(max >= 0) //if we haven't exceeded max depth, keep doing
	{
		if(strcmp(user1->name, user2->name) == 0) //if it's what we want
			return USER_FOUND;

		//for each child in node, call dls on it with max being one less
		if(user1->amigos != NULL) //make sure amigos is not null
		{
			nodePtr curNode = user1->amigos->firstFriend;
			nodePtr nextNode = curNode;
			while(curNode != NULL && nextNode != NULL) //loop through friends
			{
				curNode = nextNode;
				nextNode = curNode->next;

				//if any returns true, return true
				if(dls(curNode->user, user2, max-1))
					return USER_FOUND;
			}
		}
		return USER_NOT_FOUND; //return default of false
	}
	return USER_NOT_FOUND; //return default of false
}

/*  Function: separation
 *  Parameters: user1 - first user who has the friends list to search
 *				user2 - second user to find in the list
 *  Purpose: Determine degrees of separation between two users based upon
 *	their friends lists. Use iterative depth first search which calls a
 *	recrusive depth limited search function.
 *  Returns: size_t which is the number of degrees of separation between
 *	the two users.
 */
size_t separation(const User *user1, const User *user2)
{
	//do dls with increasing depth until we hit MAX_DEPTH
	for(int i = 0; i < MAX_DEPTH; i++)
	{
		if(dls(user1, user2, i))
			return i;
	}
	return -1;
}

/*  Function: dump_data
 *  Parameters: None.
 *  Purpose: Print all users in database and all their friends.
 *  Returns: Nothing.
 */
void dump_data()
{
	traverse(users);
	puts("\n"); //put two newlines
}
