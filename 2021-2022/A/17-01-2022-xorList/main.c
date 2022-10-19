#include<stdio.h>
#include"xorList.h"


int main () {
    node_t *head = NULL;
    head = add(head, 20);
    head = add(head, 31);
    head = add(head, 1);
    head = add(head, -35);
    
    printf("%d", containsIter(head, 3));
    printf("%d", containsIter(head, 31));
    
    return 0;
}


