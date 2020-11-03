#ifndef __BST_H__
#define __BST_H__

#include <stdbool.h>

typedef struct BinarySearchTree BinarySearchTree;

BinarySearchTree *createTree();

bool removeTree(BinarySearchTree *tree);

bool exists(BinarySearchTree *tree, int value);
bool addValue(BinarySearchTree *tree, int value);
bool removeValue(BinarySearchTree *tree, int value);

void printAscending(BinarySearchTree *tree);
void printNodeAndChildrenForm(BinarySearchTree* tree);
void printDescending(BinarySearchTree* tree);

#endif
