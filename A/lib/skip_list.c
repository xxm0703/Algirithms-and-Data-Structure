#include"skip_list.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void init_list(skip_list_t *list) {
    node_t *head = (node_t *)malloc(sizeof(node_t));
    list->head = head;
    list->size = 0;
    head->key = -1;
    head->value = 0;
    head->next = (node_t **)calloc(sizeof(node_t *), MAX_LEVEL);
    // memset(head->next, 0, MAX_LEVEL);
}

void insert_update(skip_list_t *list, unsigned short key, short value) {
    node_t **update = (node_t **)calloc(sizeof(node_t *), MAX_LEVEL);
    node_t *current = list->head;
    for (int i = MAX_LEVEL - 1; i >= 0; --i) {
        while (current->next[i] != NULL && 
            current->next[i]->key < key)
                current = current->next[i];
        update[i] = current;
    }
    
    node_t *next = current->next[0];
   
    // UPDATE value
    if (next != NULL && next->key == key) {
        current->next[0]->value = value;
        return;
    }
    
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->key = key;
    newNode->value = value;
    int level = (key % 3) ? 1 : 2;
    newNode->next = (node_t **)calloc(sizeof(node_t *), level);
    
    for (int i = 0; i < level; ++i) {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }
    free(update);
    list->size++;

}

void print(skip_list_t *l) {
    for (int i = MAX_LEVEL - 1; i >= 0; --i) {
        node_t *current = l->head;
        while (current->next[i] != NULL) {
                current = current->next[i];
                printf("%d(%d) ", current->value, current->key);
        }
        printf("\n");
    }

} 

void destroy(skip_list_t *l) {
    node_t *current, *next;
    next = l->head;
    
    while (next) {
        current = next;
        next = current->next[0];
        free(current->next);
        free(current);
    }
}

