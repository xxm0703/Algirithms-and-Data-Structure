#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

typedef struct node_t {
	char data;
	struct node_t *xpn;
} node_t;

void push(node_t **head, char value) {
	node_t *newNode = (node_t *)malloc(sizeof(node_t));
	newNode->data = value;
	newNode->xpn = *head;
	
	if (*head != NULL) {
		(*head)->xpn = (node_t *)((uintptr_t)(*head)->xpn ^ (uintptr_t)newNode);
	}
	*head = newNode; 
}

char get(node_t *head, size_t index) {
	node_t *current, *prev, *next;
	current = head;
	prev = NULL;
	while(index--) {
		next = (node_t *)((uintptr_t)current->xpn ^ (uintptr_t)prev);
		prev = current;
		current = next;
	}
	return current->data;
}
int main() {
	node_t *head = NULL;
	push(&head, 5);
	push(&head, -3);
	push(&head, 1);
	push(&head, -6);
	printf("%d\n", get(head, 0));
	printf("%d\n", get(head, 2));
	return 0;
}

