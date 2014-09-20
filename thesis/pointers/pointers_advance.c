#include<stdio.h>
#include<stdlib.h>

int main(){

	int* ptr;
	int a;
	ptr = &a; // ptr = (int*)malloc(sizeof(int)); are equivalent

	//int arr[5]; is equivalent to below two lines
	int *arr;
	arr = (int*)malloc(sizeof(int)*5);

	return 0;
}