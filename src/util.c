#include "../lib/util.h"

int countTree(struct node *head)
{
	//count number of nodes in tree and return
	int i, sum;
	int num_children;

	// printf("smiale\n");
	// printf("%d\n",num_children);
	sum = 1;
	
	if(!head)
		return 0;

	num_children = head->num_children;

	for( i=0; i < num_children; i++)
	{
		sum += countTree(head->arr[i]);
	}
	
	return sum;
}