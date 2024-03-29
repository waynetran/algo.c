#ifndef LIST_H
#define LIST_H
#include "types.h"
#include "listnode.h"

/* Ordered ascending list
 * Sorted by ListNode's weight
 */
struct List{
	ListNode *head;	/*First node.  This is the minimum*/
	ListNode *tail; /*First node.  This is the maximum*/
	size_t size;	/*size of the list*/
};

void ListCreate(List **listRef);
void ListDestroy(List **listRef);

/* Inserts node into list
 * Takes ownership of node until remove is called
 **/
bool ListInsert(List *list, ListNode *node);
bool ListRemove(List *list, ListNode *node);

ListNode *ListNext(ListNode *node);
ListNode *ListPrev(ListNode *node);


ListNode *ListMax(List *list);
ListNode *ListMin(List *list);

char *ListToString(List *list);

#endif // LIST_H
