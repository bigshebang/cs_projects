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
		fprintf(stderr, "User given is null.");
		return;
	}

	if(user->amigos == NULL) //if user has no friends yet create new list
	{
		//malloc friends list and make sure not null
		user->amigos = (FriendStruct*)malloc(sizeof(FriendStruct));
		if(user->amigos == NULL)
		{
			fprintf(stderr, "Could not allocate memory for friends list.");
			return;
		}

		//malloc a new node ane make sure not null
		user->amigos->firstFriend = (nodePtr)malloc(sizeof(node));
		if(user->amigos->firstFriend == NULL)
		{
			fprintf(stderr, "Could not allocate memory for friends list.");
			return;
		}

		//initialize data in node
		user->amigos->firstFriend->user = amigo;
		user->amigos->firstFriend->next = NULL;
	}
	else //if user already has friends, add to end of list
	{
		//create new node and add data to it. make sure it's not null too
		nodePtr newNode = (nodePtr)malloc(sizeof(node));
		if(newNode == NULL) //if new node is null, print error and return
		{
			fprintf(stderr, "Could not allocate memory for friends list.");
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
		nodePtr curNode = user->amigos->firstFriend;
		nodePtr nextNode = curNode;
		int ret = -1;

		//while next is not null and it's not the node we want, go to next
		while(nextNode != NULL && 
			  !(ret = strcmp(nextNode->user->name, exAmigo->name)))
		{
			curNode = nextNode;
			nextNode = curNode->next;
		}

		if(!ret) //if it's a match, remove
		{
			// nodePtr temp = nextNode->next;
			curNode->next = nextNode->next;
			free(nextNode);
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
		nodePtr nextNode = curNode;
		while(nextNode != NULL)
		{
			printf("%s%s", curNode->user->name,
				   (nextNode->next != NULL) ? " " : "");
			curNode = nextNode;
			nextNode = curNode->next;
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

/*  Function: que_create
 *  Parameters: cmp - pointer to a function that returns an int and takes two
 					  void pointers
 *  Purpose: Take in an ordering function and create a queue ADT.
 *  Returns: QueueADT, a pointer to a queueStruct.
 */
// QueueADT que_create(int (*cmp)(const void*a, const void*b))
// {
// 	//allocate space for new queue item and make sure it isn't NULL
// 	QueueADT newQueue = (QueueADT)malloc(sizeof(struct queueStruct));
// 	assert(newQueue != NULL);

// 	//initialize values
// 	newQueue->myNode = NULL;
// 	newQueue->func = cmp;

// 	return newQueue;
// }

/*  Function: que_destroy
 *  Parameters: queue - A QueueADT which may or may not have values in it.
 *  Purpose: Free the memory allocated for the given queue.
 *  Returns: Nothing.
 */
// void que_destroy(QueueADT queue)
// {
// 	assert(queue != NULL);

// 	nodePtr curNode = queue->myNode;
// 	nodePtr nextNode = NULL;
// 	if(curNode != NULL)
// 	{
// 		nextNode = curNode->next;
// 		free(curNode);
// 		curNode = nextNode;
// 	}

// 	free(queue);
// }

/*  Function: que_clear
 *  Parameters: queue - QueueADT which may or may not be empty
 *  Purpose: Empty the given queue and reset all values to NULL or 0.
 *  Returns: Nothing.
 */
// void que_clear(QueueADT queue)
// {
// 	assert(queue != NULL);

// 	nodePtr curNode = queue->myNode;
// 	nodePtr nextNode = NULL;
// 	if(curNode != NULL)
// 	{
// 		nextNode = curNode->next;
// 		free(curNode);
// 		curNode = nextNode;
// 	}
// 	queue->myNode = NULL;
// }

/*  Function: que_insert
 *  Parameters: queue - QueueADT object to insert the given data into
 				data - void pointer to the data we should add to the queue
 *  Purpose: Insert a given piece of data into the given queue in an ordered
 *	fashion.
 *  Returns: Nothing.
 */
// void que_insert(QueueADT queue, void *data)
// {
// 	assert(queue != NULL);

// 	//create new node and add data to it. make sure it's not null too
// 	nodePtr newNode = (nodePtr)malloc(sizeof(struct node));
// 	assert(newNode != NULL);
// 	newNode->contents = data;
// 	newNode->next = NULL;

// 	//node pointers used by both if/else clauses
// 	nodePtr curNode = queue->myNode;
// 	nodePtr nextNode = curNode;

// 	//handle insertion
// 	if(curNode == NULL) //if no elements yet
// 		queue->myNode = newNode;
// 	else if(queue->func == NULL) //if no ordering function given
// 	{		
// 		while(nextNode != NULL)
// 		{
// 			curNode = nextNode;
// 			nextNode = curNode->next;
// 		}

// 		//add new node to end of queue/linked list
// 		curNode->next = newNode;
// 	}
// 	else //if ordering function given
// 	{
// 		nodePtr prevNode = NULL;
// 		int ret = -1;

// 		while(curNode != NULL
// 			  && (ret = (queue->func)(curNode->contents, data)) <= 0
// 			  && nextNode != NULL)
// 		{
// 			prevNode = curNode;
// 			curNode = nextNode;
// 			nextNode = curNode->next;
// 		}

// 		if(prevNode == NULL) //first element inserted higher than others
// 		{
// 			queue->myNode = newNode;
// 			newNode->next = curNode;
// 		}
// 		else if(nextNode == NULL && ret <= 0) //if last element
// 		{
// 			curNode->next = newNode;
// 		}
// 		else //if in the middle
// 		{
// 			newNode->next = curNode;
// 			prevNode->next = newNode;
// 		}
// 	}
// }

/*  Function: que_remove
 *  Parameters: queue - QueueADT object to remove the item from.
 *  Purpose: Remove and return the first (oldest) item in the queue.
 *  Returns: void pointer to the item just removed from the given queue
 */
// void *que_remove(QueueADT queue)
// {
// 	assert(queue != NULL);

// 	//get and replace first element, free old element and return data
// 	if(queue->myNode != NULL)
// 	{
// 		nodePtr tempNode = queue->myNode;
// 		queue->myNode = tempNode->next;
// 		void *tempData = tempNode->contents;
// 		free(tempNode);
// 		return tempData;
// 	}

// 	return NULL; //return null in case we never get inside if statement
// }

/*  Function: que_empty
 *  Parameters: queue - the QueueADT object to be checked.
 *  Purpose: Determine if the given queue is empty or not.
 *  Returns: boolean of true if queue is empty and false if not
 */
// bool que_empty(QueueADT queue)
// {
// 	return(queue->myNode == NULL);
// }
