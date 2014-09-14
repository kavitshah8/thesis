#include<stdio.h>
#include<stdlib.h>

int main(){
	int* ptr;
	int** ptr_ptr;
	int pointe;
	int pointe_1;
	
	//setting up linked list
	ptr = &pointe;
	ptr_ptr = &ptr;

	//changing pointees value using first pointer
	*ptr = 10;
	printf("%d\n",pointe);

	//changing pointees value using second pointer	
	**ptr_ptr = 100;
	printf("%d\n",pointe);

	//Using ptr_ptr changing where the ptr will be pointing
	printf("%d\n", ptr);
	// *ptr_ptr = 10; (can not assign int to int* )
	*ptr_ptr = &pointe_1;
	printf("%d\n", ptr);

	return 0;
}