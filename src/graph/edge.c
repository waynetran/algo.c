#include "edge.h"
#include "node.h"
#include "log.c/log.h"

bool EdgeCreate(Edge ** edgeOut,double weight, Node *nodeFrom, Node *nodeTo){

	if(!NodeIsValid(nodeFrom)|| !NodeIsValid(nodeTo)){
		logError("EdgeCreate() error creating edge. Requirements not met.");
		return false;
	}

	if(nodeFrom == nodeTo){
		logError("Edgecreate() self loops are not allowed.");
		return false;
	}

	*edgeOut = (Edge *) malloc(sizeof(Edge));

	if(*edgeOut){
		(*edgeOut)->weight = weight;

		(*edgeOut)->nodeFrom = nodeFrom;

		(*edgeOut)->nodeTo = nodeTo;

		NodeAddEdge(nodeFrom,*edgeOut);

	}else{
		logError("EdgeCreate() error allocating memory.");
		return false;
	}

	return true;
}

void EdgeDestroy(Edge **edgeRef){
	if(*edgeRef == NULL){
		logDebug("Could not free edge.  Edge was previously destroyed.");
		return;
	}

	if(EdgeIsConnected(*edgeRef)){
		logTrace("Edge destroy called on connected edge.  Attempting to disconnect.");
		NodeRemoveEdge((*edgeRef)->nodeFrom,*edgeRef);
		(*edgeRef)->nodeFrom = NULL;
		(*edgeRef)->nodeTo = NULL;
	}

	free(*edgeRef);
	(*edgeRef) = NULL;
	edgeRef = NULL;
}


void EdgeRemoveNode(Edge *edge, Node *node){

	if(!edge || !node){
		return;
	}

	if(edge->nodeFrom == node){
		edge->nodeFrom = NULL;
	}

	if(edge->nodeTo == node){
		edge->nodeTo = NULL;
	}


}

bool EdgeIsConnected(Edge *edge){
	if(!edge)
		return false;


	if(NodeIsValid(edge->nodeFrom) || NodeIsValid(edge->nodeTo)){
		return true;
	}

	return false;
}
