#include <stdio.h>

int main()
{
    printf("Write n:\n");
    int n = 0;
    scanf("%d", &n);
    int answer = 1;
    for (int i = 1; i < n + 1; ++i) {
        answer *= i;
    }
    printf("factorial n = %d", answer, "\n");
    return 0;
}