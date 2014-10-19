#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

int countTree (atn *head)
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

void printTree (atn* iterator)
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

vds* createDataStr (atn **queue, int nodes) 
{

	int dep;
	int front;
	
	vds* top = NULL;
	vds* tempverticalDataStr;
	vds* mover;
	
	hds* temphorizontalDataStr;

	atn* ptr;
	atn* head; 

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
				top = (vds*)malloc(sizeof(vds));
				top->depth = dep;
				top->next = NULL;
				top->list = (hds*)malloc(sizeof(hds));
				top->list->ptr = ptr;
				top->list->next = NULL;
				continue;
		}
		else
		{
			if (top->depth < dep)
			{
				tempverticalDataStr = (vds*)malloc(sizeof(vds));
				tempverticalDataStr->depth = dep;
				tempverticalDataStr->list = (hds*)malloc(sizeof(hds));
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
				tempverticalDataStr = (vds*)malloc(sizeof(vds));
				tempverticalDataStr->depth = dep;
				tempverticalDataStr->list = (hds*)malloc(sizeof(hds));
				tempverticalDataStr->list->ptr = ptr;
				tempverticalDataStr->list->next = NULL;

				//insert tempverticalDataStr a end of verticalDataStr link list
				tempverticalDataStr->next = mover->next;
				mover->next = tempverticalDataStr;
			}
			else if (mover->depth == dep)
			{
				temphorizontalDataStr = (hds*)malloc(sizeof(hds));
				temphorizontalDataStr->ptr = ptr;
				temphorizontalDataStr->next = mover->list;
				mover->list = temphorizontalDataStr;

			}
			else
			{	
				vds* previous;
				//mover->depth < dep
				tempverticalDataStr = (vds*)malloc(sizeof(vds));
				tempverticalDataStr->depth = dep;
				tempverticalDataStr->list = (hds*)malloc(sizeof(hds));
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

vds* findPrevious (vds* head, vds* target)
{
	vds* walker;

	walker = head;
	
	while (walker->next != target)
	{
		walker = walker->next;
	}
	return walker;
}

void printDataStr (vds* vdsMover)
{
	hds* hdsMover;

	printf("\n\nPrinting createDataStr : \n\n");

	while (vdsMover != NULL)
	{
		hdsMover = vdsMover->list;
		
		printf("depth = %d\n", hdsMover->ptr->depth);

		while (hdsMover != NULL)
		{
			printf("id = %d, num_children = %d ||",hdsMover->ptr->id, hdsMover->ptr->num_children);
			hdsMover = hdsMover->next;
		}

		printf("\n\n");
		
		vdsMover = vdsMover->next;
	}
}

ctn* createCommitmentTree (vds* vdsMover)
{
	int i, j;
	hds* hdsMover;
	ctn* ctnPtr;
	ctn* myChildForest;
	ctn* moverPtr;
	
	while (vdsMover != NULL)
	{
		hdsMover = vdsMover->list;

		while (hdsMover != NULL)
		{
			ctnPtr = (ctn*)malloc(sizeof(ctn)); 
			
			if (ctnPtr == NULL)
			{
				printf("Memory Allocation Error\n");
				exit(1);				
			}
			
			ctnPtr->leftChild = NULL;
			ctnPtr->rightChild = NULL;
			ctnPtr->nextTree = NULL;
			ctnPtr->parent = NULL;
			ctnPtr->ptrToAggregationTreeNode = hdsMover->ptr;
			ctnPtr->id = hdsMover->ptr->id;
			ctnPtr->ptrToAggregationTreeNode->myForests = ctnPtr; 
			moverPtr = ctnPtr;
			
			for (i = 0; i < hdsMover->ptr->num_children; i++)
			{

				moverPtr->nextTree = hdsMover->ptr->arr[i]->myForests;

				while (moverPtr->nextTree != NULL)
				{
					moverPtr = moverPtr->nextTree;					
				}

			}

			hdsMover = hdsMover->next;
		}
		
		vdsMover = vdsMover->next;
	}
	printf("\n node_id = %d nodes in a forest = %d \n", ctnPtr->ptrToAggregationTreeNode->id, countForest(ctnPtr));

	return ctnPtr;
}

int countForest (ctn* ctnPtr)
{
	int sum = 0;
	
	while (ctnPtr != NULL)
	{
		sum++;
		ctnPtr = ctnPtr->nextTree;
	}

	return sum;
}

void printLinkedList(ctn* head)
{
	while(head != NULL)
	{
		printf("%d\n",head->id);
		head = head->nextTree;
	}	
}

ctn *sortLinkedList( ctn *start )
{
    ctn *p, *q, *top;
    int changed = 1;

    if( (top = (ctn*)malloc(sizeof(ctn))) == NULL) {
        printf("Memory Allocation error.\n" );
        exit(1);
    }

    top->nextTree = start;
    if( start != NULL && start->nextTree != NULL ) {

        while(changed) {
            changed = 0;
            q = top;
            p = top->nextTree;
            while( p->nextTree != NULL ) {
                if( p->id > p->nextTree->id ) {
                    q->nextTree = switchLinkedListElements( p, p->nextTree );
                    changed = 1;
                }
                q = p;
                if( p->nextTree != NULL )
                    p = p->nextTree;
            }
        }
    }

    p = top->nextTree;
    free( top );
    return p;
}

ctn *switchLinkedListElements( ctn *l1, ctn *l2 )
{
    l1->nextTree = l2->nextTree;
    l2->nextTree = l1;
    return l2;
}