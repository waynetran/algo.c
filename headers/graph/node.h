#ifndef ALGORITHMS_NODE_H
#define ALGORITHMS_NODE_H
#include "types.h"
#include "list/list.h"
#include "list/listnode.h"

struct Edge;

/*It is up to the you to manage "data"*/
struct Node{
	void * data;
	List *edges;
};

/*Creates new node with a copy of data*/
bool NodeCreate(Node **nodeOut, void *data);

/*Destroys node, it's data and sets to NULL*/
void NodeDestroy(Node **nodeRef);

/*Returns a new string representation of the node.  Needs to be freed*/
const char *NodeToString(Node *node);

/* node is a valid node.
 * nearestOut returns a reference to the first nearest neighbor,
 *            will be a reference to a NULL pointer if there are no neighbors
 * returns the length of the edge.
 */
size_t NodeGetNearestNeighbor(Node *node, Node **nearestOut);

void NodeSetData(Node *node, void *data);

void NodeAddEdge(Node *node, Edge *edge);

Edge *NodeConnectTo(Node *nodeFrom, Node *nodeTo, double weight);

Edge *NodeGetEdge(Node *nodeFrom, Node *nodeTo);

size_t NodeNumEdges(Node *node);

void NodeClearEdges(Node *node);

void NodeRemoveEdge(Node *node, Edge *edge);

bool NodeIsUnconnected(Node *node);
bool NodeIsConnectedTo(Node *nodeFrom, Node *nodeTo);
bool NodeIsValid(Node *node);
bool NodeIsSameObject(Node *node1, Node *node2);




#endif
