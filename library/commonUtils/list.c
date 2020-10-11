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
    ListElement* toPrint = list->head;
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
    ListElement* temp = list->tail;
    temp->next = elem;
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
    if (position > list->size || position < 0) {
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

bool delete (int position, List* list)
{
    if (position > list->size || position < 0) {
        return false;
    }
    list->size--;
    ListElement* previous = retrieve(position - 1, list);
    ListElement* current = retrieve(position, list);
    previous->next = current->next;
    freeListElement(current);
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
