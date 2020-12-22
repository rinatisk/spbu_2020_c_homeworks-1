#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../library/commonUtils/dfa.h"
#include "../library/commonUtils/stringOperations.h"

const int NUMBER_OF_DFA_STATES = 6;

// const to create a transition for all digits
const char DIGIT = 'D';

// const to create a transition for all letters
const char LETTER = 'L';

bool isLetter(char toCheckSymbol)
{
    return (toCheckSymbol >= 'A' && toCheckSymbol <= 'Z');
}

DFAState** createDFAStates()
{
    DFAState** states = (DFAState**)malloc(NUMBER_OF_DFA_STATES * sizeof(DFAState*));

    DFAState* initial = createDFAState(false);
    states[0] = initial;

    DFAState* firstPart = createDFAState(false);
    states[1] = firstPart;

    DFAState* atSymbol = createDFAState(false);
    states[2] = atSymbol;

    DFAState* secondPart = createDFAState(false);
    states[3] = secondPart;

    DFAState* dot = createDFAState(false);
    states[4] = dot;

    DFAState* thirdPart = createDFAState(true);
    states[5] = thirdPart;

    addTransition(initial, LETTER, firstPart);
    addTransition(initial, DIGIT, firstPart);
    addTransition(initial, '.', firstPart);
    addTransition(initial, '_', firstPart);
    addTransition(initial, '%', firstPart);
    addTransition(initial, '+', firstPart);
    addTransition(initial, '-', firstPart);

    addTransition(firstPart, '@', atSymbol);
    addTransition(firstPart, LETTER, firstPart);
    addTransition(firstPart, DIGIT, firstPart);
    addTransition(firstPart, '.', firstPart);
    addTransition(firstPart, '_', firstPart);
    addTransition(firstPart, '%', firstPart);
    addTransition(firstPart, '+', firstPart);
    addTransition(firstPart, '-', firstPart);

    addTransition(atSymbol, DIGIT, secondPart);
    addTransition(atSymbol, LETTER, secondPart);
    addTransition(atSymbol, '-', secondPart);

    addTransition(secondPart, '.', dot);
    addTransition(secondPart, DIGIT, secondPart);
    addTransition(secondPart, LETTER, secondPart);
    addTransition(secondPart, '-', secondPart);

    addTransition(dot, LETTER, thirdPart);
    addTransition(dot, DIGIT, secondPart);
    addTransition(dot, LETTER, secondPart);
    addTransition(dot, '-', secondPart);

    addTransition(thirdPart, DIGIT, secondPart);
    addTransition(thirdPart, LETTER, secondPart);
    addTransition(thirdPart, '-', secondPart);

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
    char* expression = getString(lengthOfExpression);
    for (int i = 0; i < *lengthOfExpression; ++i) {
        if (isLetter(expression[i]))
            expression[i] = LETTER;
        if (isdigit(expression[i]) != 0)
            expression[i] = DIGIT;
    }
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
