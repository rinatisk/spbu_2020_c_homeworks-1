#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int firstArray[], int secondArray[], int sizeFirstArray, int sizeSecondArray, int mergedArray[])
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < sizeFirstArray && j < sizeSecondArray) {
        if (firstArray[i] < secondArray[j]) {
            mergedArray[k] = firstArray[i];
            k++;
            i++;
        } else {
            mergedArray[k] = secondArray[j];
            k++;
            j++;
        }
    }

    while (i < sizeFirstArray) {
        mergedArray[k] = firstArray[i];
        k++;
        i++;
    }
    while (j < sizeSecondArray) {
        mergedArray[k] = secondArray[j];
        k++;
        j++;
    }
}

int main()
{
    printf("write size of first array and elements of first array:\n");
    int sizeFirstArray = 0;
    scanf("%d", &sizeFirstArray);
    int* firstArray = calloc(sizeFirstArray, sizeof(int));
    for (int i = sizeFirstArray - 1; i >= 0; --i) {
        scanf("%d", &firstArray[i]);
    }

    printf("write size of second array and elements of second array:\n");
    int sizeSecondArray = 0;
    scanf("%d", &sizeSecondArray);
    int* secondArray = calloc(sizeSecondArray, sizeof(int));
    for (int i = sizeSecondArray - 1; i >= 0; --i) {
        scanf("%d", &secondArray[i]);
    }
    int* mergedArray = calloc(sizeFirstArray + sizeSecondArray, sizeof(int));

    mergeArrays(firstArray, secondArray, sizeFirstArray, sizeSecondArray, mergedArray);

    printf("Array after merging\n");
    for (int i = sizeFirstArray + sizeSecondArray - 1; i >= 0; --i)
        printf("%d ", mergedArray[i]);

    return 0;
}
