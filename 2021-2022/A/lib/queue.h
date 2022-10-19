#include <stdio.h>
#include <stdlib.h>
#include"graph.h"
#define char_t unsigned char

typedef struct node_t{
    struct node_t *prev, *next;
    struct graph_node_t *data;
    char_t priority;
} node_t;

typedef struct list_t{
    node_t *head;
    node_t *tail;
    size_t size;
} list_t;

list_t *init(){
    list_t *l = (list_t*)malloc(sizeof(list_t));

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return l;
}

struct graph_node_t *front(list_t list){
    return list.head->data;
}
char back(list_t list){
    return list.tail->data;
}

struct graph_node_t * push(list_t* list, struct graph_node_t *value, char_t priority){
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->priority = priority;
    
    new_node->next = list->head;
    new_node->prev = NULL;

    if (list->head != NULL)
        list->head->prev = new_node;
    else
        list->tail = new_node;
    
    list->head = new_node;
    ++list->size;
    return new_node->data;
}

char dpop(list_t* list){
    if (list->size == 0)
        return 0;

    char temp = back(*list);

    node_t* old_node = list->tail;
    list->tail = old_node->prev;
    list->tail->next = NULL;

    free(old_node);
    --list->size;
    return temp;
}

void ppop(list_t* list){
    if (list->size == 0)
        return;
    
    node_t *current = list->head;
    node_t *max_priority = list->head;
    for(int i = 0; i < list->size; ++i){
        if(max_priority->priority > current->priority){
            max_priority = current;
        }
        current = current->next;
    }

    if(max_priority->prev == NULL){
        list->head = max_priority->next;
        list->head->prev = NULL;
    } else if (max_priority->next == NULL){
        list->tail = max_priority->prev;
        list->tail->next = NULL;
    } else {
        max_priority->prev->next = max_priority->next;
        max_priority->next->prev = max_priority->prev;
    }
    
    --(list->size);
    free(max_priority);
    max_priority = NULL;
}

struct graph_node_t *peek(list_t* list){
    if (list->size == 0)
        return NULL;
    
    node_t *current = list->head;
    node_t *max_priority = list->head;
    for(int i = 0; i < list->size; ++i){
        if(max_priority->priority > current->priority){
            max_priority = current;
        }
        current = current->next;
    }

    return max_priority->data;
}

void print_list(list_t list){
    node_t *c_node = list.head;
    while(c_node != NULL){
        printf("Data: %d\n", c_node->data);
        printf("Priority: %d\n", c_node->priority);

        c_node = c_node->next;
    }
    printf("\n");
}

list_t *destroy(list_t *list){
    node_t *c_node = list->head;
    while(c_node->next != NULL){
        c_node = c_node->next;
        free(c_node->prev);
    }
    free(c_node);
    free(list);

    return NULL;
}

int main(){
    list_t* list = init();
    push(list, 1, 1);
    push(list, 2, 1);
    push(list, 4, 2);
    push(list, 5, 5);
    print_list(*list);
    ppop(list);
    print_list(*list);
    printf("\nPeek: %d\n", peek(list));

    destroy(list);
    return 0;
}