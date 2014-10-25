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

