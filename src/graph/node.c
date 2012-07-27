#include <stdio.h>
#include <string.h>
#include <log.c/log.h>
#include "node.h"
#include "edge.h"


/*private*/
bool NodeInit(Node *node, void *data);

bool NodeCreate(Node **nodeOut, void *data){

	*nodeOut = (Node *) malloc(sizeof(Node));

	if(*nodeOut != NULL){
		return NodeInit(*nodeOut,data);
	}else{
		logError("NodeCreate() error allocating memory.");
		return false;
	}

	return true;
}

bool NodeInit(Node *node, void *data){

	if(node == NULL){
		return false;
	}

	memset(node,0,sizeof(Node));

	ListCreate(&(node->edges));
	NodeSetData(node, data);

	if(!NodeIsValid(node)){
		NodeDestroy(&node);
		return false;
	}

	return true;
}



void NodeDestroy(Node **nodeRef){
	if(*nodeRef==NULL){
		return;
	}

	NodeClearEdges(*nodeRef);
	free((*nodeRef)->edges);
	//free((*nodeRef)->data);
	free(*nodeRef);
	(*nodeRef) = NULL;
	nodeRef = NULL;

}


const char* NodeToString(Node *node){
	if(!node){
		return "NULL";
	}

	if(node->data == NULL){
		return "Node(NULL)";
	}

	char *buffer = malloc(MAXLENGTH);
	snprintf(buffer,MAXLENGTH,"Node(%s)",(char *)node->data);

	ListNode *current= node->edges->head;
	size_t length = node->edges->size;

	if(length > 0){
		strncat(buffer, ": ", 3);
	}else{
		return buffer;
	}

	size_t i = 0;

	while(current){
		Edge *edge = (Edge*) current->data;
		if(EdgeIsConnected(edge) && NodeIsValid(edge->nodeTo)){
			char * str = (char *)edge->nodeTo->data;
			strncat(buffer, str, strlen(str)+1);
			if(i<length-1)
				strncat(buffer, ", ", 3);
		}
		current = ListNext(current);
		i++;
	}


	return buffer;

}


size_t NodeGetNearestNeighbor(Node *node, Node **nearestOut){
	size_t length = node->edges->size;
	*nearestOut = NULL;

	if(length <= 0){
		return 0;
	}


	ListNode *min = ListMin(node->edges);

	if(!min)
		return 0;

	Edge *edge = (Edge*)min->data;
	if(!edge){
		logError("NodeGetNearestNeighbor() found null edge.");
		return 0;
	}

	if(!EdgeIsConnected(edge)){
		logError("NodeGetNearestNeighbor() found unconnected edge.");
		return 0;
	}

	Node *nodeTo = edge->nodeTo;
	if(!nodeTo){
		logError("NodeGetNearestNeighbor() found unconnected edge.");
		return 0;
	}

	//Return the node
	*nearestOut = nodeTo;
	return edge->weight;

}

void NodeSetData(Node *node, void *data){

	if(!node){
		return;
	}


	//if(node->data){
	//	free(node->data);
	//}


	node->data = data;
	//node->data = malloc(size);
	//memcpy(node->data, data, size);
	//node->dataSize = size;

}

void NodeAddEdge(Node *node, Edge *edge){
	if(!NodeIsValid(node) || !edge){
		return;
	}
	ListNode *lnode = NULL;
	ListNodeCreate(&lnode,"",(void*)edge,edge->weight);
	ListInsert(node->edges,lnode);
}


Edge * NodeConnectTo(Node *nodeFrom, Node *nodeTo, double weight){
	Edge *edge = NULL;
	if(EdgeCreate(&edge,weight, nodeFrom, nodeTo)){
		logDebug("NodeConnectTo() Created edge:");
		logDebug(NodeToString(nodeFrom));
		logDebug(NodeToString(nodeTo));
	}
	return edge;
}

Edge *NodeGetEdge(Node *nodeFrom, Node *nodeTo){
	if(!NodeIsValid(nodeFrom) || !NodeIsValid(nodeTo)  ){
		return NULL ;
	}

	ListNode *current= nodeFrom->edges->head;

	while(current){
		Edge *edge = (Edge*) current->data;

		if(!EdgeIsConnected(edge)){
			logError("found unconneted edge in node.");
			current = ListNext(current);
			continue;
		}

		if(EdgeIsConnected(edge) && edge->nodeTo == nodeTo){
			return edge;
		}

		current = ListNext(current);
	}

	return NULL;
}


size_t NodeNumEdges(Node *node){
	if(!NodeIsValid(node)){
		return 0;
	}

	return node->edges->size;

}


void NodeClearEdges(Node *node){
	if(!NodeIsValid(node)){
		return;
	}

	ListNode *current = node->edges->head;
	while(current){
		Edge *edge = (Edge*) current->data;
		if(edge){
			//NodeRemoveEdge(node,edge);
			ListRemove(node->edges,current);
			EdgeRemoveNode(edge,node);
			EdgeDestroy(&edge);
			current->data = NULL;
		}
		ListNode *prev = current;
		current = ListNext(current);
		ListRemove(node->edges, prev);
		ListNodeDestroy(&prev);
	}
}


void NodeRemoveEdge(Node *node, Edge *edge){
	if(!NodeIsValid(node) || !EdgeIsConnected(edge) ){
		return;
	}

	if(node->edges->size <= 0  ){
		return;
	}

	ListNode *current = node->edges->head;
	while(current){
		Edge *e = (Edge*) current->data;
		if(e == edge){
			//NodeRemoveEdge(node,edge);
			ListRemove(node->edges,current);
			EdgeRemoveNode(edge,node);
			EdgeDestroy(&edge);
			current->data = NULL;
			ListNode *prev = current;
			current = ListNext(current);
			ListRemove(node->edges, prev);
			ListNodeDestroy(&prev);
			return;
		}

		current = ListNext(current);

	}

}


bool NodeIsUnconnected(Node *node){
	if(!NodeIsValid(node) || node->edges->size <= 0)
		return false;

	return true;
}

bool NodeIsConnectedTo(Node *nodeFrom, Node *nodeTo){
	Edge *edge = NodeGetEdge(nodeFrom,nodeTo);
	return EdgeIsConnected(edge);
}


bool NodeIsValid(Node *node){
	if(!node){
		return false;
	}

	if(node->edges == NULL){
		return false;
	}

	return true;
}

bool NodeIsSameObject(Node *node1, Node *node2){
	if(!node1){
		logWarn("NodeIsSameObject() node1 is NULL.");
		return false;
	}

	if(!node2){
		logWarn("NodeIsSameObject() node2 is NULL.");
		return false;
	}

	if(node1 == node2){
		return true;
	}

	return false;

}
