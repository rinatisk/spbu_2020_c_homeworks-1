#include <stdio.h>
#include "../library/commonUtils/numericOperations.h"
#include <stdlib.h>
int main()
{
    int m = 0;
    int n = 0;
    scanf("%d%d", &m, &n);
    int x[m + n];
    for (int i = 0; i < m + n; ++i) {
        scanf("%d", &x[i]);
    }
    int left = 0;
    int right = m - 1;
    while (left < right) {
        swap(right, left);
        right--;
        left++;
    }
    left = m;
    right = m + n - 1;
    while (left < right) {
        swap(right, left);
        right--;
        left++;
    }
    left = 0;
    right = m + n - 1;
    while (left < right) {
        swap(right, left);
        right--;
        left++;
    }
    for (int i = 0; i < m + n; ++i) {
        printf("%d%s", x[i], " ");
    }
    free(x);
    return 0;
}