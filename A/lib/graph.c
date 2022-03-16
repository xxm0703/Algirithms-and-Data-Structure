#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "queue.h"

struct graph_node_t* init_graph_node(int value);


void add_node(struct graph_node_t* start, int new_value, int parent_value);

void print_node(struct graph_node_t* node) {
    printf("value=%d item_count=%d visited=%d items=",
           node->value, node->item_count, node->visited
    );
    for(int i = 0; i < node->item_count; i++) {
        printf("%d,",node->items[i]->value);
    }
}

int bfs(struct graph_node_t *start, struct graph_node_t *end);
struct graph_node_t* find_node(struct graph_node_t* start, int value);


struct graph_node_t* init_graph_node(int value)
{
    struct graph_node_t* new_node = (struct graph_node_t*)malloc(sizeof(struct graph_node_t));
    new_node->value = value;
    new_node->items = NULL;
    new_node->item_count = 0;
    new_node->visited = 0;
    return new_node;
}

unsigned short dijkstra(struct graph_node_t *s, struct graph_node_t *e) {
    size_t size = greatestVal(s) + 1;
    unsigned int pathsLen[size];
    list_t *l = init();

    for (size_t i = 0; i < size; i++) {
        pathsLen[i] = -1;
    }
    push(l, s, 0);   

    while (l->size) {
        struct graph_node_t *node = peek(l);
        ppop(l);

        for (size_t i = 0; i < node->item_count; i++) {
            unsigned int path = pathsLen[node->value] + node->weights[i];
            if (path < pathsLen[node->items[i]->value]); {
                pathsLen[node->items[i]->value] = path;
                push(l, node->items[i], path);
            }
        }

    }
    
    return pathsLen[e->value];
}

void connect_nodes(struct graph_node_t* a, struct graph_node_t* b, unsigned short weight) {
    if (a == NULL || b == NULL)
        return;
        
    a->items = (struct graph_node_t**)realloc(a->items, (1 + a->item_count) * sizeof(struct graph_node_t*));
    a->weights[a->item_count] = weight;
    a->items[a->item_count++] = b;
}

struct graph_node_t* find_node(struct graph_node_t* start, int value)
{
    if(start->value == value)
        return start;

    start->visited = 1;

    for(int i = 0; i < start->item_count; i++)
    {
        if(start->items[i]->visited == 1)
            continue;

        struct graph_node_t* temp = find_node(start->items[i], value);
        if(temp != NULL)
        {
            start->visited = 0;
            return temp;
        }
    }

    start->visited = 0;
    return NULL;
}

void add_node(struct graph_node_t* start, int new_value, int parent_value)
{
    struct graph_node_t *temp = find_node(start, parent_value);
    struct graph_node_t *new_node = init_graph_node(new_value);
    connect_nodes(temp, new_node, 1);
}

int hasPath(struct graph_node_t *start, struct graph_node_t *end){
    start->visited = 1;
    if(start == end)
    {
        start->visited = 0;
        return 1;
    }
    for(int i = 0; i < start->item_count; i++)
    {      
        if(!start->items[i]->visited && hasPath(start->items[i], end))
        {
            start->visited = 0;
            return 1;
        }
    }
    start->visited = 0;
    return 0;
}

int greatestVal(struct graph_node_t *start) {
    start->visited = 1;
    int temp = start->value;

    for(int i = 0; i < start->item_count; i++) {      
        if(!start->items[i]->visited) {
            int val = greatestVal(start->items[i]);
            if (val > temp)
                temp = val;
        }
    }
    start->visited = 0;
    return temp;
}

int bfs(struct graph_node_t *start, struct graph_node_t *end)
{
    if(!start || !end)
        return 0;
      
    que queue;
    queue.push = 0;
    queue.pop = 0;

    queue.arr[queue.push++] = start;
    start->visited = 1;
    
    
    while(queue.push - queue.pop > 0) {
    	struct graph_node_t *temp = queue.arr[queue.pop];
        
	if(end == queue.arr[queue.pop])
            return 1;
            
        for(int i = 0; i < temp->item_count; i++)
        {
            if(temp->items[i]->visited == 0) {
                queue.arr[queue.push++] = temp->items[i];
            	temp->items[i]->visited = 1;
	    }
        }
        queue.pop++;
    }
    
    return 0;
}


