#ifndef INC_2909PRACT__LIST_H_
#define INC_2909PRACT__LIST_H_
#include <stdbool.h>

typedef struct StackElement StackElement;

typedef struct Stack Stack;

Stack* createStack();

StackElement* createStackElement(int store);

void push(Stack* stack, StackElement* newElement);

int getSize(Stack* stack);

StackElement* pop(Stack* stack);

bool isEmpty(Stack* stack);

void deleteStackElement(StackElement* stackElement);

void deleteStack(Stack* stack);

int getValue(StackElement* stackElement);

#endif//INC_2909PRACT__LIST_H_
