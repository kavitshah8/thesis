#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node{
	int num_children;
	struct node** arr;
};

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

	front = 0 ;
	back = 0;
	queue = (struct node**)malloc(sizeof(struct node*)*N);

	srand(time(NULL));

	N--;
	root = makenode();
	iterator = root;
	
	while( N > 0 ){
		
		iterator->num_children = rand() % ( N + 1 );
		
		if( iterator == root && iterator->num_children == 0 ){
			iterator->num_children = 1;
		}
		
		N = N - ( iterator->num_children );
		
		iterator->arr = (struct node**)malloc( sizeof(struct node*) * iterator->num_children ) ;
		
		for( i=0; i<iterator->num_children; i++ ){
		
			iterator->arr[i] = (struct node*)malloc( sizeof(struct node) ) ;
			queue[back] = iterator->arr[i];
			back++;
		
		}
		
		if( front > back ){
			printf("Queue is not working as supposed to \n");
			break;
		}
		
		iterator = queue[front];
		front++;
	}

//	free(root->arr);
	return 0;
}