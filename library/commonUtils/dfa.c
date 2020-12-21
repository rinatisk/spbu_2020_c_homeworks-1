#include "dfa.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Transition {
    char symbol;
    DFAState* transitionState;
} Transition;

struct DFAState {
    bool isFinal;
    int transitionsSize;
    int transitionAllocationSize;
    Transition** transitions;
};

struct DFA {
    DFAState* initialState;
    DFAState* failState;
};

Transition* createTransition(char symbol, DFAState* transitionState)
{
    Transition* transition = (Transition*)malloc(sizeof(Transition));
    transition->symbol = symbol;
    transition->transitionState = transitionState;

    return transition;
}

DFA* createDFA(DFAState* initialState)
{
    DFA* dfa = (DFA*)malloc(sizeof(DFA));
    dfa->initialState = initialState;
    dfa->failState = createDFAState(false);

    return dfa;
}

bool removeDFA(DFA* dfa)
{
    if (dfa == NULL) {
        return false;
    }
    removeDFAState(dfa->failState);
    free(dfa);
    return true;
}

DFAState* createDFAState(bool isFinal)
{
    DFAState* dfaState = (DFAState*)malloc(sizeof(DFAState));
    dfaState->isFinal = isFinal;
    dfaState->transitionsSize = 0;
    dfaState->transitionAllocationSize = 1;
    dfaState->transitions = (Transition**)calloc(1, sizeof(Transition*));
    return dfaState;
}

bool removeDFAState(DFAState* dfaState)
{
    if (dfaState == NULL) {
        return false;
    }
    for (int i = 0; i < dfaState->transitionsSize; ++i) {
        free(dfaState->transitions[i]);
    }
    free(dfaState->transitions);
    free(dfaState);
    return true;
}

void reallocTransition(DFAState* dfaState)
{
    dfaState->transitions = realloc(dfaState->transitions, dfaState->transitionAllocationSize * 2 * sizeof(Transition*));
    memset(dfaState->transitions + dfaState->transitionAllocationSize, 0, dfaState->transitionAllocationSize * sizeof(Transition*));
    dfaState->transitionAllocationSize *= 2;
}

void addTransition(DFAState* firstState, char value, DFAState* secondState)
{
    Transition* newTransition = createTransition(value, secondState);
    if (firstState->transitionAllocationSize == firstState->transitionsSize) {
        reallocTransition(firstState);
    }
    firstState->transitions[firstState->transitionsSize] = newTransition;
    firstState->transitionsSize++;
}

bool isExpressionValid(DFA* DFA, char* expression, int lengthOfExpression)
{
    bool isFind = false;
    DFAState* currentDfaState = DFA->initialState;
    char toCheckSymbol = expression[0];
    for (int i = 0; i < lengthOfExpression; ++i) {
        toCheckSymbol = expression[i];
        isFind = false;
        for (int j = 0; j < currentDfaState->transitionsSize; ++j) {
            if (toCheckSymbol == currentDfaState->transitions[j]->symbol) {
                isFind = true;
                currentDfaState = currentDfaState->transitions[j]->transitionState;
                break;
            }
        }
        if (!isFind)
            currentDfaState = DFA->failState;
    }

    return currentDfaState->isFinal;
}
