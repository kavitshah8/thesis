#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../header_files/util.h"

int main () 
{

	int const NODES = 10;
	int const DIVISOR = 4;	
	int N; // N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back;
	struct aggregationTreeNode* root;
	struct aggregationTreeNode* iterator;
	struct aggregationTreeNode* queue[10000];
	//queue = (struct aggregationTreeNode**)malloc(sizeof(struct aggregationTreeNode*) * (N+1) );
	vds* top;
	struct commitmentTreeNode* head;

	srand(time(NULL));

	N = NODES;
	front =	back = 0;

	// Handling the root seperately 
	root = iterator = queue[back] = (struct aggregationTreeNode*)malloc(sizeof(struct aggregationTreeNode));
	
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
	
		iterator->num_children = rand() % DIVISOR;

		if (N < iterator->num_children)
		{
			iterator->num_children = rand() % (N+1);
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
						iterator->num_children = rand() % (N+1);
					}								
				} 
			}
		}
	
		// malloc(0) should return NULL; 
		iterator->arr = (struct aggregationTreeNode**)malloc( sizeof(struct aggregationTreeNode*) * iterator->num_children ) ;

		if (iterator->arr == NULL)
		{
			printf("Memory Allocation Error\n");
			exit(1);
		}
		
		for (i=0; i < iterator->num_children; i++)
		{
			iterator->arr[i] = (struct aggregationTreeNode*)malloc( sizeof(struct aggregationTreeNode) ) ;

			if (iterator->arr[i] == NULL )
			{
				printf("Memory Allocation Error\n");
				exit(1);
			}
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
	printf("front = %d  back = %d N = %d\n\n", front, back, N);

	if (front == back)
		if (front == NODES) 
			printf("front == back == NODES :) \n\n");
	
	printf("Traversing tree using DFS-post order\n\n");
	printTree(root); 
	// free(root->arr);
	
	top = createDataStr(queue, NODES);

	printDataStr(top);
	
	head = createCommitmentTree(top);
	printf("Unsorted LinkedList:\n");
	printLinkedList(head);
	head = sortLinkedList(head);
	printf("Sorted LinkedList:\n");
	printLinkedList(head);
	
	printf("\n");

	
	return 0;
}
