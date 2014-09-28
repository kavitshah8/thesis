#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct node
{
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;
	// struct label* label;
};

int countTree(struct node *head);
int depthOfNode(struct node *head, struct node *ptr);
void printTree(struct node**, int);

int main()
{
	int N, NN; // NN is total number of nodes in the aggregation tree
						// N is the toal number of remaining nodes in the aggregation tree generation
	int i, j;
	int front, back;
	struct node* root;
	struct node* iterator;
	struct vertex* commitmentTree;
	struct node* queue[10000];
	//queue = (struct node**)malloc(sizeof(struct node*) * (N+1) );

	srand(time(NULL));

	N = NN = 200;
	front =	back = 0;

	// Handling the root seperately 
	root = iterator = queue[back] = (struct node*)malloc(sizeof(struct node));
	iterator->id = back;
	iterator->depth = 0;
	iterator->parent = NULL;
	back++;
	N--;	

	while( front < NN )
	{
	
		if( back < NN )
		{
			iterator->num_children = rand() % 4;
		}
		else
		{
			iterator->num_children = 0;	
		}


		// Gives you a tree
		if( iterator == root && iterator->num_children == 0 )
		{
			iterator->num_children = 1;
		}
		else
		{
			if( iterator != root  && iterator->num_children == 0 )
			{
				int dep = 1 + (iterator->parent->depth);
				int sum = 0;
				int tt = 0;
				while( tt < back )
				{
					if( queue[tt]->depth == dep )
						break;
					tt++;
				}
				while( tt < back )
				{
					sum += queue[tt]->num_children;
					tt++;
				}
				if( !sum ) 
					iterator->num_children = 1;
			}
		}
	
		if( N > 0 )
		{		
			N = N - iterator->num_children;
		}
		else
		{
			printf("Back is getting outside range\n");
		}
		
		iterator->arr = (struct node**)malloc( sizeof(struct node*) * iterator->num_children ) ;
		
		for( i=0; i < iterator->num_children; i++ )
		{
			iterator->arr[i] = (struct node*)malloc( sizeof(struct node) ) ;
			iterator->arr[i]->id = back;
			iterator->arr[i]->depth = iterator->depth + 1;
			iterator->arr[i]->parent = iterator;
			iterator->arr[i]->num_children=0;
			iterator->arr[i]->arr=NULL;
			queue[back] = iterator->arr[i];
			back++;
		}				
		
		if( front > back )
		{
			printf("Queue is not working as supposed to \n");
			break;
		}
		
		// printf("%p\n", queue[front]);
		front++;
		iterator = queue[front];
		
	}

	printTree(queue,front);
	printf("\n Number of nodes in tree = %d\n",countTree(queue[0]));
	printf("\n front %d   %d\n", front, back);
	// free(root->arr);
	
	return 0;
}

void printTree(struct node** arr, int total)
{
	int i, temp, depth;
	
	depth = arr[0]->depth;
	
	for( i=0; i < total; i++ ){
	
		temp = arr[i]->depth;
	
		if( temp != depth )
		{
			depth = temp;
			printf("\n \n");
		}
	
		if( depth == 0 )
		{
			printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent = NULL || ", i, arr[i]->id, arr[i]->depth, arr[i]->num_children );
		}
		else
		{
			printf("( Index %d ) Node's id = %d depth = %d num_children = %d parent's_id = %d || ", i, arr[i]->id, arr[i]->depth, arr[i]->num_children, arr[i]->parent->id );
		}
	}
}

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

int depthOfNode(struct node *head, struct node *ptr)
{
	int dep=0;
	
	while(ptr!=head)
	{
		ptr=ptr->parent;
		dep++;
	}
	
	return dep;
}