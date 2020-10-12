#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include <stdbool.h>

typedef struct ListElement ListElement;

typedef struct List List;

List* createList();

ListElement* createListElement(int value);

void printList(List* list);

void addListElement(List* list, ListElement* elem);

void removeList(List* list);

ListElement* retrieve(int position, List* list);

bool removeByValue(List* list, int value);

bool insert(ListElement* value, int position, List* list);

int locate(ListElement* value, List* list);

bool deleteElement(int position, List* list);

ListElement* tail(List *list);

ListElement* head(List *list);

int getSizeList(List* list);

int getValue(ListElement* listElement);
#endif //UNTITLED_LIST_H
