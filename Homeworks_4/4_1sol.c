#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../library/commonUtils/stack.h"

const int MAX_SIZE = 100;


int getNewNumber (char* string, int position)
{
    int value = 0;
    while (isdigit(string[position])) {
        value *= 10;
        value += (string[position] - 48);
        position++;
    }
    return value;
}

int calculateNumbersBeforeOperation(Stack* numbers, char operation)
{
    int firstOperand = getValue(pop(numbers));
    int secondOperand = getValue(pop(numbers));
    switch (operation) {
    case '+':
        return firstOperand + secondOperand;
    case '-':
        return firstOperand - secondOperand;
    case '*':
        return firstOperand * secondOperand;
    case '/':
        return firstOperand / secondOperand;
    }
};


int calculateFullExpression (char string[])
{
    Stack* computation = createStack();
    StackElement* newNumber = createStackElement(0);
    int position = 0;
    while (string[position] != '\n') {
        if (isdigit(string[position])) {
            newNumber = createStackElement(getNewNumber(string, position));
            push(computation, newNumber);
        }
        if (string[position] >= '*' && string[position] <= '/') {
            newNumber = createStackElement(calculateNumbersBeforeOperation(computation, string[position]));
            push(computation, newNumber);
        }
        position++;
    }
    int totalResult = getValue(pop(computation));
    return totalResult;
}

int main()
{
    char string[MAX_SIZE];
    printf("write expression:\n");
    fgets(string, MAX_SIZE, stdin);
    int totalResult = calculateFullExpression(string);
    printf("%d", totalResult);
    return 0;
}
