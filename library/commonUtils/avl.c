#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "numericOperations.h"

typedef struct AVLTreeNode {
    int value;
    int height;
    struct AVLTreeNode* leftChild;
    struct AVLTreeNode* rightChild;
} AVLTreeNode;

typedef struct AVLTree {
    struct AVLTreeNode* root;
} AVLTree;

enum Direction {
    left,
    right,
    none
};

AVLTree* createTree()
{
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    newTree->root = NULL;
    return newTree;
}

bool existsRecursive(AVLTreeNode* node, int value)
{
    if (value == node->value) {
        return true;
    }
    if (value < node->value && node->leftChild != NULL) {
        return existsRecursive(node->leftChild, value);
    }
    if (value > node->value && node->rightChild != NULL) {
        return existsRecursive(node->rightChild, value);
    }
    return false;
}

bool isEmpty(AVLTree* tree)
{
    return (tree->root == NULL);
}

int getHeight(AVLTreeNode* node)
{
    return node == NULL ? 0 : node->height;
}

int getBalanceFactor(AVLTreeNode* node)
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

void updateHeight(AVLTreeNode* node)
{
    int heightLeft = getHeight(node->leftChild);
    int heightRight = getHeight(node->rightChild);
    node->height = max(heightLeft, heightRight) + 1;
}

bool exists(AVLTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return existsRecursive(tree->root, value);
}

AVLTreeNode* createNode(int value)
{
    AVLTreeNode* node = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    node->rightChild = NULL;
    node->leftChild = NULL;
    node->value = value;
    node->height = 0;
    return node;
}

AVLTreeNode* rotateRight(AVLTreeNode* root)
{
    if (root == NULL) {
        return NULL;
    }
    AVLTreeNode* pivot = root->leftChild;
    root->leftChild = pivot->rightChild;
    pivot->rightChild = root;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

AVLTreeNode* rotateLeft(AVLTreeNode* root)
{
    if (root == NULL) {
        return NULL;
    }
    AVLTreeNode* pivot = root->rightChild;
    root->rightChild = pivot->leftChild;
    pivot->leftChild = root;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

AVLTreeNode* balance(AVLTreeNode* root)
{
    updateHeight(root);
    if (getBalanceFactor(root) == 2) {
        if (getBalanceFactor(root->rightChild) < 0)
            root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }
    if (getBalanceFactor(root) == -2) {
        if (getBalanceFactor(root->leftChild) > 0)
            root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    return root;
}

AVLTreeNode* addValueRecursive(AVLTreeNode* node, int value)
{
    if (value < node->value) {
        if (node->leftChild == NULL) {
            node->leftChild = createNode(value);
        } else
            node->leftChild = addValueRecursive(node->leftChild, value);
    }
    if (value > node->value) {
        if (node->rightChild == NULL) {
            node->rightChild = createNode(value);
        } else
            node->rightChild = addValueRecursive(node->rightChild, value);
    }
    return balance(node);
}

void addValue(AVLTree* tree, int value)
{
    if (isEmpty(tree)) {
        tree->root = createNode(value);
    }
    tree->root = addValueRecursive(tree->root, value);
}

bool isLeaf(AVLTreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

AVLTreeNode* getMinimum(AVLTreeNode* root)
{
    if (root == NULL) {
        return NULL;
    }

    if (root->leftChild != NULL) {
        return getMinimum(root->leftChild);
    }

    return root;
}

AVLTreeNode* removeMinimum(AVLTreeNode* root)
{
    if (root == NULL) {
        return NULL;
    }

    if (root->leftChild == NULL) {
        return root->rightChild;
    }

    root->leftChild = removeMinimum(root->leftChild);
    return balance(root);
}

AVLTreeNode* removeRecursive(int value, AVLTreeNode* root)
{
    if (root == NULL) {
        return NULL;
    }

    if (value < root->value) {
        root->leftChild = removeRecursive(value, root->leftChild);
    }
    if (value > root->value) {
        root->rightChild = removeRecursive(value, root->rightChild);
    }
    if (value == root->value) {
        AVLTreeNode* leftChild = root->leftChild;
        AVLTreeNode* rightChild = root->rightChild;

        if (rightChild == NULL) {
            free(root);
            return leftChild;
        }

        AVLTreeNode* minimum = getMinimum(rightChild);
        minimum->rightChild = removeMinimum(rightChild);
        minimum->leftChild = leftChild;
        free(root);
        return balance(minimum);
    }

    return balance(root);
}

void removeValue(AVLTree* tree, int value)
{
    if (tree == NULL) {
        return;
    }
    if (exists(tree, value)) {
        tree->root = removeRecursive(value, tree->root);
    }
}

void printNodeAndChildrenRecursive(AVLTree* tree, AVLTreeNode* node)
{
    if (node != NULL) {
        printf("(");
        if (isLeaf(node)) {
            printf(" %d null null ", node->value);
        }
        if ((node->leftChild == NULL) && (node->rightChild != NULL)) {
            printf(" %d null ", node->value);
            printNodeAndChildrenRecursive(tree, node->rightChild);
        }
        if ((node->rightChild == NULL) && (node->leftChild != NULL)) {
            printf(" %d null", node->value);
            printNodeAndChildrenRecursive(tree, node->leftChild);
        }
        if ((node->leftChild != NULL) && (node->rightChild != NULL)) {
            printf(" %d ", node->value);
            printNodeAndChildrenRecursive(tree, node->leftChild);
            printNodeAndChildrenRecursive(tree, node->rightChild);
        }
        printf(")");
    }
}

void printNodeAndChildrenForm(AVLTree* tree)
{
    printf("Here's your tree: ");
    printNodeAndChildrenRecursive(tree, tree->root);
    printf("\n");
}

void printAscendingRecursive(AVLTreeNode* node)
{
    if (node == NULL)
        return;
    if (node->leftChild != NULL) {
        printAscendingRecursive(node->leftChild);
    }
    printf("%d ", node->value);
    if (node->rightChild != NULL) {
        printAscendingRecursive(node->rightChild);
    }
}

void printAscending(AVLTree* tree)
{
    printf("Here's your tree: ( ");
    if (tree != NULL)
        printAscendingRecursive(tree->root);
    printf(")\n");
}

void printDescendingRecursive(AVLTreeNode* node)
{
    if (node == NULL)
        return;
    if (node->rightChild != NULL) {
        printDescendingRecursive(node->rightChild);
    }
    printf("%d ", node->value);
    if (node->leftChild != NULL) {
        printDescendingRecursive(node->leftChild);
    }
}

void printDescending(AVLTree* tree)
{
    printf("Here's your tree: ( ");
    if (tree != NULL)
        printDescendingRecursive(tree->root);
    printf(")\n");
}

bool removeTreeRecursive(AVLTree* tree, AVLTreeNode* node)
{
    if (node == NULL) {
        return false;
    }
    if (isLeaf(node)) {
        free(node);
        return true;
    }
    if (node->leftChild != NULL) {
        removeTreeRecursive(tree, node->leftChild);
    }
    if (node->rightChild != NULL) {
        removeTreeRecursive(tree, node->rightChild);
    }
    free(node);
    return true;
}

bool removeTree(AVLTree* tree)
{
    if (tree == NULL) {
        return false;
    }
    if (tree->root == NULL) {
        free(tree);
        return true;
    }
    removeTreeRecursive(tree, tree->root->leftChild);
    removeTreeRecursive(tree, tree->root->rightChild);
    free(tree->root);
    free(tree);
    return true;
}
