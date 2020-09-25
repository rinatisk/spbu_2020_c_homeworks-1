#include "numericOperations.h"
#include <malloc.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int **dynamic_array_alloc(int N, int M)
{
    int **A = (int **) malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *) malloc(M * sizeof(int));
    }
    return A;
}

void dynamic_array_free(int **A, int N)
{

    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);

}

void swap(int a, int b)
{
    int c = a;
    a = b;
    b = c;
}