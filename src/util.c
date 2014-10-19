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

void printDataStr (struct verticalDataStr* vdsMover)
{
	struct horizontalDataStr* hdsMover;

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

struct commitmentTreeNode* createCommitmentTree (struct verticalDataStr* vdsMover)
{
	int i, j;
	struct horizontalDataStr* hdsMover;
	struct commitmentTreeNode* ctnPtr;
	struct commitmentTreeNode* myChildForest;
	struct commitmentTreeNode* moverPtr;
	
	while (vdsMover != NULL)
	{
		hdsMover = vdsMover->list;

		while (hdsMover != NULL)
		{
			ctnPtr = (struct commitmentTreeNode*)malloc(sizeof(struct commitmentTreeNode)); 
			
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

int countForest (struct commitmentTreeNode* ctnPtr)
{
	int sum = 0;
	
	while (ctnPtr != NULL)
	{
		sum++;
		ctnPtr = ctnPtr->nextTree;
	}

	return sum;
}

void printLinkedList(struct commitmentTreeNode* head)
{
	while(head != NULL)
	{
		printf("%d\n",head->id);
		head = head->nextTree;
	}	
}

CTN *sortLinkedList( CTN *start )
{
    CTN *p, *q, *top;
    int changed = 1;

    if( (top = (CTN*)malloc(sizeof(CTN))) == NULL) {
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

CTN *switchLinkedListElements( CTN *l1, CTN *l2 )
{
    l1->nextTree = l2->nextTree;
    l2->nextTree = l1;
    return l2;
}