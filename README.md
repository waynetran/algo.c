# ALGO.C - A study in data structures and algorithms in C.
This is an ongoing project to compare and experiment with different algorithms.

# Dependencies
https://github.com/waynetran/log.c

# Data Structures
## Graph
### Directed weighted graph. May contain cycles.  Edge weights are > 0.
```C
/* A Graph contains a list of nodes and a list of edges */
typedef struct {
	List *nodes;
	List *edges;
} Graph;

/*A Node contians a list of edges and a generic pointer data.  
  The edges are sorted ascending weights.
*/
struct Node{
	void * data;
	List *edges;
};

/*An Edge has non-zero weight and a pointers to a from and to node.
struct Edge{
	double weight;
	Node *nodeFrom;
	Node *nodeTo;
};

```

## List
### Sorted Linked list implementation
```C
/* Ordered ascending list
 * Sorted by ListNode's weight
 */
struct List{
	ListNode *head;	/*First node.  This is the minimum*/
	ListNode *tail; /*First node.  This is the maximum*/
	size_t size;	/*size of the list*/
};

/* Elements of the list */
struct ListNode{
	char *key; 	/*label for node*/
	void *data; 	/*storing arbitrary data */
	double weight; 	/*used for sorting, default 0*/
	struct ListNode *next;   /*Next element of the list.  NULL Indicates node is a tail.*/
	struct ListNode *prev;   /*Next element of the list.  NULL Indicates node is a head.*/
};

```

# Build and Install

	make && sudo make install

This will build and install into:
* ***/usr/local/include/algo.c ***
* ***/usr/local/lib/libalgo.c.a***

# Contact
Author: Wayne Tran  
Email: wayne@tran.io  
License: MIT  

