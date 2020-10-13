#include "complex.h"
#include <stdlib.h>

struct ComplexNumber {
    double first;
    double second;
};


ComplexNumber* createComplexNumber(double first, double second)
{
    ComplexNumber* complexNumber = malloc(sizeof(ComplexNumber));
    complexNumber->first = first;
    complexNumber->second = second;
    return complexNumber;
}

ComplexNumber* sum(ComplexNumber* firstNumber, ComplexNumber* secondNumber)
{
    double first = firstNumber->first + secondNumber->first;
    double second = firstNumber->second + secondNumber->second;
    ComplexNumber* sumNumber = createComplexNumber(first, second);
    return sumNumber;
}

ComplexNumber* difference(ComplexNumber* firstNumber, ComplexNumber* secondNumber)
{
    double first = firstNumber->first - secondNumber->first;
    double second = firstNumber->second - secondNumber->second;
    ComplexNumber* sumNumber = createComplexNumber(first, second);
    return sumNumber;
}

ComplexNumber* composition(ComplexNumber* firstNumber, ComplexNumber* secondNumber)
{
    double first = (firstNumber->first) * (secondNumber->first) - (secondNumber->second) * (firstNumber->second);
    double second = (firstNumber->first) * (secondNumber->second) + (secondNumber->first) * (firstNumber->second);
    ComplexNumber* sumNumber = createComplexNumber(first, second);
    return sumNumber;
}

ComplexNumber* division(ComplexNumber* firstNumber, ComplexNumber* secondNumber)
{
    double numerator = ((secondNumber->first) * (secondNumber->first) +
                        (secondNumber->second) * (secondNumber->second));
    double first =
            ((firstNumber->first) * (secondNumber->first) + (secondNumber->second) * (firstNumber->second)) / numerator;
    double second =
            (firstNumber->first) * (secondNumber->first) - (secondNumber->second) * (firstNumber->second) / numerator;
    ComplexNumber* sumNumber = createComplexNumber(first, second);
    return sumNumber;
}

void removeComplexNumber(ComplexNumber* complexNumber)
{
    free(complexNumber);
}