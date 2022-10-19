#include<stdlib.h>
#include<stdio.h>

struct node_t {
	char data;
	struct node_t *xor_ptr;
};

struct list_t {
	struct node_t *head, *tail;
};

struct list_t *init() {
	struct list_t *l = (struct list_t *)malloc(sizeof(struct list_t));
	l->head = l->tail = NULL;
	return l;
}

int push(struct list_t *l, char data) {
	if (l == NULL)
		return 1;
	struct node_t *newNode = (struct node_t *)malloc(sizeof(struct node_t));
	newNode->xor_ptr = l->head;
	newNode->data = data;
	if (l->head != NULL)
		l->head->xor_ptr ^= newNode;
	else
		l->tail = newNode;
	l->head = newNode;
	return 0;
}

int printData(struct list_t *l) {
	if (l == NULL)
		return 1;
	struct node_t *tempNode = l->tail;
	struct node_t *prevNode = NULL;
	while (tempNode != NULL) {
		printf("%d ", tempNode->data);
		struct node_t *tempPtr = tempNode;
		tempNode = tempNode->xor_ptr ^ prevNode;
		prevNode = tempPtr;
	}
	return 0;
}

int main() {
	return 0;
}
