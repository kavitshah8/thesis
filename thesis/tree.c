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

/* vertex of the commitment tree */
struct vertex{
    int count; // represents number of vertices rooted in that subtree
    struct vertex *left,*right;
};

void printTree(struct node**, int);

int findSmaller (struct vertex* array[], int differentFrom);

void buildCommitmentTree(struct vertex**);

int main(){

	int N, NN; // N is total number of nodes in the aggregation tree
	int i, j;
	int front, back;
	struct node* root;
	struct node* iterator;
	struct vertex* commitmentTree;
	struct node** queue;


	N = NN = 15;
	front =	back = 0;
	queue = (struct node**)malloc(sizeof(struct node*) * N );

	srand(time(NULL));

	root = iterator = queue[back] = (struct node*)malloc(sizeof(struct node));
	iterator->id = back;
	iterator->depth = 0;
	iterator->parent = NULL;

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
	buildCommitmentTree(&commitmentTree);
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

/*finds and returns the index of first smallest sub-tree in the forest*/
int findSmaller (struct vertex *array[], int differentFrom){

  int smaller,i;
    
  i = 0;
  while ( array[i]->count == -1 ){i++;}
	smaller = i;
    
	if ( i == differentFrom ){
    i++;
    while ( array[i]->count == -1 ){i++;}
    smaller=i;
  }

  for ( i=1; i < NODES; i++ ){
    if (array[i]->count == -1 )
      continue;
    if ( i == differentFrom )
      continue;
    if ( array[i]->count < array[smaller]->count ){
      // saving the index of smaller one
      smaller = i;
    }
  }
  return smaller;
}

/*builds the commitment tree and returns its address by reference*/
void buildCommitmentTree(struct vertex **tree ){
   
	struct vertex *temp;
	struct vertex *array[NODES];
  //	struct vertex ** array = (struct vertex**)malloc(sizeof(struct vertex*)*NODES);
  int i, subTrees = NODES;
  int smallOne,smallTwo;

  for ( i = 0; i < NODES; i++ ){

    array[i] = (struct vertex*)malloc(sizeof(struct vertex));
    array[i]->count = rand()%10;
    array[i]->left = NULL;
    array[i]->right = NULL;
    printf("%d\t", array[i]->count);
    
  }

  printf("\n\n");

  while ( subTrees > 1 ){
    // find smaller returns the index in the tree
    smallOne = findSmaller(array,-1);
    smallTwo = findSmaller(array,smallOne);
    printf("smallOne = %d smallTwo = %d \n", smallOne, smallTwo);

    temp = array[smallOne]; 
    array[smallOne] = (struct vertex*)malloc(sizeof(struct vertex));
    array[smallOne]->count = temp->count + array[smallTwo]->count;
    array[smallOne]->left = array[smallTwo];
    array[smallOne]->right = temp;
    array[smallTwo]->count = -1;
     
		subTrees--;
  }

  *tree = array[smallOne];

  return;
}
