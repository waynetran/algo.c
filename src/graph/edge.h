#ifndef ALGORITHMS_EDGE_H
#define ALGORITHMS_EDGE_H
#include <stdlib.h>
#include "types.h"

struct Node;

struct Edge{
	/*char *uuid;*/
	double weight;
	Node *nodeFrom;
	Node *nodeTo;
};

/* Edge Constructor, length must be > 0,
 * and nodeFrom and nodeTo must be not be NULL
 */
bool EdgeCreate(Edge **edgeOut, double weight, Node *nodeFrom, Node *nodeTo);
void EdgeDestroy(Edge **edgeRef);

/*Removes the edge from Node, as well as disconnects the edge's from and to.
 *Edge should be freed if not used again.
 */
void EdgeRemoveNode(Edge *edge, Node *node);
/*char *EdgeGetUUID(Edge **edgeRef);*/

bool EdgeIsDestroyed(Edge *edge);
//bool EdgeIsInitialized(Edge **edgeRef);
bool EdgeIsConnected(Edge *edge);

#endif
