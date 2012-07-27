#ifndef ALGORITHMS_LISTNODE_H
#define ALGORITHMS_LISTNODE_H
#include "types.h"

struct ListNode{
	/*label for node*/
	char *key;
	/*storing arbitrary data */
	void *data;
	/*size in bytes of data*/
	//size_t dataSize;
	/*used for sorting, initial 0*/
	double weight;

	struct ListNode *next;
	struct ListNode *prev;
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
