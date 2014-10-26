#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

atn* createCommitmentTree (vds *vdsMover)
{
	int i, j;
	int const HEIGHT = 0;

	hds *hdsMover;
	atn *root;
	ctn *ctnPtr;
	ctn *myChildForest;
	ctn *moverPtr;
	ctn *aggregator;
	ctn *prev;
	
	hdsMover = NULL;
	root = NULL;
	ctnPtr = myChildForest = moverPtr = aggregator = prev = NULL;

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
			ctnPtr->height = HEIGHT;
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

					// Might not need the following loop (?)
					while (moverPtr->nextTree != NULL)
					{
						moverPtr = moverPtr->nextTree;					
					}
				}

				hdsMover->ptr->myForests = sortLinkedList(hdsMover->ptr->myForests);
				moverPtr = hdsMover->ptr->myForests;

				// Huffman coding
				while (moverPtr->nextTree != NULL)
				{
					if (moverPtr->height != moverPtr->nextTree->height)
					{
						prev = moverPtr;
						moverPtr = moverPtr->nextTree;
					}
					else
					{
						aggregator = (ctn*)malloc(sizeof(ctn));
						// aggregator->id = ?;
						aggregator->height = moverPtr->height + 1;
						// aggregator->ptrToAggregationTreeNode = ? ;
						aggregator->leftChild = moverPtr;
						aggregator->rightChild = moverPtr->nextTree;
						aggregator->parentInctn = NULL;
						aggregator->nextTree = moverPtr->nextTree->nextTree;

						// sets parents & removes from the LL
						moverPtr->parentInctn = moverPtr->nextTree->parentInctn = aggregator;
						moverPtr->nextTree->nextTree = NULL;
						moverPtr->nextTree = NULL;
						
						// Inserts aggregator to the LL (?)
						if (hdsMover->ptr->myForests == moverPtr)
						{	
							hdsMover->ptr->myForests = aggregator;
						}
						else
						{
							
							while(prev->nextTree != moverPtr)
							{
								prev = prev->nextTree;	
							}
							prev->nextTree = aggregator;
						}

						// sort new LL
						hdsMover->ptr->myForests = sortLinkedList(hdsMover->ptr->myForests);
						moverPtr = hdsMover->ptr->myForests;
					}
				}
				
			}
			hdsMover = hdsMover->next;
		}
		
		if (vdsMover->next == NULL)
		{
			return vdsMover->list->ptr;
		}
		vdsMover = vdsMover->next;
	}
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

void printLinkedList (ctn *head)
{
	printf("Printing a LL:\n");
	while(head != NULL)
	{
		printf("%d\n",head->height);
		head = head->nextTree;
	}	
}

ctn *sortLinkedList (ctn *top)
{
  ctn *p, *prev;
  int changed;
          
  changed = 1;

  if (top != NULL && top->nextTree != NULL) 
  {
    while (changed)
    {
      changed = 0;
  		prev = NULL;
      p = top;
      
      while (p->nextTree != NULL)
      {
      
      	if (p->height > p->nextTree->height)
        {
         	if (prev)
          {
          	prev->nextTree = switchLinkedListElements(p, p->nextTree);
            prev = prev->nextTree;
          }
          else
          {
          	top = switchLinkedListElements(p, p->nextTree);
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

ctn *switchLinkedListElements (ctn *l1, ctn *l2)
{
  l1->nextTree = l2->nextTree;
  l2->nextTree = l1;
  return l2;
}

void printCommitmentTree (atn* root)
{
	ctn *mover;

	mover = root->myForests;
	
	printf("Printing a commitment Forest\n");

	while (mover)
	{
		if (!mover->height)
		{
			printf("height = %d\n",mover->height);
		}
		else
		{
			MorrisTraversal(mover);
		}
		mover = mover->nextTree;		
	}
}

void MorrisTraversal (ctn *root)
{
  ctn *current, *pre;
 
  if (root == NULL)
     return; 
 
  current = root;

  while (current != NULL)
  {                 
    if (current->leftChild == NULL)
    {
      printf(" %d ", current->height);
      current = current->rightChild;      
    }    
    else
    {
      /* Find the inorder predecessor of current */
      pre = current->leftChild;
      while (pre->rightChild != NULL && pre->rightChild != current)
        pre = pre->rightChild;
 
      /* Make current as rightChild child of its inorder predecessor */
      if (pre->rightChild == NULL)
      {
        pre->rightChild = current;
        current = current->leftChild;
      }
             
      /* Revert the changes made in if part to restore the original 
        tree i.e., fix the rightChild child of predecssor */   
      else 
      {
        pre->rightChild = NULL;
        printf(" %d ",current->height);
        current = current->rightChild;      
      } /* End of if condition pre->rightChild == NULL */
    } /* End of if condition current->leftChild == NULL*/
  } /* End of while */
}