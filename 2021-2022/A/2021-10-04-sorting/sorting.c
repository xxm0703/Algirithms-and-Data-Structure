#include<stdio.h>
#define ARR_SIZE 5

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void printArr(int *arr, size_t size) {

	for (int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);    // arr[i] <=> *(arr + i)
	}
	printf("\n");
}

void selectionSort(int *arr, size_t size) {

	for (int i = 0; i < size - 1; ++i) {
		int min = i;
		for (int j = i; j < size; ++j) {
			if (arr[min] > arr[j])
				min = j;
		}
		swap(arr + min, arr + i);
	}

}

int partition(int *start, int *end) {	
	int pivot = 0;
	
	for (int i = 1; i <= end - start; ++i) {
		
		if (start[i] < start[pivot]) { 
			int index = i;
			do {
				swap(start + index, start + index - 1);
			} while(--index > pivot);
		}
	}

	return pivot;
}

void quickSort(int *start, int *end) {
	if (end - start <= 0)
		return;

	int pivot  = partition(start, end);
	
	quickSort(start, start + pivot - 1);
	quickSort(start + pivot + 1, end);
}

int main() {
	int arr[ARR_SIZE];
	for(int i = 0; i < ARR_SIZE; ++i) {
		scanf("%d", arr + i);
	}
	quickSort(arr, arr + ARR_SIZE);

	printArr(arr, ARR_SIZE);
	return 0;
}
