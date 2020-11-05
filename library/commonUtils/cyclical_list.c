#include <stdlib.h>

#include "cyclical_list.h"
#include "list.h"

int getNextPosition(List* list, int position, int m)
{
    if (position + m == getSizeList(list)) {
        return 0;
    }
    if (position + m < getSizeList(list)) {
        return position + m;
    }
    if (position + m > getSizeList(list)) {
        return (position + m) % getSizeList(list);
    }
}

int getLastSoldier(List* list)
{
    ListElement* listElement = head(list);
    return getValue(listElement);
}
