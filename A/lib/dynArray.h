#ifndef __DYN_ARRAY
#define __DYN_ARRAY
#include<stddef.h>

typedef struct stack {
	double *arr;
	size_t size;
	size_t capacity;
} stack_t;

stack_t *init(size_t initCap);
void destroy_stack(stack_t *s);
void push_back(stack_t *stack, double value);
void pop(stack_t *stack);
double back(stack_t *stack);
double front(stack_t *stack);

#endif


