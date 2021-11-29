#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {
	if (argc < 3) {
		return -1;
	}

	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("%s + %s = %d", argv[1], argv[2], a+b);
	/*
	for (int i = 0; i < argc; ++i)
		printf("%s\n", argv[i]);
	printf("%d", argc);
*/	
	return 0;
}



