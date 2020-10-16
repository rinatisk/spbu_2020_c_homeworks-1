#include <math.h>
#include <stdbool.h>
#include <stdio.h>

const int SHIFT = 1023;

int getDecimalNumber(int start, int end, char* number)
{
    int currentPlus = 1;
    int decimalNumber = 0;
    for (int i = end; i > start - 1; i--) {
        if (number[i] == '1')
            decimalNumber += currentPlus;
        currentPlus *= 2;
    }
    return decimalNumber;
}

double getSmallDecimalNumber(int start, int end, char* number)
{
    double currentPlus = 0.5;
    double decimalNumber = 0;
    for (int i = start; i <= end; i++) {
        if (number[i] == '1')
            decimalNumber += currentPlus;
        currentPlus /= 2;
    }
    return decimalNumber;
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

int getSign(char* binaryNumber, int sign)
{
    if (binaryNumber[0] == '1') {
        sign = -1;
    }
    return sign;
}
char getSignOfMantissa(int sign)
{
    char signOfMantissa = '+';
    if (sign == -1) {
        signOfMantissa = '-';
    }
    return signOfMantissa;
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
    int sign = 1;
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

    sign = getSign(binaryNumber, sign);
    int exponent = getDecimalNumber(1, 11, binaryNumber) - SHIFT;
    double mantissa = getSmallDecimalNumber(12, 63, binaryNumber) + 1;
    char signOfMantissa = getSignOfMantissa(sign);
    printf("%c%lg * %d ^ {%d}", signOfMantissa, mantissa, 2, exponent);

    return 0;
}