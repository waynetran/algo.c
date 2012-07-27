#include <log.c/log.h>
#include "list/list.h"
#include "list/listnode.h"

void ListCreate(List **listRef){
	*listRef = (List *) malloc(sizeof(List));

	if(*listRef == NULL){
		logError("ListCreate() out of memory");
		return;
	}

	memset(*listRef,0,sizeof(List));
}

void ListDestroy(List **listRef){
	List *list = *listRef;
	if(!list){
		return;
	}

	ListNode *current = list->head;
	while(current){

		/*We need previous because ListNodeDestroy will set
		  our current pointer to NULL when it's done*/
		ListNode *current2 = current;
		ListNodeDestroy(&current);
		current = ListNext(current2);
	}

	free(list);
	*listRef = NULL;
}

bool ListInsert(List *list, ListNode *node){
	if(!list){
		logError("ListInsert() list is null");
		return false;
	}

	if(!node){
		logError("ListInsert() node is null");
		return false;
	}

	if(list->size < 0){
		logError("ListInsert() size < 0");
		return false;
	}

	if(list->size == 0){
		list->head = node;
		list->tail = node;
		list->size++;
		return true;
	}

	if(!(list->head && list->tail)){
		logError("ListInsert() invalid list.");
		return false;
	}


	if(list->size == 1){
		if(node->weight >= list->head->weight){
			node->prev = list->head;
			list->head->next = node;
			list->tail = node;
		}else{
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		list->size++;
		return true;
	}


	/*If the weights are equal, we append the new node*/
	ListNode *current = list->head;
	while(current){
		if((node->weight < current->weight)){
			break;
		}
		current = current->next;
	}

	if(!current){
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}else{

		ListNode *prev= current->prev;
		if(prev){
			prev->next = node;
			node->prev = prev;
		}else{
			list->head = node;
		}

		current->prev = node;
		node->next = current;

	}

	list->size++;
	return true;

}

bool ListRemove(List *list, ListNode *node){
	if(!list){
		logWarn("ListRemove() list is null");
		return false;
	}

	if(!node){
		logWarn("ListRemove() node is null");
		return false;
	}

	if(list->size <= 0){
		logWarn("ListRemove() size < 0");
		return false;
	}

	if(list->size == 1){
		list->head = NULL;
		list->tail = NULL;
		list->size = 0;
		return true;
	}


	if(node == list->head){
		list->head = list->head->next;
		list->head->prev = NULL;
		node->next = NULL;
		if(node->prev){
			logWarn("ListRemove() list->head's prev was not NULL.  Setting to NULL.");
			node->prev = NULL;
		}
		list->size--;
		return true;
	}

	if(node == list->tail){
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		node->prev = NULL;
		if(node->next){
			logWarn("ListRemove() list->tail's next was not NULL. Setting to NULL.");
			node->next = NULL;
		}
		list->size--;
		return true;
	}


	ListNode *current = list->head;
	bool found = false;
	while(current){
		if(current == node){
			found = true;
			break;
		}
		current = ListNext(current);
	}

	if(found){
		ListNode *prev = node->prev;
		ListNode *next = node->next;
		prev->next = next;
		next->prev = prev;
		list->size--;
		return true;
	}

	return false;
}

ListNode *ListNext(ListNode *node){
	if(!node)
		return NULL;

	return node->next;
}

ListNode *ListPrev(ListNode *node){
	if(!node)
		return NULL;

	return node->prev;
}


ListNode *ListMax(List *list){
	if(!list || list->size == 0){
		return NULL;
	}

	return list->tail;

}

ListNode *ListMin(List *list){
	if(!list || list->size == 0){
		return NULL;
	}

	return list->head;
}

char *ListToString(List *list){

	if(!list || !(list->head)){
		return "List:{}";
	}

	char *buffer = malloc(MAXLENGTH);
	snprintf(buffer,MAXLENGTH,"List: { \n size:%d,\n head:%s,\n tail:%s,\n nodes: [\n",
			 list->size,
			 ListNodeToString(list->head),
			 ListNodeToString(list->tail)
			 );

	ListNode *node = list->head;

	while(node){
		char *nodeString = ListNodeToString(node);
		strncat(buffer,nodeString, strlen(nodeString) + 1);
		if(node->next)
			strncat(buffer, ",\n", 3);
		node = node->next;
	}
	strncat(buffer, "\n]", 3);

	return buffer;
}
