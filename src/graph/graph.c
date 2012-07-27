#include "graph/graph.h"
#include "log.c/log.h"

bool GraphCreate(Graph **graphOut){

	*graphOut = (Graph *) malloc(sizeof(Graph));

	if(!GraphIsDestroyed(*graphOut)){
		memset(*graphOut ,0,sizeof(Graph));
		ListCreate(&((*graphOut)->nodes));
		if((*graphOut)->nodes == NULL){
			logError("GraphCreate() could not create node list");
			return false;
		}
		ListCreate(&((*graphOut)->edges));
		if((*graphOut)->edges == NULL){
			logError("GraphCreate() could not create edge list");
			return false;
		}

	}else{
		logError("GraphCreate() could not allocate memory for graph");
		return false;
	}

	return true;
}


void GraphDestroy(Graph **graphRef){
	if(GraphIsDestroyed(*graphRef))
		return;

	ListNode *current = (*graphRef)->nodes->head;
	while(current){
		Node *node = (Node*) current->data;
		ListNode *prev = current;

		if(node){
			ListRemove(node->edges, prev);
			NodeDestroy(&node);
			current->data = NULL;

		}
		ListRemove((*graphRef)->nodes,current);
		ListNodeDestroy(&prev);
		current = ListNext(current);
	}
	ListDestroy(&((*graphRef)->nodes));

	//Assume the edges were destroyed when a Node was destroyed
	current = (*graphRef)->edges->head;
	while(current){
		ListNode *prev = current;
		ListRemove((*graphRef)->edges, prev);
		ListNodeDestroy(&prev);
		current = ListNext(current);
	}

	ListDestroy(&((*graphRef)->edges));
	free(*graphRef);
	(*graphRef) = NULL;
	graphRef = NULL;
}

bool GraphInit(Graph *graph, void *data[], size_t numData, double adjMatrix[]){
	if(GraphIsDestroyed(graph))
		return false;

	logDebug("GraphInit(): ");
	/* Create Nodes from data array */
	Node *nodes[numData];
	for (size_t i = 0; i < numData; i++){
		Node *node=NULL;
		if(!NodeCreate(&node, data[i])){
			logError("GraphInit() could not create node");
			return false;
		}
		nodes[i]=node;
		/*logDebug(NodeToString(node));*/
		ListNode *lnode=NULL;
		ListNodeCreate(&lnode,(char *) node->data,(void*) node, 1.0);
		ListInsert(graph->nodes,lnode);
	}

	/* Create connections from adjacencyMatrix */
	size_t row = 0;
	size_t col = 0;

	for (size_t i=0; i < numData * numData; i++){
		col= i % numData;
		row = i / numData;
		logTrace("row %d, col %d: %f \n",row,col,adjMatrix[i]);

		/* Create connection if the weight is not 0 */
		if(adjMatrix[i] != 0.0){
			logTrace("Connection found (row: %d, node: %s) --> (col: %d, node: %s) with weight: %f",
					row,
					NodeToString(nodes[row]),
					col,
					NodeToString(nodes[col]),
					adjMatrix[i]
					);

			Edge *edge = NodeConnectTo(nodes[row],nodes[col], adjMatrix[i]);
			if(edge){
				char edgeLabel[MAXLENGTH];
				snprintf(edgeLabel,MAXLENGTH, "%s -> %s",(char*)nodes[row]->data, (char*)nodes[col]->data);
				ListNode *lnode=NULL;
				ListNodeCreate(&lnode,edgeLabel,(void*) edge, adjMatrix[i]);
				ListInsert(graph->edges,lnode);
				logTrace("Edge created.  size: %d",graph->edges->size);
				logTrace("Current Edge List:\n %s\n\n", ListToString(graph->edges));
			}

		}

	}

	logTrace("Graph initialized: %s",GraphToString(graph));

	return true;
}

const char * GraphToString(Graph *graph){
	if(GraphIsDestroyed(graph)){
		return "Graph(destroyed)";
	}

	char *buffer = malloc(MAXLENGTH * sizeof(char));
	snprintf(buffer,MAXLENGTH,"\nGraph():\n\nNode List:\n%s",ListToString(graph->nodes));
	strncat(buffer, "\n\nEdge List:\n",14);
	const char *edgeString = ListToString(graph->edges);
	strncat(buffer,edgeString,strlen(edgeString) +1);
/*
	ListNode *current = graph->nodes->head;

	Node *node = NULL;

	while(current){
		node = (Node*)current->data;
		if(NodeIsValid(node)){
			const char *nodeString = NodeToString(node);
			strncat(buffer,nodeString , strlen(nodeString));
			strncat(buffer, "\n", 2);
		}
		current = ListNext(current);
	}


	snprintf(buffer,MAXLENGTH,"\nEdges with size: %d \n",graph->nodes->size);
	current = graph->edges->head;
	Edge *edge = NULL;

	while(current){
		node = (Edge*)current->data;
		if(NodeIsValid(node)){
			const char *nodeString = NodeToString(node);
			strncat(buffer,nodeString , strlen(nodeString));
			strncat(buffer, "\n", 2);
		}
		current = ListNext(current);
	}
	*/
	return buffer;

}


bool GraphIsDestroyed(Graph *graph){
	if(graph == NULL){
		return true;
	}

	if(graph->nodes == NULL){
		logWarn("GraphIsDestroyed() graph has null nodes list.");
		return true;
	}

	if(graph->edges == NULL){
		logWarn("GraphIsDestroyed() graph has null edges list.");
		return true;
	}

	return false;
}
