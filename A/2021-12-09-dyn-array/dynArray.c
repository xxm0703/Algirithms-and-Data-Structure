#include"dynArray.h"
#include<stdlib.h>


stack_t *init(size_t initCap) {
	if (initCap < 1) {
		exit(-1);
	}
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	stack->size = 0;
	stack->arr = (double *)malloc(sizeof(double) * initCap);
	stack->capacity = initCap;
	return stack;
}

void destroy_stack(stack_t *s) {
	free(s->arr);
	free(s);
}

void push_back(stack_t *stack, double value) {
	if (stack->size == stack->capacity) {
		stack->arr = realloc(stack->arr, stack->capacity *= 2);
	}
	stack->arr[stack->size++] = value;
}

void pop(stack_t *stack) {
	if (stack->size)
		--stack->size;
}

double back(stack_t *stack) {
	if (stack->size)
		return stack->arr[stack->size - 1];
}

double front(stack_t *stack) {
	if (stack->size)
		return stack->arr[0];
}
