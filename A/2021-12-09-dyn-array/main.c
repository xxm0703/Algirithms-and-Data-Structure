#include"dynArray.h"
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

void list_stack(stack_t *s) {
	for (size_t i = 0; i < s->size; i++)
	{
		printf("%.2lf ", s->arr[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	stack_t *s = init(5);

	for (size_t i = 1; i < argc; i++)
	{
		if (isdigit(argv[i][0]))
		{
			push_back(s, atof(argv[i]));
			continue;
		}
		
		switch (argv[i][0])
		{
		case 'l':
			list_stack(s);
			break;
		case 'p':
			pop(s);
			break;
		case 'f':
			printf("%.2lf\n", front(s));
			break;
		case 'b':
			printf("%.2lf\n", back(s));
			break;
		
		default:
			fprintf(stderr, "Invalid operation!\n Unknown '%c'", argv[i][0]);
			break;
		}
	}
	destroy_stack(s);

	return 0;
}
