#pragma once

typedef struct aggregationTreeNode 
{
	int id;
	int depth;  // depth is to describe aggregationTreeNode property; HEIGHT is used to describe tree property
	int num_children;
	struct aggregationTreeNode* parent;
	struct aggregationTreeNode** arr;
  struct commitmentTreeNode* myForests;   //my forest comming to me
  // struct commitmentTreeNode* myForestsOut;  //my forest going out of me
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
	struct commitmentTreeNode* parent;	 
	struct commitmentTreeNode* nextTree; // this is my linked list
} CTN;

int countTree (atn*);
int depthOfNode (atn*, atn*);
void printTree (atn*);

vds* createDataStr (atn**, int);
vds* findPrevious (vds*, vds*);
void printDataStr (vds*);

struct commitmentTreeNode* createCommitmentTree (vds*);
int countForest (struct commitmentTreeNode*);
void printLinkedList (struct commitmentTreeNode*);
CTN* sortLinkedList (CTN*);
CTN* switchLinkedListElements (CTN*, CTN*);
