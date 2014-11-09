/*	ljm3103 - Luke Matarazzo
 *  CSCI-243 -- Project 2 - Amigonet
 *	filename: bst.h
 *	bst header file.
 */

#ifndef BST_H
#define BST_H
#include "amigonet.h"
#include "friends.h"

/// The definition of the tree structure
typedef struct TreeNode {
	User* user;					//user that we're holding
    struct TreeNode* left;		//node's left child
    struct TreeNode* right;		//node's right child
} TreeNode;

/// The three supported traversals
typedef enum {
    PREORDER,           // parent -> left -> right
    INORDER,            // left -> parent -> right
    POSTORDER           // left -> right -> parent
} TraversalType;

/// build_tree() 
///     Dynamically build BST by allocating nodes on the heap
///             Note that the BST will support duplicate values by
///             placing them into the left child's subtree
///
/// args -
///        root - a pointer to the pointer to the root of the tree
///               to build this tree on to.
///        elements - array of integers to add to the tree
///        count - the number of integers in the array
void buildTree(TreeNode** root, const char *name);

User *locateUser(const TreeNode *root, const char* name);
// void insertNode(TreeNode** root, const char* name);

/// traverse()
///    Recursively traverses the tree and prints the value of each
///    node.
///
/// args -
///        root - a pointer to the root of the tree to traverse
///        type - the traversal type
void traverse(const TreeNode *root);

/// cleanup_tree()
///    Cleanup all memory management associated with the nodes on the heap
///
/// args
///      root - the current root of the tree
void cleanupTree(TreeNode* root);

#endif
