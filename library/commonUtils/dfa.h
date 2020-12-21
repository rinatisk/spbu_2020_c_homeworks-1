#ifndef SPBU_2020_C_HOMEWORKS_1_DFA_H
#define SPBU_2020_C_HOMEWORKS_1_DFA_H

#include <stdbool.h>

typedef struct DFAState DFAState;

typedef struct DFA DFA;

DFA* createDFA(DFAState* initialState);

bool removeDFA(DFA* dfa);

DFAState* createDFAState(bool isFinal);

bool removeDFAState(DFAState* dfaState);

void addTransition(DFAState* firstState, char value, DFAState* secondState);

bool isExpressionValid(DFA* DFA, char* expression, int lengthOfExpression);

#endif //SPBU_2020_C_HOMEWORKS_1_DFA_H
