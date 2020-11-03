#include <stdio.h>

#include "../library/commonUtils/bst.h"

void getHelp()
{
    printf("1 is add value\n");
    printf("2 is delete value\n");
    printf("3 is exist\n");
    printf("4 is print ascending\n");
    printf("5 is print descending\n");
    printf("6 is print nodeAndChildren\n");
    printf("7 is help\n");
    printf("8 is exit\n");
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
        printf("write value\n");
        scanf("%d", &value);
        if (exists(tree, value)) {
            printf("%d exist\n", value);
        } else {
            printf("%d not exist\n", value);
        }
        break;
    }
    case 4: {
        printAscending(tree);
        break;
    }
    case 5: {
        printDescending(tree);
        break;
    }
    case 6: {
        printNodeAndChildrenForm(tree);
        break;
    }
    case 7: {
        getHelp();
        break;
    }
    case 8: {
        *exit = true;
        break;
    }
    default: {
        printf("unknown command\n");
        break;
    }
    }
}

int main()
{
    BinarySearchTree* tree = createTree();
    getHelp();
    bool exit = false;
    while (!exit) {
        menu(tree, &exit);
    }
    removeTree(tree);
    printf("All done!\n");

    return 0;
}
