#include <stdio.h>

int computeFactorialByRecursion(int n)
{
    if (n <= 1) {
        return 1;
    }
    return n * computeFactorialByRecursion(n - 1);
}

int main()
{
    printf("Write n:\n");
    int n = 0;
    scanf("%d", &n);
    n = computeFactorialByRecursion(n);
    printf("factorial n = %d", n, "\n");
    return 0;
}