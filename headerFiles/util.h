#pragma once

struct node 
{
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;
  struct commitmentTreeNode* myForests;   //my forest comming  to me
	// struct label* label;
};

struct horizontal 
{ 
	struct node* ptr;
	struct horizontal* next;
};

struct vertical 
{
	int depth;
	struct vertical* next;
	struct horizontal* list;
};

struct commitmentTreeNode
{
	int height;
  struct data* label;
  struct signatureData* myforestsignatures;
	struct node* ptrToAggregationNode;
	struct commitmentTreeNode* leftChild;
	struct commitmentTreeNode* rightChild;	 
	struct commitmentTreeNode* parent;	 
	struct commitmentTreeNode* nextTree; // this is my linked list
};

int countTree (struct node*);
int depthOfNode (struct node*, struct node*);
void printTree (struct node**, int);

struct vertical* createDataStr (struct node**, int);
struct vertical* findPrevious (struct vertical*, struct vertical*);
void printDataStr (struct vertical*);