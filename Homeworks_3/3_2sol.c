#include <stdio.h>

#include "../library/commonUtils/cyclical_list.h"

int main()
{
    List* soldiers = createList();
    int numberOfSoldiers = 0;
    int m = 0;
    ListElement* listElement = NULL;
    printf("Write number of all soldiers and number m:\n");
    scanf("%d%d", &numberOfSoldiers, &m);
    for (int i = 0; i < numberOfSoldiers; ++i) {
        listElement = createListElement(i);
        addListElement(soldiers, listElement);
    }
    int position = m - 1;
    while (getSizeList(soldiers) > m - 1) {
        deleteElement(position, soldiers);
        position = getNextPosition(soldiers, position, m);
    }
    int lastSoldier = getLastSoldier(soldiers);
    printf("Last soldier is:\n%d", lastSoldier);
    return 0;
}
