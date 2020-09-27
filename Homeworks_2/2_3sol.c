#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("Write n:\n");
    scanf("%d", &n);
    printf("Write numbers throw the space:\n");
    int* a = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    int nonZeroIndex = 0;
    for (int j = 0; j < n; ++j) {
        if (a[j] != 0) {
            a[nonZeroIndex] = a[j];
            nonZeroIndex = nonZeroIndex + 1;
        }
    }
    while (nonZeroIndex <= n) {
        a[nonZeroIndex] = 0;
        nonZeroIndex++;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    free(a);
    return 0;
}
