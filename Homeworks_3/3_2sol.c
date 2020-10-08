#include <stdio.h>

#include "../library/commonUtils/cyclical_list.h"

int main()
{
    List* soldiers = createList();
    int n = 0;
    int m = 0;
    printf("Write number of all soldiers and number m:\n");
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        ListElement* newSoldier = createListElement(i);
        addListElement(soldiers, newSoldier);
    }
    while (sizeOfList(soldiers) > m - 1) {
        deleteEveryMSoldier(soldiers, m);
    }
    delete (sizeOfList(soldiers), soldiers);
    printf("The soldiers who stay alive:\n");
    printList(soldiers);
    removeList(soldiers);
    return 0;
}
