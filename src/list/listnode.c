#include "list/listnode.h"
#include "log.c/log.h"

void ListNodeCreate(ListNode **nodeRef,
				  const char *key,
				  void *data,
				 /* size_t size,*/
				  double weight){

	*nodeRef = (ListNode *) malloc(sizeof(ListNode));

	if(*nodeRef == NULL){
		logError("ListNodeCreate() out of memory");
		return;
	}

	memset(*nodeRef,0,sizeof(ListNode));

	(*nodeRef)->key = (char *) malloc(strlen(key) + 1);

	if((*nodeRef)->key == NULL){
		logError("ListNodeCreate() out of memory");
		free(*nodeRef);
		*nodeRef = NULL;
		return;
	}

	memcpy((*nodeRef)->key,key,strlen(key) + 1);

	/*
	(*nodeRef)->data = malloc(size);
	if((*nodeRef)->data == NULL){
		logError("ListNodeCreate() out of memory");
		free(*nodeRef);
		*nodeRef = NULL;
		return;
	}


	memcpy((*nodeRef)->data, data, size);
	(*nodeRef)->dataSize = size;
	*/


	(*nodeRef)->data = data;
	(*nodeRef)->weight = weight;


}

char *ListNodeToString(ListNode *node){

	if(!node){
		return "";
	}

	char *buffer = malloc(MAXLENGTH);
	snprintf(buffer,MAXLENGTH,"ListNode {key: %s, data: %p, weight: %f}",
			 node->key,
			 node->data,
			 node->weight
			 );
	return buffer;
}

void ListNodeDestroy(ListNode **nodeRef){
	free((*nodeRef)->key);
	/*free((*nodeRef)->data);*/
	free(*nodeRef);
	*nodeRef = NULL;
}
