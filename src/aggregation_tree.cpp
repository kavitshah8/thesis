#include "../header_files/util.h"

void createAggregationTree (atn *root, atn **queue)
{
	// pseudo random tree generation algorithm in breadth first search fashion

	int N; // N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back;
	atn* iterator;
	
	N = NODES;
	front =	back = 0;

	// Handling the root seperately 
	iterator = queue[back] = root;
	
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
	
		iterator->arr = (atn**)malloc( sizeof(atn*) * iterator->numChildren ) ;

		if (iterator->arr == NULL)
		{
			printf("Memory Allocation Error\n");
			exit(1);
		}
		
		for (i = 0; i < iterator->numChildren; i++)
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

	printf("front = %d  back = %d N = %d\n\n", front, back, N);

	if (front == back && front == NODES)
	{
		printf("front == back == NODES :) \n\n");		
	}

}

int countDescendants (atn *ptr)
{
	int i, sum;
	int numChildren;

	sum = 1;
	
	if (!ptr)
		return 0;

	numChildren = ptr->numChildren;

	for (i = 0; i < numChildren; i++)
	{
		sum += countDescendants(ptr->arr[i]);
	}
	
	return sum;
}

int depthOfNode (atn *root, atn *ptr)
{
	int dep = 0;
	
	while (ptr != root)
	{
		ptr = ptr->parent;
		dep++;
	}
	
	return dep;
}

void printAggregationTree (atn *root, FILE *outFile)
{
	int i;
	atn *iterator;

	i = 0;

	iterator = root;

	if (iterator != NULL)
	{
		for (i = 0; i < iterator->numChildren; i++)
		{
			// try implementing without recurssion
			printAggregationTree(iterator->arr[i], outFile);
		}

		if (iterator->depth == 0)
		{
			printf("id = %d, depth = %d, numChildren = %d, parent = NULL\n", iterator->id, iterator->depth, iterator->numChildren );
			fprintf(outFile, "id = %d, depth = %d, numChildren = %d, parent = NULL\n", iterator->id, iterator->depth, iterator->numChildren);
		}
		else
		{
			printf("id = %d, depth = %d, numChildren = %d, parent's_id = %d\n ", iterator->id, iterator->depth, iterator->numChildren, iterator->parent->id );
			fprintf(outFile, "id = %d, depth = %d, numChildren = %d, parent's_id = %d\n ", iterator->id, iterator->depth, iterator->numChildren, iterator->parent->id );
		}
	}

}

void printAggregationTreeIteratively (atn *root)
{	
	stack<atn*> ms;
	
	atn *temp = root;

  while(!(ms.empty()) || temp)
  {
    if(temp)
  	{
			temp->count = 0;
    	ms.push(temp);

    	if (temp->count < temp->numChildren)
    	{	
	    	temp = temp->arr[temp->count];
	    	ms.top()->count++;	
    	}
	    else
	    {
	    	temp = ms.top();

				if (temp->depth == 0)
				{
					printf("id = %d, depth = %d, numChildren = %d, parent = NULL\n", temp->id, temp->depth, temp->numChildren );
				}
				else
				{
					printf("id = %d, depth = %d, numChildren = %d, parent's_id = %d\n ", temp->id, temp->depth, temp->numChildren, temp->parent->id );
				}	    	

				ms.pop();
				temp = ms.top();
	    }

    }
  }

}