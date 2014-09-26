// This file contains the necessary data structure which will help us creating a commitment forest

	//  Given depth, assuming max num children are 3 as we do mod 4
	// 	Max number of nodes in a tree will be (3^N+1)/(3-1) [geometric series]
	

	// max_nodes = pow( 3.0,N+1 )/(3.0 - 1);

	// max_nodes = (int)pow(3.0,5.0)/2;

	// printf("%d\n\n",max_nodes);
	// queue = (struct node**)malloc(sizeof(struct node*) * max_nodes );

#include <stdio.h>
#include <stdlib.h>

struct node
{
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;

	//struct forest * myforest
};

struct vertex
{
	//data
	struct vertex* vertParent;
	struct vertex* left;
	struct vertex* right;
	struct node* aggNode;
};


struct horizontal
{ 
	struct node *ptr;
	struct horizontal *nextnode;
};


struct comOne
{
	int depth;
	struct comOne *next;
	struct horizontal *list;
};

int main()
{
	return 1;
}

struct comOne * createDataStr(struct node *head)
{

	struct comOne* top=NULL;
	struct horizontal *temphorizontal;
	struct comOne *tempcomOne;
	struct comOne *mover;
	int dep;

	struct node *ptr;
	
	while(1)
	{
	//write a loop to visit ech node in tree

		dep=depthOfNode(head, ptr);
		if(top==NULL)
		{
				top = (struct comOne*)malloc(sizeof(struct comOne) );
				top->list=(struct horizontal*)malloc(sizeof(struct horizontal) );
				top->list->ptr=ptr;
				top->depth=dep;
				top->next=NULL;
				continue;


		}
		else
		{
			mover=top;
			while(mover->depth>dep)
			{  
				mover =mover->next;
				if(!mover)
					break;
			}

			if(!mover)
			{
				tempcomOne=(struct comOne*)malloc(sizeof(struct comOne) );
				tempcomOne->depth=dep;
				temphorizontal=(struct horizontal*)malloc(sizeof(struct horizontal) );
				temphorizontal->ptr=ptr;
				temphorizontal->nextnode=NULL;

				//insert tempcomOne a end of vertical link list

			}
			else if(mover->depth==dep)
			{
				temphorizontal=(struct horizontal*)malloc(sizeof(struct horizontal) );
				temphorizontal->ptr=ptr;
				temphorizontal->nextnode=mover->list;
				mover->list=temphorizontal;

			}
			else
			{
				//mover->depth<dep
				tempcomOne=(struct comOne*)malloc(sizeof(struct comOne) );
				tempcomOne->depth=dep;
				temphorizontal=(struct horizontal*)malloc(sizeof(struct horizontal) );
				temphorizontal->ptr=ptr;
				temphorizontal->nextnode=NULL;

				//insert tempcomOne infrot of mover in vertical link list


			}




		}



	}



	return top;
}