#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileOperations.h"


bool isLetter(char character)
{
    return ('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z');
}

char* expandString(char* oldString, int* oldSize)
{
    char* newString = (char*)malloc(*oldSize * 2 * sizeof(char));
    if (newString == NULL) {
        printf("error in allocating memory\n");
        return NULL;

   }
    memset(newString, 0, *oldSize * 2 * sizeof(char));
    for (int i = 0; i < *oldSize; ++i) {
        newString[i] = oldString[i];
    }
    free(oldString);
    *oldSize *= 2;
    return newString;
}

char* getWord(FILE* file)
{
    char currentSymbol = (char)fgetc(file);
    int i = 0;
    int size = 1;
    char* word = (char*)malloc(sizeof(char));
    word[0] = 0;
    while (!isLetter(currentSymbol) && !feof(file)) {
        currentSymbol = (char)fgetc(file);
    }
    while (!feof(file) && isLetter(currentSymbol)) {
        if (i == size)
            word = expandString(word, &size);
        word[i] = (char)tolower(currentSymbol);
        ++i;
        currentSymbol = (char)fgetc(file);
    }
    if (i == size)
        word = expandString(word, &size);

    word[i] = '\0';
    if (feof(file)) {
        if (size > 1)
            return word;
        else {
            free(word);
            return NULL;
        }
    }
    return word;
}
