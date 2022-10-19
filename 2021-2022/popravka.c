#include<stdio.h>
#include<string.h>

float average_of_even(int numbers[], int size){
	int temp = 0;
	int num = 0;//num sa chetnite chisla
	float avr;
	for(int i = 0; i < size; i++){
		if(numbers[i] % 2 == 0){
			temp+=numbers[i];
			num++;
		}
	} 
	avr = temp/num;
	return avr;
}

void reverse(char *arr){
	int len;
	for(int i = 0; arr[i] != '\0'; i++){
		len++;
	}
	char temp[len];
	for(int i = 0; arr[i] != '\0'; i++){
		temp[i] = arr[len-1-i];
	}
	//strlen ne raboteshe po nqkakva prichina
	printf("%s\n", temp);
}

int main(){

	int numbers[6] = {1, 2, 3, 4, 5, 6};
	char* arr = "Hello";
	
	printf("The average of the even numbers is:%f\n", average_of_even(numbers, 6));
	
	reverse(arr);
	
	return 0;
}
