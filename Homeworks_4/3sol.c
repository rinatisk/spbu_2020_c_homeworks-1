#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const int SIZE_OF_BINARY_NUMBER = sizeof(int) * 8;

void getBinaryNumber(int number, bool* binaryNumber)
{
    for (int i = 0; i < SIZE_OF_BINARY_NUMBER; ++i) {
        binaryNumber[i] = (number & 1);
        number >>= 1;
    }
}

void getBinarySum(bool* binaryFirstNumber, bool* binarySecondNumber, bool* binarySum)
{
    bool transferValue = 0;
    for (int i = 0; i < SIZE_OF_BINARY_NUMBER; ++i) {
        int currentRankValue = 0;
        currentRankValue = binaryFirstNumber[i] + binarySecondNumber[i] + transferValue;
        binarySum[i] = currentRankValue % 2;
        transferValue = currentRankValue / 2;
    }
}

int getDecimalNumber(bool* binaryNumber)
{
    int currentValue = 0;
    int nextTerm = 1;
    for (int i = 0; i < SIZE_OF_BINARY_NUMBER; ++i) {
        if (binaryNumber[i]) {
            currentValue += nextTerm;
        }
        nextTerm *= 2;
    }
    return currentValue;
}

void printBinaryNumber(bool* binaryNumber)
{
    for (int i = SIZE_OF_BINARY_NUMBER - 1; i >= 0; --i) {
        printf("%d", binaryNumber[i]);
    }
    printf("\n");
}

int main()
{
    printf("Enter first number and second number throw a space:\n");
    int firstNumber = 0;
    scanf("%d", &firstNumber);
    int secondNumber = 0;
    scanf("%d", &secondNumber);

    bool binaryFirstNumber[SIZE_OF_BINARY_NUMBER];
    memset(binaryFirstNumber, false, SIZE_OF_BINARY_NUMBER);
    getBinaryNumber(firstNumber, binaryFirstNumber);

    bool binarySecondNumber[SIZE_OF_BINARY_NUMBER];
    memset(binarySecondNumber, false, SIZE_OF_BINARY_NUMBER);
    getBinaryNumber(secondNumber, binarySecondNumber);

    bool binarySum[SIZE_OF_BINARY_NUMBER];
    memset(binarySum, false, SIZE_OF_BINARY_NUMBER);
    getBinarySum(binaryFirstNumber, binarySecondNumber, binarySum);

    printf("First binary number:\n");
    printBinaryNumber(binaryFirstNumber);

    printf("Second binary number:\n");
    printBinaryNumber(binarySecondNumber);

    printf("Binary sum:\n");
    printBinaryNumber(binarySum);

    int decimalSum = getDecimalNumber(binarySum);

    printf("Decimal sum:\n");
    printf("%d\n", decimalSum);

    return 0;
}
