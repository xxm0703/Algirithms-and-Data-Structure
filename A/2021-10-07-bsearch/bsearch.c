#include<stdio.h>

int bsearch(int *arr, size_t l, size_t r, int value) {
	if (l > r)
		return -1;

	size_t mid = (l + r) / 2;

	if (arr[mid] == value)
		return mid;

	if (arr[mid] < value)
		return bsearch(arr, mid + 1, r, value);

	return bsearch(arr, l, mid - 1, value);
	
}


int main() {
    int a[] = {1, 2, 3 ,5, 8, 9};
	printf("%d\n", bsearch(a, 0, 5, 7));
	return 0;
}




