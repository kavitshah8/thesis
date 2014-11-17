#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../header_files/util.h"

int main () 
{

	int t;

	atn *root;
	atn *queue[10000];

	vds *top;
	ctn *head;

	t = time(NULL);
	srand(t);
	printf("Seed to the random function = %d \n\n",t);

	root = (atn*)malloc(sizeof(atn));

	if (root == NULL)
	{
		printf("Memory Allocation Error\n");
		exit(1);
	}

	createAggregationTree(root, queue);
	printf("\nNumber of nodes in tree = %d\n\n",countDescendants(root));
	printf("Traversing tree using DFS-post order\n\n");
	// printTree(root); 
	// printAggregationTree(root); 
	
	top = createDataStr(queue);
	printDataStr(top);
	
	root = createCommitmentTree(top);
	printCommitmentTree(root);
	printf("\n");

	return 0;
}
