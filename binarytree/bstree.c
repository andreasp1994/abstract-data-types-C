#include "bstree.h"
#include <stdlib.h>
#include <stdio.h>

struct tnode {
	TValue value;
	TNode *left;
	TNode *right;
};

struct bstree {
	TNode *root;
	CompareFunc compare_func;
};

/* This is a compare function for integers
*  returns positive if v1 > v2
* 0 if they are equal
* negative if v1 < v2
*/
int cmp_func(TValue v1, TValue v2){
	int d1 = *((int *) v1);
	int d2 = *((int *) v2);
	return d1 - d2;
}

BSTree* bstree_create(CompareFunc func){
	BSTree* tree = NULL;
	if((tree = (BSTree *) malloc(sizeof(BSTree))) != NULL){
		tree->compare_func = func;
		return tree;
	}
	return NULL;
}

int bstree_add(BSTree *tree, TValue data){
	int result = 0;
	TNode *new_node = (TNode *) malloc(sizeof(TNode)); //error handling there
	new_node->value = data;

	TNode** currentnode = &(tree->root);
	while(*currentnode != NULL){
		if ((tree->compare_func(data, (*currentnode)->value)) <= 0) {
			currentnode = &((*currentnode)->left);
		} else {
			currentnode = &((*currentnode)->right);
		}
	}
	*currentnode = new_node;
	result = 1;
	return result;
}

TNode *bstree_find(BSTree *tree, TValue data){
	TNode *currentnode = tree->root;
	while(currentnode != NULL){
		int cmp_value = tree->compare_func(data, currentnode->value);
		if(cmp_value == 0) return currentnode;
		else if(cmp_value < 0) currentnode = currentnode->left;
		else if(cmp_value > 0) currentnode = currentnode->right;
	}
	return NULL;
}

void bstree_destroy_node(TNode *node){
	if (node != NULL) {
		bstree_destroy_node(node->left);
		free(node->left);
		bstree_destroy_node(node->right);
		free(node->right);
	}
}

void bstree_destroy(BSTree *tree){
	bstree_destroy_node(tree->root);
	free(tree->root);
	free(tree);
}

void dfs(TNode *node){
	if(node != NULL) {
		printf("%d->(", *((int *) node->value));
		dfs(node->left);
		printf("%s", ", ");
		dfs(node->right);
		printf("%s", ") ");
	} else {
		printf("%s", "NULL" );
	}
	return;
}

int main(){
	
	BSTree* mytree = bstree_create(&cmp_func);
	int a = 10;
	int b = 5;
	int c = 15;
	int d = 2;
	int e = 7;

	bstree_add(mytree, &a);
	bstree_add(mytree, &b);
	bstree_add(mytree, &c);
	bstree_add(mytree, &d);
	bstree_add(mytree, &e);

	dfs(mytree->root);
	printf("\n");

	int value_to_find = 7;
	TNode *node = bstree_find(mytree, &a);
	if(node != NULL){
		printf("%s %d\n", "FOUND:", value_to_find);
	} else {
		printf("%s %d\n", "NOT FOUND", value_to_find);
	}

	bstree_destroy(mytree);
}

