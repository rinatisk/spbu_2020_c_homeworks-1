#include <stdio.h>
#include <string.h>

int main()
{
    int n = 0;
    int numbers[10];
    memset(numbers, 0, 10 * sizeof(int));
    printf("write n:\n");
    scanf("%d", &n);
    int currentNumber = 0;
    while (n > 0) {
        currentNumber = n % 10;
        numbers[currentNumber]++;
        n = n / 10;
    }
    if (numbers[0] != 0) {
        for (int i = 1; i < 10; ++i) {
            if (numbers[i] != 0) {
                numbers[i]--;
                printf("%d", i);
                break;
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        while (numbers[i] > 0) {
            printf("%d", i);
            numbers[i]--;
        }
    }
    return 0;
}