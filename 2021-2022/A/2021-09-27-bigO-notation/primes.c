#include <stdio.h>
int IsPrime(int num){
	int a = 0;
	for(int i = 2; i < num; i++){
		if(num % i == 0){
			return false;
		}
	}

	return true;
}
