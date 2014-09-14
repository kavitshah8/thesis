/*
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main2(){
	//srand(time(NULL));
	int* ptr;
	int** ptr_ptr;
	ptr = (int* )malloc(sizeof(int));
	printf("value of ptr %d \n", ptr);
	ptr_ptr = (int** )malloc(sizeof(int));
	ptr_ptr = &ptr;
	**ptr_ptr = 10;
	printf("value of ptr after derencing %d \n", ptr);

	free(ptr);
	free(ptr_ptr);
	return 0;
}*/