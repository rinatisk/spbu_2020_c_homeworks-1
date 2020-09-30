#include <stdio.h>

int computeFactorialByIteration(int n)
{
    int currentFactorialValue = 1;
    for (int i = 1; i <= n; ++i) {
        currentFactorialValue *= i;
    }
    return currentFactorialValue;
}

int main()
{
    printf("Write n:\n");
    int n = 0;
    scanf("%d", &n);
    n = computeFactorialByIteration(n);
    printf("factorial n = %d", n, "\n");
    return 0;
}