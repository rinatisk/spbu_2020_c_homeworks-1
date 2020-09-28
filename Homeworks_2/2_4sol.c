#include <stdio.h>
#include <string.h>

const int numberOfDigits = 10;

int countDigits(int digits[], int n)
{
    int currentNumber = 0;
    while (n > 0) {
        currentNumber = n % 10;
        digits[currentNumber]++;
        n = n / 10;
    }
    return *digits;
}

void printSmallestNumber(int digits[])
{
    if (digits[0] != 0) {
        int i = 1;
        while (digits[i] == 0) {
            i++;
        }
        digits[i]--;
        printf("%d", i);
    }
    for (int i = 0; i < numberOfDigits; ++i) {
        while (digits[i] > 0) {
            printf("%d", i);
            digits[i]--;
        }
    }
}

int main()
{
    int n = 0;
    int digits[numberOfDigits];
    memset(digits, 0, numberOfDigits * sizeof(int));
    printf("write number:\n");
    scanf("%d", &n);
    *digits = countDigits(digits, n);
    printSmallestNumber(digits);
    return 0;
}