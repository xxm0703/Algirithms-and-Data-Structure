#include <stdio.h>
#include <stdbool.h>

typedef unsigned long size_t;

int minEl(int arr[], size_t size) {
	int currentMin = arr[0];
	
	for(int i = 0; i < size; ++i) {
		if(currentMin > arr[i])
			currentMin = arr[i];

	}

	return currentMin;
}

int typMinEl(int arr[], size_t size) {
	bool isMin = true;	
	int x;
	for(x = 0; x < size; ++x) {
		isMin = true;
		for (int y = 0; y < size; ++y) {
			if(arr[x] > arr[y]) {
				isMin = false;

			}

		}
		if (isMin)
			break;
	}
	return arr[x];

}

int main() {
	int a[20000];
	typMinEl(a, 20000);
}


