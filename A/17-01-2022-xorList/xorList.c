#include"xorList.h"
#include<stdlib.h>
#include<stdint.h>

node_t *xor(node_t *left, node_t *right) {
    return (node_t *)((uintptr_t) left ^ (uintptr_t) right);
}

node_t *add(node_t *head, short val) {
    node_t *el = (node_t *)malloc(sizeof(node_t));
    el->xpn = head;
    el->value = val;
    
    if (head != NULL) {
        head->xpn = xor(head->xpn, el);                
    }
    
    return el;
}

int _contains(node_t *prev, node_t *head, short val) {
    if (head == NULL)   
        return 0;
        
    if (head->value == val)
        return 1;
        
    return _contains(head, xor(prev, head->xpn), val);
}


int contains(node_t *head, short val) {
    return _contains(NULL, head, val);
}


int containsIter(node_t *head, short val) {
    node_t *current = head;
    node_t *prev = NULL;

    while (current != NULL) {
    
        if (current->value == val)
            return 1;
        
        node_t *next = xor(current->xpn, prev);
        prev = current;
        current = next;
    }
    return 0;
}



 
