#ifndef ALGORITHMS_LISTNODE_H
#define ALGORITHMS_LISTNODE_H
#include "types.h"

/* Elements of the list */
struct ListNode{
	char *key; 	/*label for node*/
	void *data; 	/*storing arbitrary data */
	double weight; 	/*used for sorting, default 0*/
	struct ListNode *next;   /*Next element of the list.  NULL Indicates node is a tail.*/
	struct ListNode *prev;   /*Next element of the list.  NULL Indicates node is a head.*/
};

/* Creates a ListNode
 * Copies the key and data
 */
void ListNodeCreate(ListNode **nodeRef,
				  const char *key,
				  void *data,
				/*  size_t size,*/
				  double weight);


void ListNodeDestroy(ListNode **nodeRef);

/*Returns a new string representation of the node.  Needs to be freed*/
char *ListNodeToString(ListNode *node);

#endif
