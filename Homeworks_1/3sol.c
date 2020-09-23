#include <stdio.h>
#include "string.h"

int const MaxSize = 100;

int main()
{
    char string[MaxSize];
    char substring[MaxSize];
    fgets(string, MaxSize, stdin);
    fgets(substring, MaxSize, stdin);
    int sizeString = strlen(string);
    int sizeSubstring = strlen(substring);
    int quantSubStrings = 0, currentSymbol = 0, currentStartSymbol = 0;
    int i = 0, j = 0;
    while (i + sizeSubstring <= sizeString) {
        j = 0;
        while (string[i] == substring[j]) {
            currentSymbol++;
            i++;
            j++;
        }
        if (currentSymbol == sizeSubstring - 1) {
            quantSubStrings++;
            currentSymbol = 0;
        }
        currentStartSymbol++;
        i = currentStartSymbol;
        currentSymbol = 0;
    }
    printf("%d", quantSubStrings);
    return 0;
}