#pragma once

#define NODES 15
#define DIVISOR 4	
#define HEIGHT 0

typedef struct aggregationTreeNode 
{
	int id;
	int depth;  // depth is to describe aggregationTreeNode property; HEIGHT is used to describe tree property
	int numChildren;
	struct aggregationTreeNode* parent;
	struct aggregationTreeNode** arr;
  struct commitmentTreeNode* myForests;   //my forest comming to me
} atn;

typedef struct horizontalDataStr 
{ 
	atn* ptr;
	struct horizontalDataStr* next;
} hds;

typedef struct verticalDataStr 
{
	int depth;
	struct verticalDataStr* next;
	struct horizontalDataStr* list;
} vds;

struct label
{	
	int count;
	int value;
	int commitment;
};

typedef struct commitmentTreeNode
{
	int id;
	int height;
  struct label* labelData;
  struct signatureData* myforestsignatures;
	atn* ptrToAggregationTreeNode;
	struct commitmentTreeNode* leftChild;
	struct commitmentTreeNode* rightChild;	 
	struct commitmentTreeNode* parentInctn;	 
	struct commitmentTreeNode* nextTree; // this is my linked list
} ctn;

void createAggregationTree (atn*, atn**);
int countTree (atn*);
int depthOfNode (atn*, atn*);
void printTree (atn*);
void printAggregationTree (atn *iterator);


vds* createDataStr (atn**, int);
vds* findPrevious (vds*, vds*);
void printDataStr (vds*);

atn* createCommitmentTree (vds*);
int countForest (struct commitmentTreeNode*);
void printLinkedList (struct commitmentTreeNode*);
ctn* sortLinkedList (ctn*);
ctn* switchLinkedListElements (ctn*, ctn*);
void printCommitmentTree (atn*);
void MorrisTraversal (ctn *root);
