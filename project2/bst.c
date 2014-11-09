/*	ljm3103 - Luke Matarazzo
 *	filename: bst.c
 *	Create a binary search tree (bst) which will contain the users on the
 *	amigonet.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

//prototypes
int strToInt(char[]);	//convert ascii to int

//define return values
#define EXIT_SUCCESS	0
#define WRONG_NUM_ARGS	-1
#define NEGATIVE_NUM	-2

/*	Function: strToInt
 *	Parameters: str - array of characters that needs to be converted.
 *	Purpose: Take in a C string assuming that it is or contains integer values,
 *	and convert it to an integer.
 *	Returns: An int which is the converted value from the C string.
 */
int strToInt(char str[])
{
	int ret = 0;
	for(unsigned int i = 0; i < strlen(str); i++)
	{
		if(isdigit(str[i]))
			ret = ret * 10 + str[i] - '0';
		else
		    break;
	}
	return ret;
}

/*	Function: build_tree
 *	Parameters: root - pointer to a TreeNode pointer
				name - name of user to add to tree
 *	Purpose: Create binary search tree or insert node into tree if it already
 *	existed.
 *	Returns: Nothing.
 */
void buildTree(TreeNode** root, const char* name)
{
	//create and initialize tree node
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->left = NULL;
	temp->right = NULL;

	//create and initialize user
	temp->user = (User*)malloc(sizeof(User));
	temp->user->amigos = NULL;

	//handle adding name
	temp->user->name = (char*)malloc(sizeof(name));
	char *tempStr = temp->user->name;
	strcpy(tempStr, name);
	tempStr = NULL;


	//insert into bst
	if(*root == NULL) //make root if we don't have one yet
		*root = temp;
	else //place element in proper place in bst
	{
		TreeNode *current = *root;
		TreeNode *next = current; //we want it to be not null initially

		//traverse tree to find where this element should go
		while(next != NULL)
		{
			int ret = strcmp(temp->user->name, current->user->name);
			
			if(ret == 0) //if already exists print error and exit
			{
				fprintf(stderr, "Cannot add user '%s'. User already exists.",
						name);
				return;
			}
			else if(ret < 0) //if new element's data < current element's data
			{
				next = current->left;

				//if next is null, that's where the new element should go
				if(next == NULL)
					current->left = temp;
			}
			else //new element's data is greater than current element's
			{
				next = current->right;

				//if next is null, that's where the new element should go
				if(next == NULL)
					current->right = temp;
			}
			current = next;
		}
	}
}

/*  Function: locateUser
 *  Parameters: root - Pointer to a TreeNode which is the root of the bst.
				name - Name of user that you want to find.
 *  Purpose: Find a user specified by the name and return that node.
 *  Returns: Nothing.
 */
User *locateUser(const TreeNode *root, const char* name)
{
	if(root != NULL) //if root is not null, find user and return it
	{
		int ret = strcmp(name, root->user->name);
		if(ret == 0) //if we have a match
			return root->user;
		else if(ret > 0) //if greater than given user
			return locateUser(root->right, name);
		else //if less than given user
			return locateUser(root->left, name);
	}

	return NULL; //return null if treenode given was null
}

/*  Function: traverse
 *  Parameters: root - Pointer to a TreeNode which is the root of the bst
 *  Purpose: Traverse a given bst and print out the values of each node as we
 *	process them.
 *  Returns: Nothing.
 */
void traverse(const TreeNode *root)
{
	if(root != NULL)
	{
		traverse(root->left);
		printf("\nUser: %s; Friends: ", root->user->name);
		printList(root->user->amigos);
		traverse(root->right);
	}
}

/*  Function: cleanup_tree
 *  Parameters: root - TreeNode pointer that is the root of a bst.
 *  Purpose: Deallocate the dynamically allocated memory from the build_tree
	function.
 *  Returns: Nothing.
 */
void cleanupTree(TreeNode* root)
{
	//recursively loop through bst in a post-order fashion and free elements
	if(root != NULL)
	{
		cleanupTree(root->left);
		cleanupTree(root->right);
		free((void*)root->user->name);
		free(root->user);
		listDestroy(root->user->amigos);
		free(root);
	}
}
