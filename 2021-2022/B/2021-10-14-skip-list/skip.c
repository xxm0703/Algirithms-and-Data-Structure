#include<stdio.h>
#include<stdlib.h>
#define MAX_LEVEL 2

typedef struct node_t {
	int key, value;
	struct node_t **next;
} node_t;


node_t *init_list() {
	node_t *head = (node_t *)malloc(sizeof(node_t));
	head->next = (node_t **)calloc(sizeof(node_t *), MAX_LEVEL);
	return head;
}

void insert_update(node_t *head, int key, int value) {
	node_t *current = head;
	node_t *update[MAX_LEVEL];

	for (int i = MAX_LEVEL - 1; i >= 0; --i) {
		while (current->next[i] != NULL && 
			current->next[i]->key < key) 
			current = current->next[i];
		update[i] = current;
	}

	node_t *next = current->next[0];
	if (next != NULL && next->key == key) {
		next->value = value;
		return;
	}
	
	node_t* newNode = (node_t *)malloc(sizeof(node_t));
	newNode->key = key;
	newNode->value = value;
	int level = key % 3 ? 1 : 2;
	newNode->next = (node_t **)calloc(sizeof(node_t *), level);
	for (int i = 0; i < level; ++i) {
		newNode->next[i] = update[i]->next[i];
		update[i]->next[i] = newNode;
	}

}

void print(node_t *head) {
	for (int i = MAX_LEVEL - 1; i >= 0; --i) {
		node_t *current = head;
		while(current->next[i]) {
			current = current->next[i];
			printf("%d ", current->key);
		}
		printf("\n");
	}

}

int main() {
	node_t *head = init_list();
	insert_update(head, 2, 13);
	insert_update(head, 6, 23);
	insert_update(head, 4, 43);
	insert_update(head, 3, 23);
	insert_update(head, 1, 23);
	print(head);
	return 0;
}
