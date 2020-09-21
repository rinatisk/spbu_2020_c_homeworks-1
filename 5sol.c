#include <stdio.h>

int main()
{
    int size, max = 0;
    scanf("%d", &size);
    int s[100000];
    int x[size];
    for (int i = 0; i < size; ++i) {
        scanf("%d", &x[i]);
        s[x[i]]++;
        if ((s[x[i]] >= 2) && (x[i] > max)) {
            max = x[i];
        }
    }
    printf("%d", max);
    return 0;
}