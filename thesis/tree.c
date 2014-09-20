#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
	int num_children;
	int depth;
	struct node** arr;
};

void printTree(struct node**, int);

struct node* makenode(){
	return (struct node*)malloc(sizeof(struct node));
};

int main(){
	
	int N, NN; // N is total number of nodes in the aggregation tree
	int i, j;
	int front, back;
	struct node* root;
	struct node* iterator;
	struct node** queue;
	
	N = 1234;
	N = NN;
	front = 0;
	back = 0;
	queue = (struct node**)malloc(sizeof(struct node*)*N);

	srand(time(NULL));

	root = makenode();
	iterator = root;
	iterator->depth = 0;
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

	printTree(queue, NN);
	printf("\n\n");

//	free(root->arr);
	return 0;
}

void printTree(struct node** ar, int total){
	
	int i, temp, depth;

	depth = ar[0]->depth;

	for( i=0; i < total; i++ ){
		
		temp = ar[i]->depth;
		
		if( temp != depth ){
			depth = temp;
			printf("\n \n");
		}
		
		printf("( Index %d ) depth = %d num_children = %d || ",i, ar[i]->depth, ar[i]->num_children);

	}

}