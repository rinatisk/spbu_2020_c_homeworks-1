#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../library/commonUtils/dfa.h"

const int NUMBER_OF_DFA_STATES = 8;
const char IS_DIGIT = '0';

bool createTransitions(DFAState** states)
{
    if (states == NULL) {
        return false;
    }

    addTransition(states[0], '+', states[1]);
    addTransition(states[0], '-', states[1]);
    addTransition(states[2], '.', states[3]);
    addTransition(states[2], 'E', states[5]);
    addTransition(states[4], 'E', states[5]);
    addTransition(states[5], '+', states[6]);
    addTransition(states[5], '-', states[6]);

    addTransition(states[0], IS_DIGIT, states[2]);
    addTransition(states[1], IS_DIGIT, states[2]);
    addTransition(states[2], IS_DIGIT, states[2]);
    addTransition(states[3], IS_DIGIT, states[4]);
    addTransition(states[4], IS_DIGIT, states[4]);
    addTransition(states[5], IS_DIGIT, states[7]);
    addTransition(states[6], IS_DIGIT, states[7]);
    addTransition(states[7], IS_DIGIT, states[7]);
}

DFAState** createDFAStates()
{
    DFAState** states = (DFAState**)malloc(NUMBER_OF_DFA_STATES * sizeof(DFAState*));

    DFAState* startState = createDFAState(false);
    states[0] = startState;

    DFAState* dot = createDFAState(false);
    states[3] = dot;

    DFAState* signOfNumber = createDFAState(false);
    states[1] = signOfNumber;

    DFAState* signOfExponent = createDFAState(false);
    states[6] = signOfExponent;

    DFAState* exponentSymbol = createDFAState(false);
    states[5] = exponentSymbol;

    DFAState* digitOfNumber = createDFAState(true);
    states[2] = digitOfNumber;

    DFAState* digitOfFractionalPart = createDFAState(true);
    states[4] = digitOfFractionalPart;

    DFAState* digitOfExponent = createDFAState(true);
    states[7] = digitOfExponent;

    createTransitions(states);

    return states;
}

bool removeDFAStates(DFAState** states, int statesNumber)
{
    if (states == NULL || statesNumber == 0) {
        return false;
    }
    for (int i = 0; i < statesNumber; ++i) {
        removeDFAState(states[i]);
    }
    free(states);
    return true;
}

void printInfoAboutExpression(bool isValid)
{
    isValid ? printf("expression is valid") : printf("expression is invalid");
}

char* getExpression(int* lengthOfExpression)
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

int main()
{
    int lengthOfExpression = 0;
    printf("Write your expression:\n");
    char* expression = getExpression(&lengthOfExpression);

    DFAState** states = createDFAStates();
    DFA* DFA = createDFA(states[0]);

    printInfoAboutExpression(isExpressionValid(DFA, expression, lengthOfExpression));

    removeDFAStates(states, NUMBER_OF_DFA_STATES);
    removeDFA(DFA);
    free(expression);
    return 0;
}
