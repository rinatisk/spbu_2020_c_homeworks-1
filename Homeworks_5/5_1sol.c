#include <stdio.h>

#include "../library/commonUtils/bst.h"

int main()
{
    BinarySearchTree* tree = createTree();
    addValue(tree, 8);
    addValue(tree, 3);
    addValue(tree, 1);
    addValue(tree, 9);
    addValue(tree, 12);
    printf("%d", exists(tree, 5));
    addValue(tree, 11);
    addValue(tree, 5);
    addValue(tree, 4);
    printf("%d\n", exists(tree, 5));

    printAscending(tree);

    removeValue(tree, 8);

    printDescending(tree);
    printNodeAndChildForm(tree);

    removeTree(tree);
    printf("All done!\n");

    return 0;
}
