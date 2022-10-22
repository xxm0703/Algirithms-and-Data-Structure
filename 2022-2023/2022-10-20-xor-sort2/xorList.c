#include<stdlib.h>
#include<stdio.h>

struct node_t {
	char data;
	struct node_t *xor_ptr;
};

struct list_t {
	struct node_t *head, *tail;
};

struct list_t *init() {
	struct list_t *l = (struct list_t *)malloc(sizeof(struct list_t));
	l->head = l->tail = NULL;
	return l;
}

struct node_t *xor(struct node_t *n1, struct node_t *n2) {
    return (struct node_t *)((size_t)n1 ^ (size_t)n2);    
}

int push(struct list_t *l, char data) {
	if (l == NULL)
		return 1;
	struct node_t *newNode = (struct node_t *)malloc(sizeof(struct node_t));
	newNode->xor_ptr = l->head;
	newNode->data = data;
	if (l->head != NULL)
		l->head->xor_ptr = xor(l->head->xor_ptr, newNode);
	else
		l->tail = newNode;
	l->head = newNode;
	return 0;
}

int pop(struct list_t *l) {
	if (l == NULL || l->head == NULL)
		return 1;
    struct node_t *temp = l->head;
    
	l->head = l->head->xor_ptr;
	if (l->head != NULL)
    	l->head->xor_ptr = xor(temp, l->head->xor_ptr);
    else 
        l->tail = NULL;
    free(temp);
   	return 0;
}


int pushNode(struct list_t *l, struct node_t *n) {
	if (l == NULL)
		return 1;
	n->xor_ptr = l->head;
	if (l->head != NULL)
		l->head->xor_ptr = xor(l->head->xor_ptr, n);
	else
		l->tail = n;
	l->head = n;
	return 0;
}

struct node_t *popNode(struct list_t *l) {
    if (l == NULL || l->head == NULL)
		return NULL;
    struct node_t *temp = l->head;
    l->head = l->head->xor_ptr;
    if (l->head != NULL)
    	l->head->xor_ptr = xor(temp, l->head->xor_ptr);
    else 
        l->tail = NULL;
    return temp;
}

int printData(struct list_t *l) {
	if (l == NULL)
		return 1;
	struct node_t *tempNode = l->tail;
	struct node_t *prevNode = NULL;
	while (tempNode != NULL) {
		printf("%d ", tempNode->data);
		struct node_t *tempPtr = tempNode;
		tempNode = xor(tempNode->xor_ptr, prevNode);
		prevNode = tempPtr;
	}
	return 0;
}


int purge(struct list_t *l) {
	if (l == NULL)
		return 1;
	struct node_t *tempNode = l->tail;
	struct node_t *prevNode = NULL;
	while (tempNode != NULL) {
		struct node_t *tempPtr = tempNode;
		tempNode = xor(tempNode->xor_ptr, prevNode);
		free(prevNode);
		prevNode = tempPtr;
	}
	free(l->head);
	free(l);
	return 0;
}

void mergeSorted(struct list_t *, struct list_t *);

void mergeSort(struct list_t *l) {
    if(l == NULL || l->head == NULL || l->head->xor_ptr == NULL) return;

    struct node_t *slow_ptr = l->head, *slow_ptr_prev = NULL;
    struct node_t *fast_ptr = l->head, *fast_ptr_prev = NULL;
    
    while(fast_ptr != NULL && xor(fast_ptr->xor_ptr, fast_ptr_prev) != NULL) {
        struct node_t *temp = fast_ptr;
        fast_ptr = xor(fast_ptr->xor_ptr, fast_ptr_prev);
        fast_ptr_prev = temp;

        temp = fast_ptr;
        fast_ptr = xor(fast_ptr->xor_ptr, fast_ptr_prev);
        fast_ptr_prev = temp;

        temp = slow_ptr;
        slow_ptr = xor(slow_ptr->xor_ptr, slow_ptr_prev);
        slow_ptr_prev = temp;        
    }
    
    struct node_t *second_list_head = slow_ptr;

    slow_ptr_prev->xor_ptr = xor(slow_ptr_prev->xor_ptr, second_list_head);

    second_list_head->xor_ptr = xor(slow_ptr_prev, second_list_head->xor_ptr);
    
    struct list_t l2 = {second_list_head, l->tail};
    mergeSort(l);
    mergeSort(&l2); 

    mergeSorted(l, &l2);
}

void mergeSorted(struct list_t *l1, struct list_t *l2) {
    struct list_t *result_list = init();
    struct node_t *tempNode = NULL;
    while (l1->head || l2->head) {
        if (l1->head == NULL) {
            tempNode = popNode(l2);
            pushNode(result_list, tempNode);
        }
        else if (l2->head == NULL) {
	        tempNode = popNode(l1);
        	pushNode(result_list, tempNode);
        }
        else {
            if (l1->head->data > l2->head->data) {
	        tempNode = popNode(l2);
        	pushNode(result_list, tempNode);
            } else {
	        tempNode = popNode(l1);
        	pushNode(result_list, tempNode);
            }
        }
    }
    l1->head = result_list->tail;
    l1->tail = result_list->head;
    free(result_list);
}

int main() {
	struct list_t *l = init();
	push(l, 7);
	push(l, 12);
	push(l, 1);
	push(l, 0);
	push(l, -3);
	push(l, 4);

	printData(l);

	mergeSort(l);
	printf("\n");
	printData(l);
	purge(l);
	return 0;
}
