#include"dynArray.h"
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char **argv) {
	stack_t *s = init(1);

	push_back(s, 5);
	printf("%ld\n", s->capacity);
	push_back(s, 1);
	printf("%ld\n", s->capacity);
	push_back(s, 13);
	printf("%ld\n", s->capacity);
	
	printf("%.2lf\n", back(s));
	pop(s);
	printf("%.2lf\n", front(s));
	free(s->arr);
	free(s);
	return 0;
}
