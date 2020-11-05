#include <math.h>
#include <stdbool.h>
#include <stdio.h>

const int SHIFT = 1023;

int getExponent(int start, int end, char* number)
{
    int currentTerm = 1;
    int decimalNumber = 0;
    for (int i = end; i > start - 1; i--) {
        if (number[i] == '1')
            decimalNumber += currentTerm;
        currentTerm *= 2;
    }
    return decimalNumber - SHIFT;
}

double getMantissa(int start, int end, char* number)
{
    double currentTerm = 0.5;
    double decimalNumber = 0;
    for (int i = start; i <= end; i++) {
        if (number[i] == '1')
            decimalNumber += currentTerm;
        currentTerm /= 2;
    }
    return decimalNumber + 1;
}

char* getBinaryNumber(char* binaryNumber, unsigned char* bytes)
{
    int bit = 0b10000000;
    for (int i = 0; i < 8; ++i) {
        bit = 0b10000000;
        for (int j = 0; j < 8; ++j) {
            binaryNumber[j + i * 8] = ((bytes[i] & bit) ? '1' : '0');
            bit = bit >> 1;
        }
    }
    return binaryNumber;
}

int getSign(char* binaryNumber)
{
    return binaryNumber[0] == '1' ? -1 : 1;
}
char getSignOfMantissa(int sign)
{
    return sign == -1 ? '-' : '+';
}

unsigned char* reverseBytes(unsigned char* bytes)
{
    unsigned char toSwap = 0;
    for (int i = 0; i < 4; ++i) {
        toSwap = bytes[i];
        bytes[i] = bytes[7 - i];
        bytes[7 - i] = toSwap;
    }
    return bytes;
}

int main()
{
    double number = 0;
    printf("Enter a number:\n");
    scanf("%lg", &number);
    if (number == 0) {
        printf("%d * %d ^ {%d}", 0, 2, 0);
        return 0;
    }

    unsigned char* bytes = (unsigned char*)&number;
    int sign = 0;
    bytes = reverseBytes(bytes);

    char binaryNumber[64];
    int bit = 0b10000000;
    for (int i = 0; i < 8; ++i) {
        bit = 0b10000000;
        for (int j = 0; j < 8; ++j) {
            binaryNumber[j + i * 8] = ((bytes[i] & bit) ? '1' : '0');
            bit = bit >> 1;
        }
    }

    sign = getSign(binaryNumber);
    int exponent = getExponent(1, 11, binaryNumber);
    double mantissa = getMantissa(12, 63, binaryNumber);
    char signOfMantissa = getSignOfMantissa(sign);
    printf("%c%lg * %d ^ {%d}", signOfMantissa, mantissa, 2, exponent);

    return 0;
}
