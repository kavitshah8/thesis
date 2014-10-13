#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../lib/util.h"

int main () 
{
	
	int N, NN; // NN is total number of nodes in the aggregation tree
			   // N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back, middle;
	struct node* root;
	struct node* iterator;
	struct node* queue[10000];
	//queue = (struct node**)malloc(sizeof(struct node*) * (N+1) );
	struct vertical* top;

	// srand(time(NULL));

	N = NN = 20;
	front =	back = middle = 0;

	// Handling the root seperately 
	root = iterator = queue[back] = (struct node*)malloc(sizeof(struct node));
	iterator->id = back;
	iterator->depth = 0;
	iterator->parent = NULL;
	back++;
	N--;	

	// while( N > 0 )
	while (front < NN)
	{
	
		if (middle < NN)
		{
			iterator->num_children = rand() % 4;
		}
		else
		{
			iterator->num_children = 0;	
		}


		// Gives you a tree
		if (iterator == root && iterator->num_children == 0)
		{
			iterator->num_children = 1;
		}
		else
		{ // make sure left most child doesnot have 0 children and that make sure your tree does not break
			if (iterator != root  && iterator->num_children == 0)
			{
				int dep = 1 + (iterator->parent->depth);
				int sum = 0;
				int tt = 0;

				while (tt < back)
				{
					if (queue[tt]->depth == dep)
					{
						break;						
					}
					tt++;
				}
				while (tt < back)
				{
					sum += queue[tt]->num_children;
					tt++;
				}
				if (!sum)
				{
					if (middle < NN)
					{
						iterator->num_children = 1;							
					}

				} 
			}
		}
	
		middle += iterator->num_children;

		// malloc(0) should return NULL; 
		iterator->arr = (struct node**)malloc( sizeof(struct node*) * iterator->num_children ) ;
		
		for (i=0; i < iterator->num_children; i++)
		{
			iterator->arr[i] = (struct node*)malloc( sizeof(struct node) ) ;
			iterator->arr[i]->id = back;
			iterator->arr[i]->depth = iterator->depth + 1;
			iterator->arr[i]->parent = iterator;
			iterator->arr[i]->num_children = 0;
			iterator->arr[i]->arr = NULL;
			queue[back] = iterator->arr[i];
			back++;
			N--;
		}				
		
		if (front > back)
		{
			printf("Queue is not working as supposed to \n");
			break;
		}
		
		// printf("%p\n", queue[front]);
		front++;
		iterator = queue[front];
		
	}

	printf("\n Number of nodes in tree = %d\n",countTree(root));
	printf("\n front = %d  back = %d N = %d\n", front, back, N);
	printTree(queue, front); 
	// printTree(queue,back); while( N > 0)
	// free(root->arr);
	
	top = createDataStr(queue, front);
	printDataStr(top);
	printf("\n");

	return 0;
}
