#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../header_files/util.h"

int main () 
{

	atn *root;
	atn *queue[10000];

	vds *top;
	ctn *head;

	root = (atn*)malloc(sizeof(atn));

	if (root == NULL)
	{
		printf("Memory Allocation Error\n");
		exit(1);
	}

	createAggregationTree(root, queue);
	printf("\nNumber of nodes in tree = %d\n",countTree(root));
	printf("Traversing tree using DFS-post order\n\n");
	printTree(root); 
	
	top = createDataStr(queue, NODES);
	printDataStr(top);
	
	root = createCommitmentTree(top);
	printCommitmentTree(root);
	printf("\n");

	return 0;
}
