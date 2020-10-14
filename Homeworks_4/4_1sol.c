#include <ctype.h>
#include <stdio.h>

#include "../library/commonUtils/stack.h"

const int MAX_SIZE = 100;

int getNewPositiveNumber(char* string, int* position)
{
    int value = 0;
    while (isdigit(string[(*position)])) {
        value *= 10;
        value += (string[*position] - 48);
        (*position) += 1;
    }
    return value;
}

int getNewNegativeNumber(char* string, int* position)
{
    int value = getNewPositiveNumber(string, position);
    return (-value);
}

int getNewNumber(char* string, int* position)
{
    if (*position == 0 || string[*position - 1] == ' ') {
        return getNewPositiveNumber(string, position);
    }
    return getNewNegativeNumber(string, position);
}

int calculateNumbersBeforeOperation(Stack* numbers, char operation, int* error)
{
    int secondOperand = getValue(pop(numbers));
    int firstOperand = getValue(pop(numbers));
    switch (operation) {
    case '+':
        return firstOperand + secondOperand;
    case '-':
        return firstOperand - secondOperand;
    case '*':
        return firstOperand * secondOperand;
    case '/':
        if (secondOperand == 0) {
            *error = -1;
        } else
        return firstOperand / secondOperand;
    }
};

bool isOperator (char* string, int position)
{
    return (string[position] >= '*' && string[position] <= '/' && !isdigit(string[position + 1]));
}

int calculateFullExpression(char string[], int* error)
{
    Stack* computation = createStack();
    StackElement* newNumber = createStackElement(0);
    int position = 0;
    while (string[position] != '\n') {
        if (isdigit(string[position])) {
            newNumber = createStackElement(getNewNumber(string, &position));
            push(computation, newNumber);
        }
        if (isOperator(string, position)) {
            newNumber = createStackElement(calculateNumbersBeforeOperation(computation, string[position], error));
            push(computation, newNumber);
        }
        position++;
    }
    int totalResult = getValue(pop(computation));
    return totalResult;
}

int main()
{
    int error = 0;
    char string[MAX_SIZE];
    printf("write expression:\n");
    fgets(string, MAX_SIZE, stdin);
    int totalResult = calculateFullExpression(string, &error);
    if (error == 0) {
        printf("%d", totalResult);
    } else printf("error code is %d", error);
    return 0;
}
