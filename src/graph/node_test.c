#include <log.c/log.h>
#include "node_test.h"

bool node_test_run(){

	logInfo("ALGO.C Library - Node Test Suite");
	if(!node_test_create()){
		return false;
	}

	if(!node_test_data()){
		return false;
	}

	if(!node_test_add_edge()){
		return false;
	}

	if(!node_test_get_nearest_neighbor()){
		return false;
	}

	return true;
}

bool node_test_create(){
	logInfo("node_test_create...");

	Node *node=NULL;
	NodeCreate(&node,"test");

	if(!node){
		logError("fail - NodeCreate() returned NULL.");
		return false;
	}

	logDebug(NodeToString(node));

	NodeDestroy(&node);

	if(node){
		logError("fail - NodeDestroy() was not successful.");
		return false;
	}


	logInfo("success.");
	return true;
}

bool node_test_data(){
	logInfo("node_test_data...");

	Node *node=NULL;
	NodeCreate(&node,"test");
	if(!NodeIsValid(node)){
		logError("fail - NodeCreate() returned NULL.");
		return false;
	}

	logDebug(NodeToString(node));

	if(strncmp((char *) node->data, "test",5) != 0){
		logError("fail - NodeGetId() does not equal \"test\".");
		return false;
	}

	NodeSetData(node,(void *)"hello world");

	logDebug(NodeToString(node));

	if(strncmp((char *) node->data, "hello world",12) != 0){
		logError("fail - NodeGetId() does not equal \"hello world\".");
		return false;
	}

	NodeDestroy(&node);
	if(node){
		logError("fail - NodeDestroy() was not successful.");
		return false;
	}

	logInfo("success.");
	return true;

}

bool node_test_add_edge(){
	logInfo("node_test_add_edge...");
	Node *node1=NULL;
	NodeCreate(&node1,"node1");
	if(!node1){
		logError("fail - NodeCreate() returned NULL for node1.");
		return false;
	}

	Node *node2 = NULL;
	NodeCreate(&node2, "node2");
	if(!node2){
		logError("fail - NodeCreate() returned NULL for node2.");
		return false;
	}

	Node *node3 = NULL;
	NodeCreate(&node3,"node3");
	if(!node3){
		logError("fail - NodeCreate() returned NULL for node2.");
		return false;
	}

	NodeConnectTo(node1, node2,1.0);
	NodeConnectTo(node1, node3,2.0);

	logDebug(NodeToString(node1));
	logDebug(NodeToString(node2));
	logDebug(NodeToString(node3));

	if(NodeNumEdges(node1) != 2){
		logError("fail - EdgeCreate() wrong number of edges out for node 1.");
		return false;
	}

	if(NodeNumEdges(node2) != 0){
		logError("fail - EdgeCreate() wrong number of edges out for node 2.");
		return false;
	}

	if(NodeNumEdges(node3) != 0){
		logError("fail - EdgeCreate() wrong number of edges out for node 3.");
		return false;
	}

	Edge *edge1_2 = NodeGetEdge(node1, node2);

	if(!edge1_2){
		logError("fail - NodeGetEdge() returned NULL for node 1 to node 2.");
		return false;
	}

	if(edge1_2->weight != 1.0){
		logError("fail - NodeGetEdge() return unexpected value for edge's length.");
		return false;
	}

	if(!NodeIsSameObject(edge1_2->nodeFrom,node1)){
		logError("fail - edge1_2's from node is not node1.");
		return false;
	}

	if(!NodeIsSameObject(edge1_2->nodeTo,node2)){
		logError("fail - edge1_2's from node is not node2.");
		return false;
	}

	NodeDestroy(&node1);
	if(node1){
		logError("fail - NodeDestroy() was not successful for node1.");
		return false;
	}

	NodeDestroy(&node2);
	if(node2){
		logError("fail - NodeDestroy() was not successful for node2.");
		return false;
	}

	logInfo("success.");
	return true;
}

bool node_test_get_nearest_neighbor(){
	logInfo("node_test_get_nearest_neighbor...");
	Node *node1  = NULL;
	NodeCreate(&node1,"node1");
	if(!NodeIsValid(node1)){
		logError("fail - NodeCreate() returned NULL for node1.");
		return false;
	}

	Node *node2 = NULL;
	NodeCreate(&node2,"node2");
	if(!NodeIsValid(node2)){
		logError("fail - NodeCreate() returned NULL for node2.");
		return false;
	}

	Node *node3 = NULL;
	NodeCreate(&node3,"node3");
	if(!NodeIsValid(node3)){
		logError("fail - NodeCreate() returned NULL for node3.");
		return false;
	}

	Node *node4 = NULL;
	NodeCreate(&node4,"node4");
	if(!NodeIsValid(node4)){
		logError("fail - NodeCreate() returned NULL for node4.");
		return false;
	}


	NodeConnectTo(node1, node3,2.0);
	NodeConnectTo(node1, node2,1.0);
	NodeConnectTo(node1, node4,3.0);

	logDebug(NodeToString(node1));
	logDebug(NodeToString(node2));
	logDebug(NodeToString(node3));
	logDebug(NodeToString(node4));

	if(NodeNumEdges(node1) != 3){
		logError("fail - EdgeCreate() wrong number of edges out for node 1.");
		return false;
	}

	if(NodeNumEdges(node2) != 0){
		logError("fail - EdgeCreate() wrong number of edges out for node 2.");
		return false;
	}

	if(NodeNumEdges(node3) != 0){
		logError("fail - EdgeCreate() wrong number of edges out for node 3.");
		return false;
	}

	if(NodeNumEdges(node4) != 0){
		logError("fail - EdgeCreate() wrong number of edges out for node 4.");
		return false;
	}

	Node *nearestNode;
	size_t length = NodeGetNearestNeighbor(node1,&nearestNode);



	if(strncmp((char *)nearestNode->data,"node2",6) != 0){
		logError("fail - NodeGetDataAsString() wrong nearest neighbor for node1.");
		logInfo(NodeToString(nearestNode));
		return false;
	}

	if(length != 1.0){
		logError("fail - NodeGetDataAsString() wrong edge length for nearest neighbor.");

		return false;
	}



	NodeDestroy(&node1);
	if(node1){
		logError("fail - NodeDestroy() was not successful for node1.");
		return false;
	}

	NodeDestroy(&node2);
	if(node2){
		logError("fail - NodeDestroy() was not successful for node2.");
		return false;
	}

	NodeDestroy(&node3);
	if(node3){
		logError("fail - NodeDestroy() was not successful for node3.");
		return false;
	}

	NodeDestroy(&node4);
	if(node4){
		logError("fail - NodeDestroy() was not successful for node4.");
		return false;
	}

	logInfo("success.");
	return true;
}

