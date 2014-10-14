#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../header_files/util.h"

int main () 
{
	int MM;
	srand(time(NULL));

	for (MM = 0; MM < 5; MM++)
	{

	int N, NN; // NN is total number of nodes in the aggregation tree
			   		// N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back, middle;
	struct aggregationTreeNode* root;
	struct aggregationTreeNode* iterator;
	struct aggregationTreeNode* queue[10000];
	//queue = (struct aggregationTreeNode**)malloc(sizeof(struct aggregationTreeNode*) * (N+1) );
	struct verticalDataStr* top;

	// srand(time(NULL));

	N = NN = 20;
	front =	back = 0;

	// Handling the root seperately 
	root = iterator = queue[back] = (struct aggregationTreeNode*)malloc(sizeof(struct aggregationTreeNode));
	iterator->id = back;
	iterator->depth = 0;
	iterator->parent = NULL;
	back++;
	N--;	

	// while( N > 0 )
	// while (back < NN)
	while(front < NN)
	{
	
		iterator->num_children = rand() % 4;

		if (N < iterator->num_children)
		{
			while (N < iterator->num_children)
			{
				iterator->num_children = rand() % 4;
			}
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
					iterator->num_children = 1;
					if (N < iterator->num_children)
					{
						while (N < iterator->num_children)
						{
							iterator->num_children = rand() % 4;
						}
					}								
				} 
			}
		}
	
		// malloc(0) should return NULL; 
		iterator->arr = (struct aggregationTreeNode**)malloc( sizeof(struct aggregationTreeNode*) * iterator->num_children ) ;
		
		for (i=0; i < iterator->num_children; i++)
		{
			iterator->arr[i] = (struct aggregationTreeNode*)malloc( sizeof(struct aggregationTreeNode) ) ;
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
		
		front++;
		iterator = queue[front];
		
	}

	printf("\nNumber of nodes in tree = %d\n",countTree(root));

	if (front == back)
	{
		if (front == NN) 
		printf("front == back == NN :) \n");
	}

	printf("\nfront = %d  back = %d N = %d\n", front, back, N);
	
	printTree(queue, back); 
	// free(root->arr);
	
	top = createDataStr(queue, back);

	printDataStr(top);

	printf("\n");

	}
	
	printf("%d times OK\n",MM);
	
	return 0;
}
