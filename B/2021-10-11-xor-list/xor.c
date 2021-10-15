node_t *initList() {
    node_t *head = (node_t *)calloc(1, sizeof(node_t));    
    return head;
}


//e1
//e2 <-> e1
void listPushFront(node_t **ls, char val) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->val = val;
    new_node->xpn = (size_t)*ls;
    
    (*ls)->xpn ^= (size_t)new_node;
    *ls = new_node;
}

void listInsert(node_t *ls, int ix, char val) {
    int i = 0;
    node_t *prev = NULL, *next;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->val = val;
    
    for(node_t *ptr = ls; ptr; ) {
        if(i == ix) {
            new_node->xpn = (size_t)ptr ^ (size_t)next;
            
            ptr->xpn = (size_t)prev ^ (size_t)new_node;
            node_t *next2 = (size_t)ptr ^ (size_t)next;
            
            next->xpn = (size_t)next2 ^ (size_t)new_node;            
        }
        

        next = (node_t*)(ptr->xpn ^ (size_t)prev);
        prev = ptr;        

        ptr = next;
        i++;
    }
}
