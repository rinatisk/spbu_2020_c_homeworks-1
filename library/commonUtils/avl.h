#ifndef SPBU_2020_C_HOMEWORKS_1_AVL_H
#define SPBU_2020_C_HOMEWORKS_1_AVL_H

#include <stdbool.h>

typedef struct AVLTree AVLTree;

AVLTree *createTree();

bool removeTree(AVLTree *tree);

bool exists(AVLTree *tree, int value);
void addValue(AVLTree *tree, int value);
void removeValue(AVLTree *tree, int value);

void printAscending(AVLTree *tree);
void printNodeAndChildrenForm(AVLTree* tree);
void printDescending(AVLTree* tree);


#endif //SPBU_2020_C_HOMEWORKS_1_AVL_H
