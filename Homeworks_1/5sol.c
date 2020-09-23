#include <stdbool.h>
#include <stdio.h>
int const SizeValues = 10000;

int main()
{
    int size = 0;
    int max = 0;
    scanf("%d", &size);
    bool s[SizeValues];
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