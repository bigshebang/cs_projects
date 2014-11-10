/*	ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *	filename: bst.h
 *	bst header file.
 */

#ifndef BST_H
#define BST_H
#include "friends.h"

//The definition of the tree structure
typedef struct TreeNode
{
	User* user;					//user that we're holding
    struct TreeNode* left;		//node's left child
    struct TreeNode* right;		//node's right child
} TreeNode;

//functions
void buildTree(TreeNode** root, const char *name); //insert user/build tree
User *locateUser(const TreeNode *root, const char* name); //find a user
void traverse(const TreeNode *root); //traverse bst and print data for users
void cleanupTree(TreeNode* root); //free dynamically allocated memory for bst

#endif
