#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../library/commonUtils/dfa.h"
#include "../library/commonUtils/stringOperations.h"

const int NUMBER_OF_DFA_STATES = 8;

// const to create a transition for all digits
const char DIGIT = 'D';

DFAState** createDFAStates()
{
    DFAState** states = (DFAState**)malloc(NUMBER_OF_DFA_STATES * sizeof(DFAState*));

    DFAState* initial = createDFAState(false);
    states[0] = initial;

    DFAState* signOfNumber = createDFAState(false);
    states[1] = signOfNumber;

    DFAState* digitOfNumber = createDFAState(true);
    states[2] = digitOfNumber;

    DFAState* dot = createDFAState(false);
    states[3] = dot;

    DFAState* digitOfFractionalPart = createDFAState(true);
    states[4] = digitOfFractionalPart;

    DFAState* exponentSymbol = createDFAState(false);
    states[5] = exponentSymbol;

    DFAState* signOfExponent = createDFAState(false);
    states[6] = signOfExponent;

    DFAState* digitOfExponent = createDFAState(true);
    states[7] = digitOfExponent;

    //from initial to sign and digit of number
    addTransition(initial, '+', signOfNumber);
    addTransition(initial, '-', signOfNumber);
    addTransition(initial, DIGIT, digitOfNumber);

    //from sign to digit of number
    addTransition(signOfNumber, DIGIT, digitOfNumber);

    //from digit of number to fractional part or exponent part or to next digit
    addTransition(digitOfNumber, DIGIT, digitOfNumber);
    addTransition(digitOfNumber, 'E', exponentSymbol);
    addTransition(digitOfNumber, '.', dot);

    //from dot to digit of fractional part
    addTransition(dot, DIGIT, digitOfFractionalPart);

    //from digit of fractional part to exponent part or to next digit
    addTransition(digitOfFractionalPart, 'E', exponentSymbol);
    addTransition(digitOfFractionalPart, DIGIT, digitOfFractionalPart);

    //from exponent to digits of exponent part or exponent sign
    addTransition(exponentSymbol, DIGIT, digitOfExponent);
    addTransition(exponentSymbol, '+', signOfExponent);
    addTransition(exponentSymbol, '-', signOfExponent);

    //from sign of exponent part to digit of exponent part
    addTransition(signOfExponent, DIGIT, digitOfExponent);

    //from digit of exponent part to next digit
    addTransition(digitOfExponent, DIGIT, digitOfExponent);

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
