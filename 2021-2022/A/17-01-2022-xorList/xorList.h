#pragma once


typedef struct node_t {
    short value;
    struct node_t *xpn;
} node_t;

node_t *add(node_t *head, short val);
int containsIter(node_t *head, short val);
int contains(node_t *head, short val);

/*
    a =         101011110
    b =         010010111
    c = a ^ b = 111001001
    c ^ a == b =010010111
    c ^ b == a =101011110

    0 ^ 1 ^ 1 = 0
    0 ^ 0 ^ 0 = 0
    1 ^ 0 ^ 0 = 1
    1 ^ 1 ^ 1 = 1
*/
