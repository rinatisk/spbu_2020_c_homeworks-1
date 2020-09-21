#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    scanf("%d", &n);
    bool a[n];
    for (int i = 0; i < n; ++i) {
        a[i] = true;
    }
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