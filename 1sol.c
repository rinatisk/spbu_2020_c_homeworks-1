#include <stdio.h>

int main()
{
    int x = 0;
    int y = 0;
    int d = 0;
    int n;
    scanf("%d", &n);
    int mtrx[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mtrx[i][j]);
        }
    }
    x = n / 2;
    y = n / 2;
    for (int k = 1; k <= (n - 1); k++) {
        for (int j = 0; j < (k == (n - 1) ? 3 : 2); j++) {
            for (int i = 0; i < k; i++) {
                printf("%d%s", mtrx[x][y], " ");

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
    printf("%d", mtrx[x][y]);

}