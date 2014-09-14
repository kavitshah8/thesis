#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	
	int* ptr;
	int** ptr_ptr;
	
	ptr = (int* )malloc(sizeof(int));//[ptr = 5001 but it will be assigned 4 byte, because int is 4 byte]
	//ptr = (int* )malloc(sizeof(int)*5); [ptr = 5001 but it will be assigned 4*5 byte memory]
	
	ptr_ptr = &ptr;
	//ptr_ptr = (int** )malloc(sizeof(int* )*5);[ptr = 5001 but it will be assigned 8 byte * 5 memory, because int address is 8 bytes]

	*ptr = 10;
	printf("%d\n",*ptr);
	**ptr_ptr = 100;
	printf("%d\n",**ptr_ptr);

	free(ptr);
//	free(ptr_ptr);
	return 0;
}