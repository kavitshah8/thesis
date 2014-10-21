#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

int countTree (atn *head)
{
	int i, sum;
	int numChildren;

	sum = 1;
	
	if (!head)
		return 0;

	numChildren = head->numChildren;

	for ( i=0; i < numChildren; i++)
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
	int i = 0;
	
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

vds* createDataStr (atn **queue, int nodes) 
{

	int dep;
	int front;
	
	vds *top = NULL;
	vds *tempverticalDataStr;
	vds *mover;
	
	hds *temphorizontalDataStr;

	atn *ptr;
	atn *head; 

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

vds* findPrevious (vds *head, vds *target)
{
	vds *walker;

	walker = head;
	
	while (walker->next != target)
	{
		walker = walker->next;
	}
	return walker;
}

void printDataStr (vds *vdsMover)
{
	hds *hdsMover;

	printf("\n\nPrinting createDataStr : \n\n");

	while (vdsMover != NULL)
	{
		hdsMover = vdsMover->list;
		
		printf("depth = %d\n", hdsMover->ptr->depth);

		while (hdsMover != NULL)
		{
			printf("id = %d, numChildren = %d ||",hdsMover->ptr->id, hdsMover->ptr->numChildren);
			hdsMover = hdsMover->next;
		}

		printf("\n\n");
		
		vdsMover = vdsMover->next;
	}
}

ctn* createCommitmentTree (vds *vdsMover)
{
	int i, j, height;
	hds *hdsMover;
	ctn *ctnPtr;
	ctn *myChildForest;
	ctn *moverPtr;
	ctn *aggregator;
	
	height = 0;

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
			
			// hdsMover->ptr points to the node in aggregation tree which you are processing
			ctnPtr->id = hdsMover->ptr->id;
			ctnPtr->height = 0;
			// ctnPtr->height = height;
			ctnPtr->ptrToAggregationTreeNode = hdsMover->ptr;
			ctnPtr->leftChild = NULL;
			ctnPtr->rightChild = NULL;
			ctnPtr->nextTree = NULL;
			ctnPtr->parentInctn = NULL;

			hdsMover->ptr->myForests = ctnPtr; 
			moverPtr = ctnPtr;
			
			if (hdsMover->ptr->numChildren != 0)
			{
				// Attach all my children to myforest
				for (i = 0; i < hdsMover->ptr->numChildren; i++)
				{
					moverPtr->nextTree = hdsMover->ptr->arr[i]->myForests;

					while (moverPtr->nextTree != NULL)
					{
						moverPtr = moverPtr->nextTree;					
					}
				}

				hdsMover->ptr->myForests = sortLinkedList(hdsMover->ptr->myForests);
				moverPtr = hdsMover->ptr->myForests;

				while (moverPtr->nextTree != NULL)
				{
					if (moverPtr->height != moverPtr->nextTree->height)
					{
						moverPtr = moverPtr->nextTree;
					}
					else
					{
						aggregator = (ctn*)malloc(sizeof(ctn));
						// aggregator->id = ?;
						aggregator->height = moverPtr->height + moverPtr->nextTree->height;
						// aggregator->ptrToAggregationTreeNode = ? ;
						aggregator->leftChild = moverPtr;
						aggregator->rightChild = moverPtr->nextTree;
						aggregator->parentInctn = NULL;
						aggregator->nextTree = moverPtr->nextTree->nextTree;

						// sets parents & removes from the LL
						moverPtr->parentInctn = moverPtr->nextTree->parentInctn = aggregator;
						moverPtr->nextTree = moverPtr->nextTree->nextTree = NULL;
						
						// Inserts aggregator to the LL
						moverPtr = aggregator;
						// sort new LL
						hdsMover->ptr->myForests = sortLinkedList(hdsMover->ptr->myForests);
						moverPtr = hdsMover->ptr->myForests;
					}
				}
				
				hdsMover = hdsMover->next;

			}
			else
			{
				hdsMover = hdsMover->next;
			}
		}
		
		vdsMover = vdsMover->next;
		height++;
	}

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

void printLinkedList(ctn *head)
{
	printf("Printing a LL:\n");
	while(head != NULL)
	{
		printf("%d\n",head->height);
		head = head->nextTree;
	}	
}

ctn *sortLinkedList(ctn *top)
{
  ctn *p, *prev;
  int changed;
          
  changed = 1;

  if( top != NULL && top->nextTree != NULL ) 
  {
    while(changed)
    {
      changed = 0;
  		prev = NULL;
      p = top;
      while(p->nextTree != NULL)
      {
      	if(p->height > p->nextTree->height)
        {
        	if(prev)
          {
          	prev->nextTree = switchLinkedListElements( p, p->nextTree );
            prev = prev->nextTree;
          }
          else
          {
          	top = switchLinkedListElements( p, p->nextTree );
            prev = top;
          }
         	changed = 1;
        }
        else
        {
        	prev = p;
          p = p->nextTree;
        }
      }
    }
  }
	
	return top;
}

ctn *switchLinkedListElements(ctn *l1, ctn *l2)
{
    l1->nextTree = l2->nextTree;
    l2->nextTree = l1;
    return l2;
}