/*  ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *  filename: amigonet.c
 *  File containing TO DO: complete this
 */

#include <stdlib.h>

// DO THIS with real stuffz
typedef struct Friends_struct {
	int temp;
} FriendStruct;

#include "amigonet.h"
#include "bst.h"

static TreeNode *users;	//pointer to our users

/*  Function: create_amigonet
 *  Parameters: None.
 *  Purpose: Take in an ordering function and create a queue ADT.
 *  Returns: Nothing.
 */
void create_amigonet()
{
	users = NULL;
}

/*  Function: destroy_amigonet
 *  Parameters: cmp - pointer to a function that returns an int and takes two
 *  Purpose: Take in an ordering function and create a queue ADT.
 *  Returns: QueueADT, a pointer to a queueStruct.
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
 *  Parameters: cmp - pointer to a function that returns an int and takes two
 *  Purpose: Take in an ordering function and create a queue ADT.
 *  Returns: Nothing.
 */
void addAmigo(User *user, User *amigo)
{
	//code
}

/*  Function: removeAmigo
 *  Parameters: cmp - pointer to a function that returns an int and takes two
 *  Purpose: Take in an ordering function and create a queue ADT.
 *  Returns: Nothing.
 */
void removeAmigo(User *user, User *ex_amigo)
{
	//code
}

/*  Function: separation
 *  Parameters: user1 - ...
 *				user2 - ...
 *  Purpose: Take in an ordering function and create a queue ADT.
 *  Returns: QueueADT, a pointer to a queueStruct.
 */
size_t separation(const User *user1, const User *user2)
{
	//code
}

/*  Function: dump_data
 *  Parameters: None.
 *  Purpose: 
 *  Returns: Nothing.
 */
void dump_data()
{
	//code
}
