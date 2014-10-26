#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

void createAggregationTree (atn *root, atn **queue)
{
	// random tree generation algorithm in breadth first search fashion

	int N; // N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back;
	atn* iterator;
	
	srand(time(NULL));

	N = NODES;
	front =	back = 0;

	// Handling the root seperately 
	iterator = queue[back] = root;
	
	iterator->id = back;
	iterator->depth = 0;
	iterator->parent = NULL;
	back++;
	N--;	

	while (front < NODES)
	{
	
		iterator->numChildren = rand() % DIVISOR;

		if (N < iterator->numChildren)
		{
			iterator->numChildren = rand() % (N+1);
		}

		// Gives you a tree
		if (iterator == root && iterator->numChildren == 0)
		{
			iterator->numChildren = 1;
		}
		else
		{ // make sure left most child doesnot have 0 children and that make sure your tree does not break
			if (iterator != root  && iterator->numChildren == 0)
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
					sum += queue[tt]->numChildren;
					tt++;
				}
				if (!sum)
				{
					iterator->numChildren = 1;
					if (N < iterator->numChildren)
					{
						iterator->numChildren = rand() % (N+1);
					}								
				} 
			}
		}
	
		iterator->arr = (atn**)malloc( sizeof(atn*) * iterator->numChildren ) ;

		if (iterator->arr == NULL)
		{
			printf("Memory Allocation Error\n");
			exit(1);
		}
		
		for (i=0; i < iterator->numChildren; i++)
		{
			iterator->arr[i] = (atn*)malloc( sizeof(atn) ) ;

			if (iterator->arr[i] == NULL )
			{
				printf("Memory Allocation Error\n");
				exit(1);
			}
				iterator->arr[i]->id = back;
				iterator->arr[i]->depth = iterator->depth + 1;
				iterator->arr[i]->parent = iterator;
				iterator->arr[i]->numChildren = 0;
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

	printf("front = %d  back = %d N = %d\n\n", front, back, N);

	if (front == back)
		if (front == NODES) 
			printf("front == back == NODES :) \n\n");

}

int countTree (atn *head)
{
	int i, sum;
	int numChildren;

	sum = 1;
	
	if (!head)
		return 0;

	numChildren = head->numChildren;

	for (i=0; i < numChildren; i++)
	{
		sum += countTree(head->arr[i]);
	}
	
	return sum;
}

int depthOfNode (atn *head, atn *ptr)
{
	int dep = 0;
	
	while (ptr != head)
	{
		ptr = ptr->parent;
		dep++;
	}
	
	return dep;
}

void printTree (atn *iterator)
{
	int i;
	i = 0;
	
	if (iterator != NULL)
	{
		for (i = 0; i < iterator->numChildren; i++)
		{
			// try implementing without recurssion
			printTree(iterator->arr[i]);
		}

		if (iterator->depth == 0)
		{
			printf("id = %d, depth = %d, numChildren = %d, parent = NULL\n", iterator->id, iterator->depth, iterator->numChildren );
		}
		else
		{
			printf("id = %d, depth = %d, numChildren = %d, parent's_id = %d\n ", iterator->id, iterator->depth, iterator->numChildren, iterator->parent->id );
		}

	}	
}

