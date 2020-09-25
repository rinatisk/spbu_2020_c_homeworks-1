#include <malloc.h>

int* dynamic_array_alloc_one_dim(int N)
{
    int* A = (int*)calloc(N, sizeof(int));
    return A;
}

void dynamic_array_free_one_dim(int* A)
{
    free(A);
}