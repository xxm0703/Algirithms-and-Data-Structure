#include"linked_list.h"
#include<stdlib.h>
#include<stdio.h>


list_t *init_list() {
	list_t *l = (list_t *)malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void destroy_list(list_t *list) {
	while(list->head != list->tail) {
		list->head = list->head->next;
		free(list->head->prev);
	}
	free(list->head);
	free(list);
}

char push(list_t *list, char value) {
	node_t *newNode = (node_t *)malloc(sizeof(node_t));
	newNode->data = value;

	newNode->next = list->head;
	newNode->prev = NULL;

	if(list->head != NULL) { 
		list->head->prev = newNode;
	} else {
		list->tail = newNode;
	}

	list->head = newNode;
	list->size++;	

	return value;
}

char pop(list_t *list) {	
	char temp = front(*list);
	
	if (list->size != 0) {
		list->head = list->head->next;
		free(list->head->prev);
		list->head->prev = NULL;
		list->size--;
	}

	return temp; 
}

char rpush(list_t *list, char value) {
	node_t *newNode = (node_t *)malloc(sizeof(node_t));
	newNode->data = value;

	newNode->prev = list->tail;
	newNode->next = NULL;

	if(list->tail != NULL) { 
		list->tail->next = newNode;
	} else {
		list->head = newNode;
	}

	list->tail = newNode;
	list->size++;	

	return value;
}

/* TODO
 Same as pop, just change:	head -> tail
							prev -> next
							next -> prev
*/
char rpop(list_t *list);

char front(list_t list) {
	if (list.size == 0)
		return 0;

	return list.head->data;
}

char back(list_t list) {
		if (list.size == 0)
		return 0;

	return list.tail->data;
}

void printList(list_t list) {
	node_t *currentNode = list.head;	

	while(currentNode != NULL) {
		printf("%d ", (int)currentNode->data);
		currentNode = currentNode->next;
	}

	printf("\n");
}

unsigned int size(list_t list) {
	return list.size;
}

list_t *reverse(list_t *list) {
	if (list->size < 2)
		return list;

	list->tail = list->head;
	node_t *temp, *prevNode = list->head;
	
	list->head = list->head->next;
	prevNode->next = NULL;
	prevNode->prev = list->head;

	while(list->head){
			temp = prevNode;
			prevNode = list->head;
			list->head = list->head->next;
			prevNode->next = temp;
			prevNode->prev = list->head;
	}
	list->head = prevNode;
}



