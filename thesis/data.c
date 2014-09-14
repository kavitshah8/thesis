#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node {
	int children;
	struct node** arr;
};

struct node* makenode(){
	return (struct node*)malloc(sizeof(struct node));
};

int main(){
	int N = 12;
	struct node* root;
	int i,j;

	srand(time(NULL));

	N--;
	root = makenode();
	root->children = ( 1 + rand() ) % ( N + 1 );
	N = N - ( root->children );
	root->arr = (struct node**)malloc( sizeof(struct node) * root->children ) ;

	for( i = 0; i < (root->children); i++){
		j = rand() % ( N + 1 );
		N = N - j;
		root->arr = (struct node**)malloc( sizeof(struct node) * j );
		root->arr++;
	}

//	free(root->arr);
	return 0;
}