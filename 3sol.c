#include <stdio.h>
#include "string.h"

int main()
{
    char s1[20];
    char s2[20];
    fgets(s1, 20, stdin);
    fgets(s2, 20, stdin);
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    int s = 0, c = 0, p = 0;
    int i = 0, j = 0;
    while (i + size2 <= size1) {
        j = 0;
        while (s1[i] == s2[j]) {
            c++;
            i++;
            j++;
        }
        if (c == size2 - 1) {
            s++;
            c = 0;
        }
        p++;
        i = p;
        c = 0;
    }
    printf("%d", s);
    return 0;
}