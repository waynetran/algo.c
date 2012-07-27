#include "graph_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <log.c/log.h>
#include "node.h"
#include "edge.h"
#include "types.h"
#include "graph.h"
#include "ds.h"

#define MAXDATALENGTH 100

bool graph_test_run(){
	logInfo("ALGO.C Library - Graph Test Suite");
	if(!graph_test_create()){
		return false;
	}

	return true;
}

bool graph_test_create(){
	logInfo("graph_test_create...");

	Graph *graph = NULL;

	CreateTestGraph1(&graph);

	if(GraphIsDestroyed(graph)){
		logError("fail - CreateTestGraph1() returned null.");
		return false;
	}

	logDebug(GraphToString(graph));

	GraphDestroy(&graph);
	if(!GraphIsDestroyed(graph)){
		logError("fail - GraphIsDestroyed() was not successful.");
		return false;
	}

	logInfo("success.");
	return true;
}


bool CreateTestGraph1(Graph **graphOut){
	GraphCreate(graphOut);

	if(GraphIsDestroyed(*graphOut)){
		logError("fail - CreateTestGraph1() - GraphCreate() returned null.");
		return false;
	}

	size_t numNodes=5;

	/* Create node data */
	char *nodesValues[numNodes];

	for (int i=0; i<numNodes; i++){
		nodesValues[i] = malloc(MAXDATALENGTH);
		snprintf(nodesValues[i],MAXDATALENGTH,"node %d",i);
	}

	/* Create connections with weights. 0 is unconnected.
	 * 0 is connected to 1, 4
	 * 1 is connected to 0, 2, 3
	 * 2 is connected to 1, 3
	 * 3 is connected to 1 ,2 ,4
	 * 4 is connected to 0, 3
	 */

	double adjMatrix [] ={
		0.0, 1.0, 0.0, 0.0, 4.0,
		1.0, 0.0, 5.0, 1.0, 0.0,
		0.0, 5.0, 0.0, 2.0, 0.0,
		0.0, 1.0, 2.0, 0.0, 1.0,
		4.0, 0.0, 0.0, 1.0, 0.0
	};


	if(!GraphInit(*graphOut,(void**) nodesValues, numNodes, adjMatrix)){
		logError("fail - CreateTestGraph1() - GraphInit() was not successful.");
		return false;
	}

	/*
	char *expected =
			"Graph(5):\n"
			"Node(node 4): node 3, node 0\n"
			"Node(node 3): node 4, node 1, node 2\n"
			"Node(node 2): node 3, node 1\n"
			"Node(node 1): node 3, node 0, node 2\n"
			"Node(node 0): node 1, node 4\n";

	const char *result = GraphToString(*graphOut);

	if(strncmp(expected,result,strlen(expected)) != 0){
		logError("fail - GraphToString() did not return expected output: \nexpected:%s\nresult:%s\n",expected,result);
		return false;
	}


	free(result);

	logInfo(ListToString((*graphOut)->edges));
	*/

	return true;
}

