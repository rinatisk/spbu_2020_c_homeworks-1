#include <stdio.h>
#include "../library/commonUtils/numericOperations.h"

int main()
{
    int currentMove = 0;
    int sideSize = 0;
    int stepsNumber = 0;
    printf("Write side of matrix size:\n");
    scanf("%d", &sideSize);
    int **matrix = dynamic_array_alloc(sideSize, sideSize);
    printf("Write matrix elements through a space\n");
    for (int i = 0; i < sideSize; ++i) {
        for (int j = 0; j < sideSize; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int x = sideSize / 2;
    int y = sideSize / 2;
    for (int k = 1; k < sideSize; k++) {
        stepsNumber = (k == (sideSize - 1) ? 3 : 2);
        for (int j = 0; j < stepsNumber; j++) {
            for (int i = 0; i < k; i++) {
                printf("%d ", matrix[x][y]);
                switch (currentMove) {
                case 0:
                    y++;
                    break;
                case 1:
                    x++;
                    break;
                case 2:
                    y--;
                    break;
                case 3:
                    x--;
                    break;
                }
            }
            currentMove = (currentMove >= 3 ? 0 : currentMove + 1);
        }
    }
    printf("%d\n", matrix[x][y]);
    dynamic_array_free(matrix, sideSize);
}