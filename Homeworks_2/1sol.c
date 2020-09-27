#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decomposNumber(int* a, int remainTerms, int maxTerm, int numberTerm)
{
    if (remainTerms < 0) {
        return;
    }
    if (remainTerms == 0) {
        for (int i = 0; i < numberTerm - 1; ++i) {
            printf("%d + ", a[i]);
        }
        printf("%d\n", a[numberTerm - 1]);
    } else {
        if (remainTerms - maxTerm >= 0) {
            a[numberTerm] = maxTerm;
            decomposNumber(a, remainTerms - maxTerm, maxTerm, numberTerm + 1);
        }

        if (maxTerm - 1 > 0) {
            decomposNumber(a, remainTerms, maxTerm - 1, numberTerm);
        }
    }
}

int main()
{
    int originalNumber = 0;
    scanf("%d", &originalNumber);
    int* a = (int*)calloc(originalNumber, sizeof(int));
    memset(a, 0, sizeof(int) * originalNumber);
    decomposNumber(a, originalNumber, originalNumber, 0);
    free(a);
    return 0;
}