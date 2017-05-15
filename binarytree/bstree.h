#ifndef _H_BSTREE
#define _H_BSTREE

typedef struct bstree BSTree;
typedef struct tnode TNode;
typedef void* TValue;
typedef int (*CompareFunc)(TValue, TValue);

BSTree *bstree_create(CompareFunc);

int bstree_add(BSTree* tree, TValue data);

int bstree_delete(BSTree* tree, TValue data);

TNode *bstree_find(BSTree *tree, TValue data);

void bstree_destroy(BSTree* tree);

#endif