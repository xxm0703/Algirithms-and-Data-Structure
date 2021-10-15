#ifndef __SKIP_LIST
#define __SKIP_LIST

#define MAX_LEVEL 2

typedef struct node_t {
    short key;
    short value;
    struct node_t **next;
} node_t;

typedef struct skip_list_t {
    node_t *head;
    unsigned long size;        
} skip_list_t;

void init_list(skip_list_t *);
void insert_update(skip_list_t *, unsigned short key, short value);
void print(skip_list_t *l);
void destroy(skip_list_t *l);

#endif
