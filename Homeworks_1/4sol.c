#include <string.h>
#include <stdio.h>
#include <stdbool.h>
int main()
{
    int n = 0;
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
    for (int i = 2; i < n; ++i) {
        if (a[i]) {
            printf("%d%s", i, " ");
        }
    }
}