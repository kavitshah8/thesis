#pragma once

struct aggregationTreeNode 
{
	int id;
	int depth;  // depth is to describe aggregationTreeNode property; HEIGHT is used to describe tree property
	int num_children;
	struct aggregationTreeNode* parent;
	struct aggregationTreeNode** arr;
  struct commitmentTreeNode* myForests;   //my forest comming to me
  // struct commitmentTreeNode* myForestsOut;  //my forest going out of me
};

typedef struct horizontalDataStr 
{ 
	struct aggregationTreeNode* ptr;
	struct horizontalDataStr* next;
} hds;

struct verticalDataStr 
{
	int depth;
	struct verticalDataStr* next;
	struct horizontalDataStr* list;
};

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
	struct aggregationTreeNode* ptrToAggregationTreeNode;
	struct commitmentTreeNode* leftChild;
	struct commitmentTreeNode* rightChild;	 
	struct commitmentTreeNode* parent;	 
	struct commitmentTreeNode* nextTree; // this is my linked list
} CTN;

int countTree (struct aggregationTreeNode*);
int depthOfNode (struct aggregationTreeNode*, struct aggregationTreeNode*);
void printTree (struct aggregationTreeNode*);

struct verticalDataStr* createDataStr (struct aggregationTreeNode**, int);
struct verticalDataStr* findPrevious (struct verticalDataStr*, struct verticalDataStr*);
void printDataStr (struct verticalDataStr*);

struct commitmentTreeNode* createCommitmentTree (struct verticalDataStr*);
int countForest (struct commitmentTreeNode*);
void printLinkedList (struct commitmentTreeNode*);
CTN* sortLinkedList (CTN*);
CTN* switchLinkedListElements (CTN*, CTN*);
