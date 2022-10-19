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
		l->head->xor_ptr ^= newNode;
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


int printData(struct list_t *l) {
	if (l == NULL)
		return 1;
	struct node_t *tempNode = l->tail;
	struct node_t *prevNode = NULL;
	while (tempNode != NULL) {
		printf("%d ", tempNode->data);
		struct node_t *tempPtr = tempNode;
		tempNode = tempNode->xor_ptr ^ prevNode;
		prevNode = tempPtr;
	}
	return 0;
}

void mergeSort(struct list_t *l) {
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
    
    struct node_t *second_list_head = xor(slow_ptr->xor_ptr, slow_ptr_prev);
    second_list_head->xor_ptr = xor(second_list_head->xor_ptr, slow_ptr);

    slow_ptr->xor_ptr = slow_ptr_prev;
    
    struct list_t l2 = {second_list_head, l->tail};
    mergeSort(l);
    mergeSort(&l2); 

    mergeSorted(l, &l2);
}

void mergeSorted(struct list_t *l1, struct list_t *l2) {
    struct list_t *result_list = init();
    while (l1->head || l2->head) {
        if (l1->head == NULL) {
            push(result_list, l2->head->data);
            pop(l2);
        }
        else if (l2->head == NULL) {
            push(result_list, l1->head->data);
            pop(l1);
        }
        else {
            if (l1->head->data > l2->head->data) {
                push(result_list, l2->head->data);
                pop(l2);
            } else {
                push(result_list, l1->head->data);
                pop(l1);                        
            }
        }
    }
    l1->head = result_list->tail;
    l1->tail = result_list->head;
    free(result_list);
}

int main() {
	return 0;
}
