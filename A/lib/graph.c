#include <stdlib.h>
#include <stdio.h>

struct graph_node_t {
    int value;
    struct graph_node_t** items;
    int item_count;
    char visited;
};

typedef struct queue{
    struct graph_node_t *arr[1000];
    int push;
    int pop;
}que;

struct graph_node_t* init_graph_node(int value);

void connect_nodes(struct graph_node_t* a, struct graph_node_t* b);

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

int main() {
    struct graph_node_t* first = init_graph_node(5);

    add_node(first, 10, 5);
    add_node(first, 12, 5);
    add_node(first, 14, 5);

    add_node(first, 20, 10);
    add_node(first, 30, 20);

    //connect_nodes(first->items[0]->items[0], first);

    add_node(first->items[0]->items[0], 40, 5);

    connect_nodes(first->items[1], first->items[0]->items[0]);

    print_node(first->items[0]->items[0]);
    printf("\n%d ", bfs(first->items[0]->items[0], first));
    return 0;
}

struct graph_node_t* init_graph_node(int value)
{
    struct graph_node_t* new_node = (struct graph_node_t*)malloc(sizeof(struct graph_node_t));
    new_node->value = value;
    new_node->items = NULL;
    new_node->item_count = 0;
    new_node->visited = 0;
    return new_node;
}

void connect_nodes(struct graph_node_t* a, struct graph_node_t* b)
{
    if (a == NULL || b == NULL)
        return;
        
    a->items = (struct graph_node_t**)realloc(a->items, (1 + a->item_count) * sizeof(struct graph_node_t*));
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
    connect_nodes(temp, new_node);
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


