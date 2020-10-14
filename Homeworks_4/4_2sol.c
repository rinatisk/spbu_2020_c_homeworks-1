#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int computeExponentSmallNumber(double* number, int exponent, int systemNumber)
{
    while (fabs(*number) < 1) {
        *number *= systemNumber;
        exponent--;
    }
    return exponent;
}

int computeExponentBigNumber(double* number, int exponent, int systemNumber)
{
    while (fabs(*number) > systemNumber) {
        *number /= systemNumber;
        exponent++;
    }
    return exponent;
}

bool isNumberBig(double number, int system)
{
    return fabs(number) > system;
}

void printExponentFormat(double number, int exponent, int systemNumber)
{
    if (number > 0) {
        printf("+%lg * %d ^ {%d}", number, systemNumber, exponent);
    } else
        printf("%lg * %d ^ {%d}", number, systemNumber, exponent);
}

int main()
{
    double number = 0;
    printf("Enter a number:\n");
    scanf("%lg", &number);

    int exponent = 0;
    int systemNumber = 0;
    printf("write number of numeral system:\n");
    scanf("%d", &systemNumber);

    if (isNumberBig(number, systemNumber)) {
        exponent = computeExponentBigNumber(&number, exponent, systemNumber);
    } else
        exponent = computeExponentSmallNumber(&number, exponent, systemNumber);

    printExponentFormat(number, exponent, systemNumber);

    return 0;
}