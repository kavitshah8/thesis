#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../header_files/util.h"

int main () 
{

	// random tree generation algorithm in breadth first search fashion

	int N; // N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back;
	int const DIVISOR = 4;	
	int const NODES = 255;
	atn* root;
	atn* iterator;
	atn* queue[10000];
	//queue = (atn**)malloc(sizeof(atn*) * (N+1) );
	vds* top;
	ctn* head;

	srand(time(NULL));

	N = NODES;
	front =	back = 0;

	// Handling the root seperately 
	root = iterator = queue[back] = (atn*)malloc(sizeof(atn));
	
	if (root == NULL)
	{
		printf("Memory Allocation Error\n");
		exit(1);
	}

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
	
		// malloc(0) should return NULL; 
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

	printf("\nNumber of nodes in tree = %d\n",countTree(root));
	printf("front = %d  back = %d N = %d\n\n", front, back, N);

	if (front == back)
		if (front == NODES) 
			printf("front == back == NODES :) \n\n");
	
	printf("Traversing tree using DFS-post order\n\n");
	printTree(root); 
	// free(root->arr);
	
	top = createDataStr(queue, NODES);

	printDataStr(top);
	
	root = createCommitmentTree(top);
	printCommitmentTree(root);
	// printf("Unsorted LinkedList by their Height:\n");
	// printLinkedList(head);
	
	// head = sortLinkedList(head);
	// printf("Sorted LinkedList by their Height:\n");
	// printLinkedList(head);
	printf("\n");

	
	return 0;
}
