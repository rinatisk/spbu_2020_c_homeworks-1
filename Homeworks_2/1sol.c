#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void decompositionRecursion(int* a, int remainTerms, int maxTerm, int numberTerm)
{
    if (remainTerms < 0) return;
    if (remainTerms == 0) {
        int j;
        for (j = 0; j < numberTerm - 1; j++) {
            printf("%d + ", a[j]);
        }
        printf("%d\n", a[numberTerm - 1]);

    }
    else {
        if (remainTerms - maxTerm >= 0) {
            a[numberTerm] = maxTerm;
            decompositionRecursion(a, remainTerms - maxTerm, maxTerm, numberTerm + 1);
        }

        if (maxTerm - 1 > 0) {
            decompositionRecursion(a, remainTerms, maxTerm - 1, numberTerm);
        }
    }
    return;
}

int main()
{
    int originalNumber = 0;
    scanf("%d", &originalNumber);
    int* a = (int*) calloc(originalNumber, sizeof(int));
    memset(a, 0, sizeof(int) * originalNumber);
    decompositionRecursion(a, originalNumber, originalNumber, 0);
    return 0;
}