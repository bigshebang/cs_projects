/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *  filename: amigonet.c
 *  File containing the amigonet API which can create/destroy an amigonet
 *	add and find users, friend and unfriend users, find degrees of seperation
 *	between users, and dump all data about users and their friends.
 */

#include <stdlib.h>
#include <stdio.h>
#include "amigonet.h"
#include "bst.h"
#include "friends.h"

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
	int ret = addNode(user, amigo);
	if(ret) //if successful, add amigo the other way around
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
	int ret = removeNode(user, ex_amigo);
	if(ret) //if successful, remove the other way around
		removeNode(ex_amigo, user);
}

/*  Function: separation
 *  Parameters: user1 - first user who has the friends list to search
 *				user2 - second user to find in the list
 *  Purpose: Determine degrees of separation between two users based upon
 *	their friends lists.
 *  Returns: size_t which is the number of degrees of separation between
 *	the two users.
 */
size_t separation(const User *user1, const User *user2)
{
	if(strcmp(user1->name, user2->name) == 0)
		return 0;
	else
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
