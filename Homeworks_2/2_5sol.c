#include <stdio.h>

int computeFactorial(int n)
{
    if (n <= 1) return 1;
    return n * computeFactorial(n - 1);

}

int main()
{
    printf("Write n:\n");
    int n;
    scanf("%d", &n);
    n = computeFactorial(n);
    printf("factorial n = %d", n, "\n");
    return 0;
}