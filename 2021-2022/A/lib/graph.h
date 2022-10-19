#pragma once

struct graph_node_t {
    int value;
    struct graph_node_t** items;
    unsigned short weights[100];
    int item_count;
    char visited;
};

typedef struct queue{
    struct graph_node_t *arr[1000];
    int push;
    int pop;
}que;

struct graph_node_t* init_graph_node(int value);

unsigned short dijkstra(struct graph_node_t *s, struct graph_node_t *e);

void connect_nodes(struct graph_node_t*, struct graph_node_t*, unsigned short);
struct graph_node_t* init_graph_node(int value);

struct graph_node_t *read_from_file(const char *filename){

int bfs(struct graph_node_t *start, struct graph_node_t *end);
struct graph_node_t* find_node(struct graph_node_t* start, int value);

void add_node(struct graph_node_t* start, int new_value, int parent_value);

void print_node(struct graph_node_t* node) {
  printf("value=%d item_count=%d visited=%d items=",
    node->value, node->item_count, node->visited
  );
  for(int i = 0; i < node->item_count; i++) {
    printf("%d,",node->items[i]->value);
  }
  puts("");
}

struct graph_node_t* find_node(struct graph_node_t* start, int value);


