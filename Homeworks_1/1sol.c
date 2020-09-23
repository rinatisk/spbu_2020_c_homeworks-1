#include <stdio.h>
#include <stdlib.h>

int main()
{
    int d = 0;
    int n = 0;
    scanf("%d", &n);
    int matrix[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int x = n / 2;
    int y = n / 2;
    for (int k = 1; k <= (n - 1); k++) {
        for (int j = 0; j < (k == (n - 1) ? 3 : 2); j++) {
            for (int i = 0; i < k; i++) {
                printf("%d%s", matrix[x][y], " ");

                switch (d) {
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
            d = (d >= 3 ? 0 : d + 1);
        }
    }
    printf("%d", matrix[x][y]);
    free(matrix);
}