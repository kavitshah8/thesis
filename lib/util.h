#pragma once

struct node {
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;
	// struct label* label;
};

struct horizontal { 
	struct node* ptr;
	struct horizontal* nextnode;
};

struct vertical {
	int depth;
	struct vertical* next;
	struct horizontal* list;
};

int countTree (struct node*);
int depthOfNode (struct node*, struct node*);
void printTree (struct node**, int);

struct vertical* createDataStr (struct node**, int);
struct vertical* findPrevious (struct vertical*, struct vertical*);
void printDataStr(struct vertical*);