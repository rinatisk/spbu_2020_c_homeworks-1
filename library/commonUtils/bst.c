#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

typedef struct BinaryTreeNode {
    int value;
    struct BinaryTreeNode* leftChild;
    struct BinaryTreeNode* rightChild;
} BinaryTreeNode;

struct BinarySearchTree {
    struct BinaryTreeNode* root;
};

enum Direction { left,
    right,
    none };

BinarySearchTree* createTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    return newTree;
}

bool existsRecursive(BinaryTreeNode* node, int value)
{
    if (node->value == value) {
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

bool isEmpty(BinarySearchTree* tree)
{
    return (tree->root == NULL);
}

bool exists(BinarySearchTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return existsRecursive(tree->root, value);
}

BinaryTreeNode* createNode(int value)
{
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->rightChild = NULL;
    node->leftChild = NULL;
    node->value = value;
    return node;
}

bool addValueRecursive(BinaryTreeNode* node, int value)
{
    if (node->value == value) {
        return false;
    }
    if (value < node->value) {
        if (node->leftChild == NULL) {
            node->leftChild = createNode(value);
            return true;
        } else
            return addValueRecursive(node->leftChild, value);
    }
    if (value > node->value) {
        if (node->rightChild == NULL) {
            node->rightChild = createNode(value);
            return true;
        } else
            return addValueRecursive(node->rightChild, value);
    }
    return true;
}

bool addValue(BinarySearchTree* tree, int value)
{
    if (isEmpty(tree)) {
        tree->root = createNode(value);
    }
    return addValueRecursive(tree->root, value);
}

bool isLeaf(BinaryTreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

bool changeParent(BinarySearchTree* tree, BinaryTreeNode* parent, BinaryTreeNode* newNode, enum Direction parentDirection)
{
    if (parentDirection == left) {
        parent->leftChild = newNode;
    }
    if (parentDirection == right) {
        parent->rightChild = newNode;
    }
    if (parentDirection == none) {
        tree->root = newNode;
    }
    return true;
}

bool removeRecursive(BinarySearchTree* tree, BinaryTreeNode* node, int value, BinaryTreeNode* parent, enum Direction parentDirection)
{
    if (node->value == value) {
        if (isLeaf(node)) {
            free(node);
            changeParent(tree, parent, NULL, parentDirection);
            return true;
        }
        if (node->leftChild == NULL && node->rightChild != NULL) {
            changeParent(tree, parent, node->rightChild, parentDirection);
            free(node);
            return true;
        }
        if (node->rightChild == NULL && node->leftChild != NULL) {
            changeParent(tree, parent, node->leftChild, parentDirection);
            free(node);
            return true;
        }
        if (node->leftChild != NULL && node->rightChild != NULL) {
            BinaryTreeNode* maxLeftNode = node->leftChild;
            BinaryTreeNode* parentMaxLeftNode = node;
            enum Direction currentDirection = left; // if we left child of node is maximum
            while (maxLeftNode->rightChild != NULL) {
                parentMaxLeftNode = maxLeftNode;
                maxLeftNode = maxLeftNode->rightChild;
                currentDirection = right; // if left child if node have right child
            }
            node->value = maxLeftNode->value;
            removeRecursive(tree, maxLeftNode, maxLeftNode->value, parentMaxLeftNode, currentDirection);
            return true;
        }
    }
    if (node->value > value && node->leftChild != NULL) {
        return removeRecursive(tree, node->leftChild, value, node, left);
    }
    if (node->value < value && node->rightChild != NULL) {
        return removeRecursive(tree, node->rightChild, value, node, right);
    }
    return false;
}

bool removeValue(BinarySearchTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return removeRecursive(tree, tree->root, value, NULL, none);
}

void printAscendingRecursive(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    if (node->leftChild != NULL) {
        printAscendingRecursive(node->leftChild);
    }
    printf("%d ", node->value);
    if (node->leftChild != NULL) {
        printAscendingRecursive(node->rightChild);
    }
}

void printAscending(BinarySearchTree* tree)
{
    printf("Here's your tree: ( ");
    if (tree != NULL)
        printAscendingRecursive(tree->root);
    printf(")\n");
}

void printDescendingRecursive(BinaryTreeNode* node)
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

void printDescending(BinarySearchTree* tree)
{
    printf("Here's your tree: ( ");
    if (tree != NULL)
        printDescendingRecursive(tree->root);
    printf(")\n");
}

void printNodeAndChildRecursive(BinarySearchTree* tree, BinaryTreeNode* node)
{
    if (node != NULL) {
        printf("(");
        if (isLeaf(node)) {
            printf(" %d null null ", node->value);
        } else if (node->leftChild == NULL) {
            printf(" %d null ", node->value);
            printNodeAndChildRecursive(tree, node->rightChild);
        } else if (node->rightChild == NULL) {
            printf(" %d null", node->value);
            printNodeAndChildRecursive(tree, node->leftChild);
        } else {
            printf(" %d ", node->value);
            printNodeAndChildRecursive(tree, node->leftChild);
            printNodeAndChildRecursive(tree, node->rightChild);
        }
        printf(")");
    }
}

void printNodeAndChildForm(BinarySearchTree* tree)
{
    printf("Here's your tree: ");
    printNodeAndChildRecursive(tree, tree->root);
    printf("\n");
}

bool removeTreeRecursive(BinarySearchTree* tree, BinaryTreeNode* node, BinaryTreeNode* parent, enum Direction parentDirection)
{
    if (node == NULL) {
        return false;
    }
    if (isLeaf(node)) {
        changeParent(tree, parent, NULL, parentDirection);
        free(node);
        return true;
    }
    if (node->leftChild != NULL) {
        removeTreeRecursive(tree, node->leftChild, node, left);
    }
    if (node->rightChild != NULL) {
        removeTreeRecursive(tree, node->rightChild, node, right);
    }
    changeParent(tree, parent, NULL, parentDirection);
    free(node);
    return true;
}

bool removeTree(BinarySearchTree* tree)
{
    if (tree == NULL) {
        return false;
    }
    if (tree->root == NULL) {
        free(tree);
        return true;
    }
    removeTreeRecursive(tree, tree->root->leftChild, tree->root, left);
    removeTreeRecursive(tree, tree->root->rightChild, tree->root, right);
    free(tree->root);
    free(tree);
    return true;
}
