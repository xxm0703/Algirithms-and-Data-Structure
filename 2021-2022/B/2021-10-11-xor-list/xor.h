#include<stdlib.h>

typedef struct node_t {
    char val;
    //struct node_t *xpn;  // Xor-Previous-Next
    size_t xpn;
} node_t;

node_t *initList();
void listPushFront(node_t *ls, char val);

