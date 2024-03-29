/*	ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *	filename: bst.c
 *	Create a binary search tree (bst) which will contain the users on the
 *	amigonet.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

/*	Function: buildTree
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
	if(temp == NULL)
	{
		fprintf(stderr, "Could not allocate space for user.\n");
		return;
	}
	temp->left = NULL;
	temp->right = NULL;

	//create and initialize user
	temp->user = (User*)malloc(sizeof(User));
	if(temp->user == NULL)
	{
		fprintf(stderr, "Could not allocate space for user.\n");
		return;
	}
	temp->user->amigos = NULL;

	//handle adding name
	temp->user->name = (char*)malloc(sizeof(name));
	if(temp->user->name == NULL)
	{
		fprintf(stderr, "Could not allocate space for user's name.\n");
		return;
	}
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
 *  Purpose: Traverse a given bst and print the username and their friends list
 *  Returns: Nothing.
 */
void traverse(const TreeNode *root)
{
	//if not null, traverse left node, print info about current node then
	//traverse the right node. Essentially an in-order traversal.
	if(root != NULL)
	{
		traverse(root->left);
		printf("\nUser %s; friends: ", root->user->name);
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
		listDestroy(root->user->amigos); //destroy friends list
		free(root->user);
		free(root);
	}
}
