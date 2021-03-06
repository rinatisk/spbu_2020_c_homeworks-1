#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct ListElement {
    int value;
    struct ListElement* next;
};

struct List {
    struct ListElement* head;
    struct ListElement* tail;
    int size;
};

List* createList()
{
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ListElement* createListElement(int value)
{
    ListElement* elem = malloc(sizeof(ListElement));
    elem->value = value;
    elem->next = NULL;
    return elem;
}

void freeListElement(ListElement* listElement)
{
    free(listElement);
}

void printList(List* list)
{
    printf("START -> ");
    ListElement* toPrint = head(list);
    while (toPrint != NULL) {
        printf("%d -> ", toPrint->value);
        toPrint = toPrint->next;
    }
    printf("END\n");
}

void addListElement(List* list, ListElement* elem)
{
    list->size++;
    if (list->head == NULL) {
        list->head = elem;
        list->tail = elem;
        return;
    }
    ListElement* currentTail = list->tail;
    currentTail->next = elem;
    list->tail = elem;
    list->tail->next = NULL;
}

bool removeByValue(List* list, int value)
{
    list->size--;
    ListElement* current = list->head;
    if (list->head != NULL && list->head->value == value) {
        list->head = list->head->next;
        freeListElement(current);
        return true;
    }
    ListElement* previous = NULL;
    while (current != NULL) {
        if (current->value == value) {
            previous->next = current->next;
            freeListElement(current);
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

void removeList(List* list)
{
    ListElement* current = list->head;
    ListElement* toDelete = NULL;
    while (current != NULL) {
        toDelete = current;
        current = current->next;
        freeListElement(toDelete);
    }
    free(list);
}

ListElement* retrieve(int position, List* list)
{
    if (position > list->size - 1 || position < 0) {
        return NULL;
    }
    ListElement* elem = list->head;
    for (int i = 0; i < position && elem != NULL; ++i) {
        elem = elem->next;
    }
    return elem;
}

bool insert(ListElement* value, int position, List* list)
{
    if (position > list->size || position < 0) {
        return false;
    }
    if (position == list->size) {
        ListElement* current = list->tail;
        current->next = value;
        list->tail = value;
        list->tail->next = NULL;
        return true;
    }
    if (position == 0) {
        ListElement* current = list->head;
        list->head = value;
        list->head->next = current;
        return true;
    }
    ListElement* current = retrieve(position, list);
    ListElement* previous = retrieve(position - 1, list);
    previous->next = value;
    value->next = current;
    return true;
}

int locate(ListElement* value, List* list)
{
    ListElement* elem = list->head;
    int position = 0;
    while (elem != value && position != list->size) {
        elem = elem->next;
        position++;
    }
    if (position == list->size) {
        return -1;
    }
    return position;
}

bool deleteElement(int position, List* list)
{
    if (position > list->size - 1 || position < 0) {
        return false;
    }
    if (position == 0) {
        list->size--;
        ListElement* current = list->head;
        list->head = current->next;
        free(current);
        return true;
    }
    list->size--;
    ListElement* previous = retrieve(position - 1, list);
    ListElement* toDelete = previous->next;
    previous->next = toDelete->next;
    free(toDelete);
    return true;
}

ListElement* tail(List* list)
{
    return list->tail;
}

ListElement* head(List* list)
{
    return list->head;
}

int getSizeList(List* list)
{
    return list->size;
}

int getValue(ListElement* listElement)
{
    return listElement->value;
}
