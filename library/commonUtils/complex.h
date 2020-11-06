
#ifndef SPBU_2020_C_HOMEWORKS_1_COMPLEX_H
#define SPBU_2020_C_HOMEWORKS_1_COMPLEX_H

#include <stdbool.h>

typedef struct ComplexNumber ComplexNumber;

ComplexNumber* createComplexNumber(double first, double second);

ComplexNumber* sum(ComplexNumber* firstNumber, ComplexNumber* secondNumber);

ComplexNumber* difference(ComplexNumber* firstNumber, ComplexNumber* secondNumber);

ComplexNumber* composition(ComplexNumber* firstNumber, ComplexNumber* secondNumber);

ComplexNumber* division(ComplexNumber* firstNumber, ComplexNumber* secondNumber);

void removeComplexNumber(ComplexNumber* complexNumber);

#endif //SPBU_2020_C_HOMEWORKS_1_COMPLEX_H
