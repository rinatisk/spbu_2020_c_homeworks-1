#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cyclical_list.h"

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

void printList(List* list)
{
    int numberOfElements = 0;
    printf("START -> ");
    ListElement* temp = list->head;
    while (numberOfElements != sizeOfList(list)) {
        printf("%d -> ", temp->value);
        temp = temp->next;
        numberOfElements++;
    }
    printf("%d -> ", list->tail->value);
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
    list->tail->next = list->head;
}

bool removeByValue(List* list, int value)
{
    list->size--;
    ListElement* current = list->head;
    if (list->head != NULL && list->head->value == value) {
        list->head = list->head->next;
        free(current);
        return true;
    }
    ListElement* previous = NULL;
    while (current != NULL) {
        if (current->value == value) {
            previous->next = current->next;
            free(current);
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
    ListElement* temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

ListElement* retrieve(int position, List* list)
{
    ListElement* elem = list->head;
    for (int i = 1; i < position && elem != NULL; ++i) {
        elem = elem->next;
    }
    return elem;
}

bool insert(ListElement* value, int position, List* list)
{
    if (list->size < position) {
        return true;
    } else {
        ListElement* current = retrieve(position, list);
        ListElement* previous = retrieve(position - 1, list);
        previous->next = value;
        value->next = current;
        return false;
    }
}

int locate(ListElement* value, List* list)
{
    ListElement* elem = list->head;
    int position = 1;
    while (elem != value) {
        elem = elem->next;
        position++;
    }
    return position;
}

bool delete (int position, List* list)
{
    if (position <= list->size) {
        list->size--;
        ListElement* previous = retrieve(position - 1, list);
        ListElement* current = retrieve(position, list);
        previous->next = previous->next->next;
        free(current);
        return false;
    } else
        return true;
}

int sizeOfList(List* list){
    return list->size;
}

void deleteEveryMSoldier(List* list, int m){
    int numberOfRemoved = 0;
    for (int i = 1; i <= sizeOfList(list); ++i) {
        if ((i + numberOfRemoved) % m == 0) {
            delete (i, list);
            numberOfRemoved++;
        }
    }
}