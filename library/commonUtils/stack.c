#include "stack.h"
#include <stdlib.h>

struct StackElement {
    int storeElement;
    StackElement* next;
};

struct Stack {
    StackElement* top;
    int size;
};

Stack* createStack()
{
    Stack* stack = malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

StackElement* createStackElement(int storeElement)
{
    StackElement* url = malloc(sizeof(StackElement));
    url->storeElement = storeElement;
    url->next = NULL;
    return url;
}

void push(Stack* stack, StackElement* storeElement)
{
    storeElement->next = stack->top;
    stack->top = storeElement;
    stack->size++;
}

bool isEmpty(Stack* stack)
{
    return stack->size == 0;
}

StackElement* pop(Stack* stack)
{
    if (isEmpty(stack)) {
        return NULL;
    }
    StackElement* element = stack->top;
    stack->top = element->next;
    element->next = NULL;
    stack->size--;
    return element;
}

void deleteStackElement(StackElement* stackElement)
{
    free(stackElement);
}

void deleteStack(Stack* stack)
{
    while (!isEmpty(stack)) {
        StackElement* element = pop(stack);
        deleteStackElement(element);
    }
    free(stack);
}

int getSize(Stack* stack)
{
    return stack->size;
}

int getValue(StackElement* stackElement)
{
    return stackElement->storeElement;
}
