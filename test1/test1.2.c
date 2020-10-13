#include <stdio.h>

#include "../library/commonUtils/complex.h"

int main()
{
    ComplexNumber* complexNumber1 = createComplexNumber(2.24, 5.6);
    ComplexNumber* complexNumber2 = createComplexNumber(2.24, 5.6);
    removeComplexNumber(complexNumber2);
    removeComplexNumber(complexNumber1);
}
