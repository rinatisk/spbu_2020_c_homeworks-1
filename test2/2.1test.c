#include <stdio.h>

int computeFibonacci(int number)
{
    int firstPrevious = 1;
    int secondPrevious = 1;
    int toChangeValue = 0;
    if (number <= 2) return 1;
    for (int i = 2; i < number; ++i) {
        toChangeValue = firstPrevious + secondPrevious;
        firstPrevious = secondPrevious;
        secondPrevious = toChangeValue;
    }
    return secondPrevious;
}

int main()
{
    printf("Write number:\n");
    int number = 0;
    scanf("%d", &number);
    printf("%d", computeFibonacci(number));
    return 0;
}
