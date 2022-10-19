#include<stdio.h>

void printArr(int *arr, size_t size) {
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
int * minEl(int *arr, size_t size) {
	int minIndex = 0;
	for (int j = 1; j < size; ++j) {
		if (arr[j] < arr[minIndex])
			minIndex = j;
	}
	return arr + minIndex;
}

int partition(int *arr, size_t size) {
	int pivot = 0;
	for (int i = 1; i < size; ++i) {
		if (arr[i] < arr[pivot]) {
			// insert
			int index = i;
			while (index > pivot) {
				swap(arr + index, arr + index - 1);
				--index;
			}
			++pivot;
		}
	
	}
	return pivot;
}

void quickSort(int *arr, size_t size) {
	if (size <= 1)
		return;

	int pivot = partition(arr, size);

	quickSort(arr, pivot);
	quickSort(arr + pivot + 1, size - pivot - 1);
}


void selectionSort(int *arr, size_t size) {
	for (int i = 0; i < size - 1; ++i) {
		swap(&arr[i], minEl(arr + i, size - i)); 
	}

}

int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	for(int i = 0; i < n; ++i)
		scanf("%d", arr + i);

	quickSort(arr, n);
	printArr(arr, n);
}
