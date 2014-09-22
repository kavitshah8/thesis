#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NODES 150

struct node{
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;
	struct label* label;
};

int countTree(struct node *head);

void printTree(struct node**, int);

int main(){

	int N, NN; // N is total number of nodes in the aggregation tree
	int i, j;
	int front, back;
	int max_nodes;
	struct node* root;
	struct node* iterator;
	struct vertex* commitmentTree;
	struct node** queue;


	N = NN = 100;

	front =	back = 0;
	queue = (struct node**)malloc(sizeof(struct node*) * (N+1) );

	// srand(time(NULL));

	root = iterator = queue[back] = (struct node*)malloc(sizeof(struct node));
	iterator->id = back;
	iterator->depth = 0;
	iterator->parent = NULL;

	back++;
	N--;	
	
	while( N > 0 ){

		iterator->num_children = rand() % ( 4 );
		
		if( iterator == root && iterator->num_children == 0 ){
			iterator->num_children = 1;
		}
		
		N = N - ( iterator->num_children );
		
		iterator->arr = (struct node**)malloc( sizeof(struct node*) * iterator->num_children ) ;
		
		for( i=0; i < iterator->num_children; i++ ){
			
			iterator->arr[i] = (struct node*)malloc( sizeof(struct node) ) ;
			iterator->arr[i]->id = back;
			iterator->arr[i]->depth = iterator->depth + 1;
			iterator->arr[i]->parent = iterator;

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

	// printTree(queue, NN);
	printf("%d",countTree(queue[0]));
	
	printf("\n");

	//	free(root->arr);
	return 0;
}

void printTree(struct node** arr, int total){
	
	int i, temp, depth;

	depth = arr[0]->depth;

	for( i=0; i < total; i++ ){
		
		temp = arr[i]->depth;
		
		if( temp != depth ){
			depth = temp;
			printf("\n \n");
		}
		
		if( depth == 0 ){
				printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent = NULL || ", i,  arr[i]->id, arr[i]->depth, arr[i]->num_children );
		}else{
				printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent's_id = %d || ", i,  arr[i]->id, arr[i]->depth, arr[i]->num_children, arr[i]->parent->id );
		}

	}

}

int countTree(struct node *head)
{
	//count number of nodes in tree and return
	int i, sum;
	int num_children = head->num_children;
	
	if(!num_children)
	{
		return 0;
	}
	else
	{
		sum = 1;
	}

	for( i = 0; i < num_children; i++ )
	{
		if(head->arr[i]->num_children!=0)
		{
			sum += countTree(head->arr[i]);	
		}
	}	 
	return sum;
}
