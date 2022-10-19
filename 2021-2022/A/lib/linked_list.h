#ifndef __LINKED_H
#define __LINKED_H

typedef struct node_t {
	char data;
	struct node_t *next;
	struct node_t *prev;
} node_t;

typedef struct list_t {
	node_t *head;
	node_t *tail;
	unsigned int size;
} list_t;

list_t *init_list();
void destroy_list(list_t *);

char push(list_t *list, char value);
char pop(list_t *list);

char rpush(list_t *list, char value);
char rpop(list_t *list);

char front(list_t list);
char back(list_t list);

void printList(list_t list);
unsigned int size(list_t);

list_t *reverse(list_t *);

#endif
