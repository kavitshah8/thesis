#include "../header_files/util.h"
#include <stdio.h>
#include <stdlib.h>

vds* createDataStr (atn **queue) 
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

	while (front < NODES)
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
	FILE *outFile;

	outFile = fopen("/home/kavit/thesis/output/data.txt","w");

	printf("\n\nPrinting createDataStr : \n\n");
	fprintf(outFile, "\n\nPrinting createDataStr : \n\n");

	while (vdsMover != NULL)
	{
		hdsMover = vdsMover->list;
		
		printf("depth = %d\n", hdsMover->ptr->depth);
		fprintf(outFile, "%d\n", hdsMover->ptr->depth);

		while (hdsMover != NULL)
		{
			printf("id = %d, numChildren = %d ||",hdsMover->ptr->id, hdsMover->ptr->numChildren);
			fprintf(outFile, "id = %d, numChildren = %d ||",hdsMover->ptr->id, hdsMover->ptr->numChildren);
			hdsMover = hdsMover->next;
		}

		printf("\n\n");
		
		vdsMover = vdsMover->next;
	}
	fclose(outFile);
}