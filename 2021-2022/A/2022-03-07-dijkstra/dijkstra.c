#include"../lib/graph.h"


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
