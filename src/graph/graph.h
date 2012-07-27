#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H
#include <stdlib.h>
#include "node.h"
#include "edge.h"
#include "list/list.h"

typedef struct {
	List *nodes;
	List *edges;
} Graph;

bool GraphCreate(Graph **graphOut);
void GraphDestroy(Graph **graphRef);

/* Initializes the graphRef with adjacency matrix.
 * data is an array of void* pointers for each node
 * numData is the size of the data array
 * adjacencyMatrix is a flattened square matrix of edge weights between vertices.
 *		- n rows * n cols = numData^2 = array size
 *		- row index is the fromNode, and col index is the toNode for the edge.
 *		- if weight = 0, there is no connection. Weights can be negative.
 **/
bool GraphInit(Graph *graph,
			   void *data[],
			   size_t numData,
			   double adjMatrix[]);

const char * GraphToString(Graph *graph);

bool GraphIsDestroyed(Graph *graph);
	
#endif
