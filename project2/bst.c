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

int main(int argc, char *argv[])
{
	// if(argc < 2) //if arg not given, print error and exit
	// {
	// 	puts("Usage: bst #");
	// 	return WRONG_NUM_ARGS;
	// }
	
	// int size = strToInt(argv[1]);
	
	// if(size <= 0) //if num given is less than 0, print error and exit
	// {
	// 	puts("# must be greater than 0");
	// 	return NEGATIVE_NUM;
	// }

	// int nums[size]; //array to hold expected numbers from stdin
	char *nums[] = {"John", "Carl", "Andrew", "Zeaque", "Kim"};
	int size = 5;

	// printf("Enter %d integer values to place in tree:\n", size);

	// for(int i = 0; i < size; i++) //read ints int
	// 	scanf("%d", nums+i);

	//print heading and then given values
	puts("Input values:");
	for(int i = 0; i < size; i++)
		printf("%s\n", nums[i]);

	//create root treenode and build tree from given numbers
	TreeNode *tn = NULL;
	// build_tree(&tn, nums);
	for(int i = 0; i < size; i++)
		buildTree(&tn, nums[i]);

	// //print preordered
	// puts("Preorder:");
	// traverse(tn, PREORDER);

	//print inorder
	puts("Inorder:");
	traverse(tn, INORDER);

	User *tempUser = locateUser(tn, "Andrew");
	if(tempUser != NULL)
		printf("user found was: '%s'\n", tempUser->name);

	// //print postorder
	// puts("Postorder:");
	// traverse(tn, POSTORDER);

	cleanupTree(tn); //free memory that was allocated to create bst

	return EXIT_SUCCESS;
}

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
				name - 
 *	Purpose: 
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
				fprintf(stderr, "Cannot add user '%s'. User already exists.");
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

/*  Function: traverse
 *  Parameters: root - Pointer to a TreeNode which is the root of the bst
				name - 
 *  Purpose: 
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
				type - type of traversal defined in bst.h:18-22
 *  Purpose: Traverse a given bst as defined by the given type of traversal and
	print out the values of each node as we process them.
 *  Returns: Nothing.
 */
// void traverse(const TreeNode *root, const TraversalType type)
// {
// 	switch(type)
// 	{
// 		case PREORDER: //print data member, traverse left and right recursively
// 			if(root != NULL)
// 			{
// 				printf("%s\n", root->user->name);
// 				traverse(root->left, PREORDER);
// 				traverse(root->right, PREORDER);
// 			}
// 			break;
// 		case INORDER: //traverse left, print data member then traverse right
// 			if(root != NULL)
// 			{
// 				traverse(root->left, INORDER);
// 				printf("%s\n", root->user->name);
// 				traverse(root->right, INORDER);
// 			}
// 			break;
// 		case POSTORDER: //traverse left, then right, then print data member
// 			if(root != NULL)
// 			{
// 				traverse(root->left, POSTORDER);
// 				traverse(root->right, POSTORDER);
// 				printf("%s\n", root->user->name);
// 			}
// 			break;
// 		default:
// 			puts("You did not give a recognized type of traversal.");
// 			break;
// 	}
// }

/*  Function: cleanup_tree
 *  Parameters: root - TreeNode pointer that is the root of a bst
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
		free(root);
	}
}
