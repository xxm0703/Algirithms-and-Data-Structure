#include <stdio.h>


int rule30(int num) {
	int lastBits, i = 0, result = 0;
	
	while((num >> i) != 0) {
		lastBits = (num >> i) & 7;
		switch(lastBits) {
			case 1:
			case 2:
			case 3:
			case 4:
				result |= (1 << i);
		}
		++i;
	}
	return result;

}


int main() {
	int a;
	scanf("%d", &a);
	printf("%d\n", rule30(a));
	return 0;
}
