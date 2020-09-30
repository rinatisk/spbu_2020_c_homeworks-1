#include "numericOperations.h"
#include <malloc.h>

int** dynamic_array_alloc(int N, int M)
{
    int** A = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)calloc(M, sizeof(int));
    }
    return A;
}

void dynamic_array_free(int** A, int N)
{

    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
}
