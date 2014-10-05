#include "../lib/util.h"
#include <stdio.h>

int countTree (struct node *head)
{
	//count number of nodes in tree and return
	int i, sum;
	int num_children;

	// printf("smiale\n");
	// printf("%d\n",num_children);
	sum = 1;
	
	if(!head)
		return 0;

	num_children = head->num_children;

	for( i=0; i < num_children; i++)
	{
		sum += countTree(head->arr[i]);
	}
	
	return sum;
}

int depthOfNode (struct node *head, struct node *ptr)
{
	int dep=0;
	
	while (ptr != head)
	{
		ptr=ptr->parent;
		dep++;
	}
	
	return dep;
}

void printTree (struct node** arr, int total)
{
	int i, temp, depth;
	
	printf("\n\nPrinting aggregationTree : \n\n");

	depth = arr[0]->depth;
	
	for (i=0; i < total; i++)
	{
	
		temp = arr[i]->depth;
	
		if (temp != depth)
		{
			depth = temp;
			printf("\n \n");
		}
	
		if (depth == 0)
		{
			printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent = NULL || ", i, arr[i]->id, arr[i]->depth, arr[i]->num_children );
		}
		else
		{
			printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent's_id = %d || ", i, arr[i]->id, arr[i]->depth, arr[i]->num_children, arr[i]->parent->id );
		}
	}
}

struct vertical* createDataStr (struct node **queue, int nodes) {

	int dep;
	int front;
	
	struct vertical* top = NULL;
	struct vertical* tempvertical;
	struct vertical* mover;
	
	struct horizontal* temphorizontal;

	struct node* ptr;
	struct node* head; 

	front = 0;
	head = queue[front];

	while (front < nodes)
	{
		// ptr will be pointing to aggregation tree
		ptr = queue[front];
		front++;

		dep = depthOfNode(head, ptr);
		
		if (top == NULL)
		{
				top = (struct vertical*)malloc(sizeof(struct vertical) );
				top->depth = dep;
				top->next = NULL;
				top->list = (struct horizontal*)malloc(sizeof(struct horizontal) );
				top->list->ptr = ptr;
				top->list->next = NULL;
				continue;
		}
		else
		{
			if (top->depth < dep)
			{
				tempvertical = (struct vertical*)malloc(sizeof(struct vertical) );
				tempvertical->depth = dep;
				tempvertical->list = (struct horizontal*)malloc(sizeof(struct horizontal) );
				tempvertical->list->ptr = ptr;
				tempvertical->list->next = NULL;
				tempvertical->next = top;
				top = tempvertical;
				continue;
			}
			mover = top;
			while (mover->depth > dep)
			{  
				mover = mover->next;
				if (!mover)
					break;
			}
			if (!mover)
			{
				tempvertical = (struct vertical*)malloc(sizeof(struct vertical) );
				tempvertical->depth = dep;
				tempvertical->list = (struct horizontal*)malloc(sizeof(struct horizontal) );
				tempvertical->list->ptr = ptr;
				tempvertical->list->next = NULL;

				//insert tempvertical a end of vertical link list
				tempvertical->next = mover->next;
				mover->next = tempvertical;
			}
			else if (mover->depth == dep)
			{
				temphorizontal = (struct horizontal*)malloc(sizeof(struct horizontal) );
				temphorizontal->ptr = ptr;
				temphorizontal->next = mover->list;
				mover->list = temphorizontal;

			}
			else
			{	
				struct vertical* previous;
				//mover->depth < dep
				tempvertical = (struct vertical*)malloc(sizeof(struct vertical) );
				tempvertical->depth = dep;
				tempvertical->list = (struct horizontal*)malloc(sizeof(struct horizontal) );
				tempvertical->list->ptr = ptr;
				tempvertical->list->next = NULL;

				//insert tempvertical infrot of mover in vertical link list
				tempvertical->next = mover;
				previous = findPrevious(top,mover);				
				previous->next = tempvertical;
			}
		}
	}
	return top;
}

struct vertical* findPrevious (struct vertical* head, struct vertical* target)
{
	struct vertical* walker;

	walker = head;
	
	while (walker->next != target)
	{
		walker = walker->next;
	}
	return walker;
}

void printDataStr (struct vertical* top)
{
	struct horizontal* temp;

	printf("\n\nPrinting createDataStr : \n\n");

	while (top != NULL)
	{
		temp = top->list;
		while (temp != NULL)
		{
			printf("depth = %d num_children = %d \t",temp->ptr->depth, temp->ptr->num_children);
			temp = temp->next;
		}
		printf("\n");
		top = top->next;
	}
}