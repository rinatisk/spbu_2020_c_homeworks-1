#include <stdio.h>

#include "../library/commonUtils/bst.h"

void getHelp()
{
    printf("0 is exit\n");
    printf("1 is add value\n");
    printf("2 is delete value\n");
    printf("3 is print ascending\n");
    printf("4 is print descending\n");
    printf("5 is print nodeAndChild\n");
    printf("6 is exist\n");
    printf("7 is help\n");
}

void menu(BinarySearchTree* tree, bool* exit)
{
    int value = 0;
    int command = 0;
    printf("write command: \n");
    scanf("%d", &command);
    switch (command) {
    case 1: {
        printf("write value\n");
        scanf("%d", &value);
        addValue(tree, value);
        break;
    }
    case 2: {
        printf("write value\n");
        scanf("%d", &value);
        removeValue(tree, value);
        break;
    }
    case 3: {
        printAscending(tree);
        break;
    }
    case 4: {
        printDescending(tree);
        break;
    }
    case 5: {
        printNodeAndChildForm(tree);
        break;
    }
    case 6: {
        printf("write value\n");
        scanf("%d", &value);
        if (exists(tree, value)) {
            printf("%d exist\n", value);
        } else {
            printf("%d not exist\n", value);
        }
        break;
    }
    case 7: {
        getHelp();
        break;
    }
    case 0: {
        *exit = true;
        break;
    }
    default: printf("unknown command");
        break;
    }

}

int main()
{
    BinarySearchTree* tree = createTree();
    /*
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
*/
    getHelp();
    bool exit = false;
    while(!exit) {
        menu(tree, &exit);
    }
    removeTree(tree);
    printf("All done!\n");

    return 0;
}
