#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node{
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;
};

void printTree(struct node**, int);

int main(){

	int N, NN; // N is total number of nodes in the aggregation tree
	int id_count; // id_count will assign unique id to each node
	int i, j;
	int front, back;
	struct node* root;
	struct node* iterator;
	struct node** queue;

	N = NN = 12;
	id_count = front = 	back = 0;
	queue = (struct node**)malloc(sizeof(struct node*) * N );

	srand(time(NULL));

	root = (struct node*)malloc(sizeof(struct node));
	iterator = queue[back]= root;
	iterator->id = id_count;
	iterator->depth = 0;
	iterator->parent = NULL;

	id_count++;
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

			iterator->arr[i]->id = id_count;
			iterator->arr[i]->depth = iterator->depth + 1;
			iterator->arr[i]->parent = iterator;

			queue[back] = iterator->arr[i];
			
			id_count++;
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

void printTree(struct node** arr, int total){
	
	int i, temp, depth;

	depth = arr[0]->depth;

	//root's parent->id is undefined; so starting from index of 1

	for( i=1; i < total; i++ ){
		
		temp = arr[i]->depth;
		
		if( temp != depth ){
			depth = temp;
			printf("\n \n");
		}
		
		if( depth == 0 ){
				printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent's_id = %d || ", i,  arr[i]->id, arr[i]->depth, arr[i]->num_children, arr[i]->parent->id );
		}else{
				printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent's_id = %d || ", i,  arr[i]->id, arr[i]->depth, arr[i]->num_children, arr[i]->parent->id );
		}

	}

}