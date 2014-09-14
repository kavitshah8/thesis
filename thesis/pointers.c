#include<stdio.h>
#include<stdlib.h>

int main(){
	int* ptr;
	int** ptr_ptr;
	int pointe;
	
	//setting up linked list
	ptr = &pointe;
	ptr_ptr = &ptr;

	//changing pointees value using first pointer
	*ptr = 10;
	printf("%d\n",pointe);

	//changing pointees value using second pointer	
	**ptr_ptr = 100;
	printf("%d\n",pointe);

	return 0;
}