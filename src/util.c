#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

int countTree (struct aggregationTreeNode *head)
{
	int i, sum;
	int num_children;

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

void printTree (struct aggregationTreeNode* iterator)
{
	int i = 0;
	
	if (iterator != NULL)
	{
		for (i = 0; i < iterator->num_children; i++)
		{
			// try implementing without recurssion
			printTree(iterator->arr[i]);
		}

		if (iterator->depth == 0)
		{
			printf("id = %d, depth = %d, num_children = %d, parent = NULL\n", iterator->id, iterator->depth, iterator->num_children );
		}
		else
		{
			printf("id = %d, depth = %d, num_children = %d, parent's_id = %d\n ", iterator->id, iterator->depth, iterator->num_children, iterator->parent->id );
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
		
		printf("depth = %d\n", temp->ptr->depth);

		while (temp != NULL)
		{
			printf("id = %d, num_children = %d ||",temp->ptr->id, temp->ptr->num_children);
			temp = temp->next;
		}

		printf("\n\n");
		
		top = top->next;
	}
}