#pragma once

struct aggregationTreeNode 
{
	int id;
	int depth;  // depth is to describe aggregationTreeNode property; HEIGHT is used to describe tree property
	int num_children;
	struct aggregationTreeNode* parent;
	struct aggregationTreeNode** arr;
  struct commitmentTreeNode* myForests;   //my forest comming  to me
	// struct label* label;
};

struct horizontalDataStr 
{ 
	struct aggregationTreeNode* ptr;
	struct horizontalDataStr* next;
};

struct verticalDataStr 
{
	int depth;
	struct verticalDataStr* next;
	struct horizontalDataStr* list;
};

struct commitmentTreeNode
{
  struct data* label;
  struct signatureData* myforestsignatures;
	struct aggregationTreeNode* ptrToAggregationNode;
	struct commitmentTreeNode* leftChild;
	struct commitmentTreeNode* rightChild;	 
	struct commitmentTreeNode* parent;	 
	struct commitmentTreeNode* nextTree; // this is my linked list
};

int countTree (struct aggregationTreeNode*);
int depthOfNode (struct aggregationTreeNode*, struct aggregationTreeNode*);
void printTree (struct aggregationTreeNode**, int);

struct verticalDataStr* createDataStr (struct aggregationTreeNode**, int);
struct verticalDataStr* findPrevious (struct verticalDataStr*, struct verticalDataStr*);
void printDataStr (struct verticalDataStr*);