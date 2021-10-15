#include<stdio.h>


int xor(int a, int b) {
	int or = a | b;
	int nand = ~(a & b);
	return or & nand;
}


int main() {
	int a, b;
	scanf("%d %d", &a, &b);

	printf("%d\n", xor(a, b));
}

