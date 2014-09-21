#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NODES 5

/* vertex of the commitment tree */
struct vertex{
    int count; // represents number of vertices rooted in that subtree
    struct vertex *left,*right;
};

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

// void printCommitmentTree(struct vertex** tree){

//     int i;
//     struct vertex** temp;
//     struct vertex** iterator;

//     iterator = tree;

// }

int main(){

    struct vertex *commitmentTree;
    srand(time(NULL));
    
    buildCommitmentTree(&commitmentTree);
    // printCommitmentTree(&commitmentTree);
    return 0;
}