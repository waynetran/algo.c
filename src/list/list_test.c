#include "list_test.h"
#include "list.h"
#include "listnode.h"

bool list_test_run(){
	logInfo("ALGO.C Library - List Test Suite");
	if(!list_test_add_remove()){
		return false;
	}

	if(!list_test_equal_weights()){
		return false;
	}

	return true;
}

bool list_test_add_remove(){
	logInfo("list_test_add_remove()...");
	List *list = NULL;
	ListCreate(&list);
	if(!list){
		logError("fail - ListCreate() returned NULL for list.");
	}

	ListNode *node1 = NULL;
	ListNodeCreate(&node1,"node1",NULL,6.0);
	if(!node1){
		logError("fail - ListNodeCreate() returned NULL for node1.");
		return false;
	}

	logDebug(ListNodeToString(node1));

	ListNode *node2 = NULL;
	ListNodeCreate(&node2,"node2",NULL,3.0);
	if(!node2){
		logError("fail - ListNodeCreate() returned NULL for node2.");
		return false;
	}

	ListNode *node3 = NULL;
	ListNodeCreate(&node3,"node3",NULL,8.0);
	if(!node3){
		logError("fail - ListNodeCreate() returned NULL for node3.");
		return false;
	}

	ListNode *node4 = NULL;
	ListNodeCreate(&node4,"node4",NULL,2.0);
	if(!node4){
		logError("fail - ListNodeCreate() returned NULL for node4.");
		return false;
	}

	ListNode *node5 = NULL;
	ListNodeCreate(&node5,"node5",NULL,10.0);
	if(!node5){
		logError("fail - ListNodeCreate() returned NULL for node5.");
		return false;
	}

	if(!ListInsert(list,node1)){
		logError("fail - ListInsert() returned false for node1.");
		return false;
	}
	if(!ListInsert(list,node2)){
		logError("fail - ListInsert() returned false for node2.");
		return false;
	}
	if(!ListInsert(list,node3)){
		logError("fail - ListInsert() returned false for node3.");
		return false;
	}
	if(!ListInsert(list,node4)){
		logError("fail - ListInsert() returned false for node4.");
		return false;
	}
	if(!ListInsert(list,node5)){
		logError("fail - ListInsert() returned false for node5.");
		return false;
	}

	/* should be node4, node2, node1, node3, node5 */
	logDebug(ListToString(list));

	if(ListMin(list) != node4){
		logError("fail - ListMin() did not return node4.");
		return false;
	}

	if(ListMax(list) != node5){
		logError("fail - ListMax() did not return node5.");
		return false;
	}

	if(!ListRemove(list,node1)){
		logError("fail - ListRemove() failed to remove node1.");
		return false;
	}

	ListNodeDestroy(&node1);

	/* should be node4, node2, node3, node5 */
	logDebug("\n\nAfter node1 removal:");
	logDebug(ListToString(list));

	if(!ListRemove(list,node4)){
		logError("fail - ListRemove() failed to remove node4.");
		return false;
	}

	ListNodeDestroy(&node4);

	/* should be node2, node3, node5 */
	logDebug("\n\nAfter node4 removal:");
	logDebug(ListToString(list));

	if(!ListRemove(list,node5)){
		logError("fail - ListRemove() failed to remove node4.");
		return false;
	}

	ListNodeDestroy(&node5);

	/* should be node2, node3 */
	logDebug("\n\nAfter node5 removal:");
	logDebug(ListToString(list));

	if(!ListRemove(list,node2)){
		logError("fail - ListRemove() failed to remove node4.");
		return false;
	}

	ListNodeDestroy(&node2);

	/* should be node3 */
	logDebug("\n\nAfter node2 removal:");
	logDebug(ListToString(list));


	if(!ListRemove(list,node3)){
		logError("fail - ListRemove() failed to remove node4.");
		return false;
	}

	/* should be {} */
	logDebug("\n\nAfter node3 removal:");
	logDebug(ListToString(list));


	logRemoveFlags(LOGFLAG_WARN);

	if(ListRemove(list,node3)){
		logError("fail - ListRemove() returned true for non member.");
		return false;
	}

	logAddFlags(LOGFLAG_WARN);

	ListNodeDestroy(&node3);

	ListDestroy(&list);
	if(list){
		logError("fail - ListDestroy() did not set list to NULL.");
		return false;
	}

	logInfo("success.");
	return true;

}

bool list_test_equal_weights(){
	logInfo("list_test_equal_weights()...");

	List *list = NULL;
	ListCreate(&list);
	if(!list){
		logError("fail - ListCreate() returned NULL for list.");
	}

	ListNode *node = NULL;
	for(int i = 0; i < 3; i++){
		char buff[10];
		snprintf(buff,10,"node%d",i);
		ListNodeCreate(&node,buff,NULL,1.0);
		if(!node){
			logError("fail - ListNodeCreate() returned NULL for node1.");
			return false;
		}
		ListInsert(list,node);
	}

	ListNodeCreate(&node,"node-last",NULL,5.0);
	ListInsert(list,node);

	ListNodeCreate(&node,"node-second-last",NULL,4.0);
	ListInsert(list,node);

	ListNodeCreate(&node,"node-first",NULL,0.1);
	ListInsert(list,node);

	ListNodeCreate(&node,"node-second",NULL,0.2);
	ListInsert(list,node);

	for(int i = 0; i < 3; i++){
		char buff[10];
		snprintf(buff,10,"node%d",i);
		ListNodeCreate(&node,buff,NULL,1.0);
		if(!node){
			logError("fail - ListNodeCreate() returned NULL for node1.");
			return false;
		}
		ListInsert(list,node);
	}

	logDebug(ListToString(list));

	node = list->head;
	char *expectedNode = "node-first";
	double expectedWeight = 0.1;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node-second";
	expectedWeight = 0.2;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node0";
	expectedWeight = 1.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node1";
	expectedWeight = 1.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node2";
	expectedWeight = 1.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node0";
	expectedWeight = 1.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node1";
	expectedWeight = 1.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node2";
	expectedWeight = 1.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node-second-last";
	expectedWeight = 4.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	node = ListNext(node);
	expectedNode = "node-last";
	expectedWeight = 5.0;
	if(strcmp((char *)node->key, expectedNode) != 0 || node->weight != expectedWeight){
		logError("fail - found node: %s, weight %f.  expected: %s, weight %f",
				 (char *)node->key, node->weight, expectedNode, expectedWeight);
		return false;
	}

	ListDestroy(&list);
	if(list){
		logError("fail - ListDestroy() did not set list to NULL.");
		return false;
	}

	logInfo("success.");
	return true;
}
