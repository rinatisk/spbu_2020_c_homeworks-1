#include "stdio.h"
#include "string.h"
#include <stdbool.h>

int main()
{
    int n = 0;
    printf("Write a number n:\n");
    scanf("%d", &n);
    bool a[n];
    memset(a, true, n);
    for (int i = 2; i * i <= n; ++i) {
        if (a[i]) {
            for (int j = i * i; j <= n; j += i) {
                a[j] = false;
            }
        }
    }
    printf("Prime number less then n:\n");
    for (int i = 2; i < n; ++i) {
        if (a[i]) {
            printf("%d ", i);
        }
    }
}