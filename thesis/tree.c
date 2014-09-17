#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node{
	int num_children;
	int depth;
	// To store the address of (struct node) and malloc returns (struct node*) which is address of (struct node)
	struct node** arr;
};

void printTree(struct node**, int);

struct node* makenode(){
	return (struct node*)malloc(sizeof(struct node));
};

int main(){
	int N = 12;

	struct node* root;
	struct node* iterator;
	struct node** queue;
	int i,j;
	int front, back;

	front = 0;
	back = 0;
	queue = (struct node**)malloc(sizeof(struct node*)*N);

	srand(time(NULL));

	/* makenode() returns a pointer to the ( struct node ), root is pointing to that pointer.
		---------------------------------------------------
		|ADDRESS| NAME | VALUE|     |ADDRESS| NAME | VALUE|
		| 6001  | root | 3001 | 	| 3001  | ???? | ???? | 
		----------------------------------------------------
	*/
	root = makenode();
	iterator = root;
	//(*iterator).depth = iterator->depth ( direct = indirect component selection )
	iterator->depth = 0;
	// queue is an array and you can store (struct node*) in it
	queue[back] = iterator;
	back++;
	N--;	
	
	while( N > 0 ){

		iterator->num_children = rand() % ( N + 1 );
		
		if( iterator == root && iterator->num_children == 0 ){
			iterator->num_children = 1;
		}
		
		N = N - ( iterator->num_children );
		
		iterator->arr = (struct node**)malloc( sizeof(struct node*) * iterator->num_children ) ;
		
		for( i=0; i < iterator->num_children; i++ ){
			
			iterator->arr[i] = (struct node*)malloc( sizeof(struct node) ) ;
			iterator->arr[i]->depth = iterator->depth + 1;
			queue[back] = iterator->arr[i];
			back++;
		
		}
		
		if( front > back ){
			printf("Queue is not working as supposed to \n");
			break;
		}

		front++;
		iterator = queue[front];
	
	}

	printTree(queue, N);
	printf("\n\n");

//	free(root->arr);
	return 0;
}

void printTree(struct node** ar, int total){
	
	int i, temp, depth;

	depth = ar[0]->depth;

	for( i=0; i < 12; i++ ){
		
		temp = ar[i]->depth;
		
		if( temp != depth ){
			depth = temp;
			printf("\n \n");
		}
		
		printf("( Index %d ) depth = %d num_children = %d || ",i,ar[i]->depth, ar[i]->num_children);

	}

}