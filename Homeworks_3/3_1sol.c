#include <stdio.h>

#include "../library/commonUtils/list.h"

int main()
{
    List* numbers = createList();
    ListElement* number1 = createListElement(1);
    ListElement* number2 = createListElement(2);
    ListElement* number3 = createListElement(3);
    ListElement* number4 = createListElement(4);
    addListElement(numbers, number1);
    addListElement(numbers, number2);
    addListElement(numbers, number3);
    printList(numbers);
    insert(number4, 2, numbers);
    printList(numbers);
    int position = locate(number4, numbers);
    printf("%d\n", position);
    delete(2, numbers);
    printList(numbers);
    removeList(numbers);
    return 0;
}
