#include <stdio.h>

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int x[m + n];
    for (int i = 0; i < m + n; ++i) {
        scanf("%d", &x[i]);
    }
    int tmp = 0;
    int left = 0;
    int right = m - 1;
    while (left < right) {
        tmp = x[left];
        x[left] = x[right];
        x[right] = tmp;
        right--;
        left++;
    }
    left = m;
    right = m + n - 1;
    while (left < right) {
        tmp = x[left];
        x[left] = x[right];
        x[right] = tmp;
        right--;
        left++;
    }
    left = 0;
    right = m + n - 1;
    while (left < right) {
        tmp = x[left];
        x[left] = x[right];
        x[right] = tmp;
        right--;
        left++;
    }
    for (int i = 0; i < m + n; ++i) {
        printf("%d%s", x[i], " ");
    }
    return 0;
}