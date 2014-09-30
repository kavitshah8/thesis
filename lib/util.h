#pragma once

struct node
{
	int id;
	int depth;
	int num_children;
	struct node* parent;
	struct node** arr;
	// struct label* label;
};

int countTree(struct node*);
