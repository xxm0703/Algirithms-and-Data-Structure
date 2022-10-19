#include<stdio.h>


void selectionSort(int *arr, size_t size) {
	for (size_t i = 0; i < size - 1; ++i) {
		size_t minIndex = i;
		for (size_t j = i; j < size; ++j) {
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		int temp = arr[i];
		arr[i] = arr[minIndex];
		arr[minIndex] = temp;
	}
}

int main() {
	int arr[] = {-3, -5, 10, 0, 2};
	selectionSort(arr, 5);
	for (size_t i = 0; i < 5; ++i) {
		printf("%d, ", arr[i]);
	}
	return 0;
}
