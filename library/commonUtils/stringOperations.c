#include <stdio.h>
#include <stdlib.h>

#include "stringOperations.h"

char* getString(int* lengthOfExpression)
{
    int currentLengthOfExpression = 1;
    char* expression = calloc(currentLengthOfExpression, sizeof(char));
    char newSymbol = ' ';
    int toAddIndex = -1;
    scanf("%c", &newSymbol);
    while (newSymbol != '\n') {
        ++toAddIndex;
        if (toAddIndex + 1 == currentLengthOfExpression) {
            expression = realloc(expression, currentLengthOfExpression * 2 * sizeof(char));
            currentLengthOfExpression *= 2;
        }
        expression[toAddIndex] = newSymbol;
        scanf("%c", &newSymbol);
    }
    *lengthOfExpression = toAddIndex;
    return expression;
}
