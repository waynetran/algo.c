#include <stdio.h>
#include <stdlib.h>
#include <log.c/log.h>
#include "graph/node_test.h"
#include "graph/graph_test.h"
#include "list/list_test.h"

int main(int argc, char * argv[])
{
	logInit("algo-test.log");
	logSetFlags(LOGFLAG_ERROR|LOGFLAG_INFO|LOGFLAG_WARN|LOGFLAG_STDOUT);

	logInfo("\n\n----------------------------");
	if(!list_test_run()){
			logError("list test suite failed");
			return 1;
	}

	logInfo("\n\n----------------------------");
	if(!node_test_run()){
		logError("Node test suite failed");
		return 1;
	}

	logInfo("\n\n----------------------------");
	if(!graph_test_run()){
		logError("Graph test suite failed");
		return 1;
	}

	return 0;
}
