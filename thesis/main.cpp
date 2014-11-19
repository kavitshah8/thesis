#include "../header_files/util.h"

int main () 
{

	int t;

	atn *root;
	atn *queue[10000];

	vds *top;
	ctn *head;

	FILE *outFile;
	outFile = fopen("/home/kavit/thesis/output/data.txt","a");

	t = time(NULL);
	srand(t);
	printf("Seed to the random function = %d \n\n",t);
	fprintf(outFile, "Seed to the random function = %d \n\n",t);

	root = (atn*)malloc(sizeof(atn));

	if (root == NULL)
	{
		printf("Memory Allocation Error\n");
		fprintf(outFile, "Memory Allocation Error\n");
		exit(1);
	}

	createAggregationTree(root, queue);
	printf("\nNumber of nodes in tree = %d\n\n",countDescendants(root));
	fprintf(outFile, "\nNumber of nodes in tree = %d\n\n",countDescendants(root));
	
	printf("Traversing tree using DFS-post order\n\n");
	fprintf(outFile, "Traversing tree using DFS-post order\n\n");
	printAggregationTree(root, outFile); 
	
	top = createDataStr(queue);
	printDataStr(top, outFile);
	
	root = createCommitmentTree(top);
	printCommitmentTree(root, outFile);
	printf("\n");

	fclose(outFile);
	return 0;
}
