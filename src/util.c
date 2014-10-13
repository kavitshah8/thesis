#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

int countTree (struct aggregationTreeNode *head)
{
	//count number of nodes in tree and return
	int i, sum;
	int num_children;

	// printf("smiale\n");
	// printf("%d\n",num_children);
	sum = 1;
	
	if (!head)
		return 0;

	num_children = head->num_children;

	for ( i=0; i < num_children; i++)
	{
		sum += countTree(head->arr[i]);
	}
	
	return sum;
}

int depthOfNode (struct aggregationTreeNode *head, struct aggregationTreeNode *ptr)
{
	int dep = 0;
	
	while (ptr != head)
	{
		ptr = ptr->parent;
		dep++;
	}
	
	return dep;
}

void printTree (struct aggregationTreeNode** arr, int total)
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
			printf("Node's id = %d depth = %d num_children = %d parent = NULL || ", arr[i]->id, arr[i]->depth, arr[i]->num_children );
		}
		else
		{
			printf("Node's id = %d depth = %d num_children = %d parent's_id = %d || ", arr[i]->id, arr[i]->depth, arr[i]->num_children, arr[i]->parent->id );
		}
	}
}

struct verticalDataStr* createDataStr (struct aggregationTreeNode **queue, int nodes) 
{

	int dep;
	int front;
	
	struct verticalDataStr* top = NULL;
	struct verticalDataStr* tempverticalDataStr;
	struct verticalDataStr* mover;
	
	struct horizontalDataStr* temphorizontalDataStr;

	struct aggregationTreeNode* ptr;
	struct aggregationTreeNode* head; 

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
				top = (struct verticalDataStr*)malloc(sizeof(struct verticalDataStr));
				top->depth = dep;
				top->next = NULL;
				top->list = (struct horizontalDataStr*)malloc(sizeof(struct horizontalDataStr));
				top->list->ptr = ptr;
				top->list->next = NULL;
				continue;
		}
		else
		{
			if (top->depth < dep)
			{
				tempverticalDataStr = (struct verticalDataStr*)malloc(sizeof(struct verticalDataStr));
				tempverticalDataStr->depth = dep;
				tempverticalDataStr->list = (struct horizontalDataStr*)malloc(sizeof(struct horizontalDataStr));
				tempverticalDataStr->list->ptr = ptr;
				tempverticalDataStr->list->next = NULL;
				tempverticalDataStr->next = top;
				top = tempverticalDataStr;
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
				tempverticalDataStr = (struct verticalDataStr*)malloc(sizeof(struct verticalDataStr));
				tempverticalDataStr->depth = dep;
				tempverticalDataStr->list = (struct horizontalDataStr*)malloc(sizeof(struct horizontalDataStr));
				tempverticalDataStr->list->ptr = ptr;
				tempverticalDataStr->list->next = NULL;

				//insert tempverticalDataStr a end of verticalDataStr link list
				tempverticalDataStr->next = mover->next;
				mover->next = tempverticalDataStr;
			}
			else if (mover->depth == dep)
			{
				temphorizontalDataStr = (struct horizontalDataStr*)malloc(sizeof(struct horizontalDataStr));
				temphorizontalDataStr->ptr = ptr;
				temphorizontalDataStr->next = mover->list;
				mover->list = temphorizontalDataStr;

			}
			else
			{	
				struct verticalDataStr* previous;
				//mover->depth < dep
				tempverticalDataStr = (struct verticalDataStr*)malloc(sizeof(struct verticalDataStr));
				tempverticalDataStr->depth = dep;
				tempverticalDataStr->list = (struct horizontalDataStr*)malloc(sizeof(struct horizontalDataStr));
				tempverticalDataStr->list->ptr = ptr;
				tempverticalDataStr->list->next = NULL;

				//insert tempverticalDataStr infrot of mover in verticalDataStr link list
				tempverticalDataStr->next = mover;
				previous = findPrevious(top, mover);				
				previous->next = tempverticalDataStr;
			}
		}
	}
	return top;
}

struct verticalDataStr* findPrevious (struct verticalDataStr* head, struct verticalDataStr* target)
{
	struct verticalDataStr* walker;

	walker = head;
	
	while (walker->next != target)
	{
		walker = walker->next;
	}
	return walker;
}

void printDataStr (struct verticalDataStr* top)
{
	struct horizontalDataStr* temp;

	printf("\n\nPrinting createDataStr : \n\n");

	while (top != NULL)
	{
		temp = top->list;
		while (temp != NULL)
		{
			printf("depth = %d num_children = %d \t",temp->ptr->depth, temp->ptr->num_children);
			temp = temp->next;
		}
		printf("\n\n");
		top = top->next;
	}
}