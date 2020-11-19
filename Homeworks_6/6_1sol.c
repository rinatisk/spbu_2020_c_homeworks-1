#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../library/fileOperations.h"
#include "../library/commonUtils/hash_Table.h"

int main()
{
    FILE* text = NULL;
    text = fopen("../Homeworks_6/input.txt", "r");
    HashTable* hashtable = createHashTable(10);
    char* currentKey = getWord(text);
    while (currentKey != NULL) {
        add(hashtable, currentKey, 1);
        currentKey = getWord(text);
    }
    delete(hashtable, "the");
    printInfoAboutTable(hashtable);
    printTopWords(hashtable, 12);
    free(currentKey);
    destroyHashTable(hashtable);
    fclose(text);
    return 0;
}