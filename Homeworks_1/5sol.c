#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../library/commonUtils/arrayOperations.h"

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main()
{
    int size = 0;
    int max = 0;
    printf("Write the number of digits:\n");
    scanf("%d", &size);
    int* s = dynamic_array_alloc_one_dim(size);
    printf("Write a digits throw a space:\n");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &s[i]);
    }
    qsort(s, size, sizeof(int), cmpfunc);
    for (int i = size - 1; i > 1; --i) {
        if (s[i] == s[i-1]){
            max = s[i];
            break;
        }
    }
    printf("answer is:\n");
    printf("%d\n", max);
    dynamic_array_free_one_dim(s);
    return 0;
}