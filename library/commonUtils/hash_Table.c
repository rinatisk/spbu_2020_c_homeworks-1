#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_Table.h"
#include "numericOperations.h"

enum CellType { empty, used,
        deleted };

typedef struct HashElement {
    int value;
    char* key;
    int numberOfProbes;
} HashElement;

typedef struct HashTable {
    HashElement** hashTable;
    enum CellType* types;
    int bucketCount;
    int elementCount;
    int polynomFactor;
} HashTable;

const float maxLoadFactor = 0.7;

float getLoadFactor(HashTable* hashTable)
{
    return (float)hashTable->elementCount / (float)hashTable->bucketCount;
}

HashElement* createHashElement(char* key)
{
    if (key == NULL) {
        return NULL;
    }
    HashElement* newElement = (HashElement*)malloc(sizeof(HashElement));
    int keySize = strlen(key);
    newElement->key = (char*)malloc(sizeof(char) * keySize);
    strcpy(newElement->key, key);

    newElement->numberOfProbes = 0;
    newElement->value = 1;

    return newElement;
}

bool deleteHashElement(HashElement* hashElement)
{
    if (hashElement == NULL) {
        return false;
    }
    free(hashElement->key);
    free(hashElement);
    return true;
}

HashTable* createHashTableWithSize(int polynomFactor, int size)
{
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    newTable->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(newTable->types, (int)empty, size * sizeof(enum CellType));
    newTable->bucketCount = size;
    memset(newTable->hashTable, 0, size * sizeof(HashElement*));
    newTable->elementCount = 0;
    newTable->polynomFactor = polynomFactor;
    return newTable;
}

HashTable* createHashTable(int polynomFactor)
{
    return createHashTableWithSize(polynomFactor, 1);
}

int getHash(char* key, int polynomFactor, int module)
{
    int size = strlen(key);
    int currentHash = 0;
    for (int i = 0; i < size; ++i) {
        currentHash = ((currentHash * polynomFactor) + (key[i] - 'a')) % module;
    }
    return currentHash;
}

void destroyHashTable(HashTable* table)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->hashTable[i] != empty) {
            deleteHashElement(table->hashTable[i]);
        }
    }
    free(table->hashTable);
    free(table->types);
    free(table);
}

void expandTable(HashTable* table)
{
    HashElement** oldElements = table->hashTable;
    enum CellType* oldTypes = table->types;

    int oldSize = table->bucketCount;
    int size = table->bucketCount * 2;

    table->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    table->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(table->hashTable, 0, size * sizeof(HashElement*));
    memset(table->types, (int)empty, size * sizeof(enum CellType));
    table->bucketCount = size;
    table->elementCount = 0;

    for (int i = 0; i < oldSize; ++i) {
        if (oldTypes[i] != used)
            continue;
        HashElement* element = oldElements[i];
        add(table, element->key, element->value);
        deleteHashElement(element);
    }

    free(oldElements);
    free(oldTypes);
}

int getIndex(HashTable* hashTable, int probeNumber, int hash)
{
    return (hash + (probeNumber + probeNumber * probeNumber) / 2) % hashTable->bucketCount;
}

bool add(HashTable* table, char* key, int value)
{
    int probeStep = 0;
    int startHash = getHash(key, table->polynomFactor, table->bucketCount);
    int currentIndex = getIndex(table, probeStep, startHash);
    while (table->types[currentIndex] == used) {
        if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
            table->hashTable[currentIndex]->numberOfProbes = max(table->hashTable[currentIndex]->numberOfProbes, probeStep);
            table->hashTable[currentIndex]->value++;
            return true;
        }
        ++probeStep;
        currentIndex = getIndex(table, probeStep, startHash);
    }
    HashElement* newElement = createHashElement(key);
    newElement->value = value;
    newElement->numberOfProbes = probeStep;
    table->hashTable[currentIndex] = newElement;
    table->types[currentIndex] = used;
    table->elementCount++;

    if (getLoadFactor(table) > maxLoadFactor)
        expandTable(table);

    return true;
}

bool deleteElementFromKey(HashTable* table, char* key)
{
    int probeStep = 0;
    int startHash = getHash(key, table->polynomFactor, table->bucketCount);
    HashElement* newElement = createHashElement(key);
    int currentIndex = startHash;
    while (table->types[currentIndex] == used) {
        if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
            table->types[currentIndex] = deleted;
            table->elementCount--;
            deleteHashElement(table->hashTable[currentIndex]);
            return true;
        }
        currentIndex = getIndex(table, probeStep, startHash);
        if (currentIndex == startHash) {
            return false;
        }
    }
    table->hashTable[currentIndex] = newElement;
    table->types[currentIndex] = used;
    table->elementCount++;

    if (getLoadFactor(table) > maxLoadFactor)
        expandTable(table);

    return true;
}

bool getValue(HashTable* table, char* key, int* result)
{
    int probeStep = 1;
    int startIndex = getHash(key, table->polynomFactor, table->bucketCount);
    int currentIndex = startIndex;
    printf("%d", table->types[0]);
    while (table->types[currentIndex] != empty) {
        if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
            *result = table->hashTable[currentIndex]->value;
            return true;
        }
        currentIndex = (currentIndex + probeStep * probeStep) % table->bucketCount;
        probeStep++;
        if (currentIndex == startIndex) {
            return false;
        }
    }
    return false;
}

void printHashTable(HashTable* hashTable)
{
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] == used) {
            for (int j = 0; hashTable->hashTable[i]->key[j] != '\0'; ++j) {
                printf("%c", hashTable->hashTable[i]->key[j]);
            }
            printf("- %d probes %d value \n", hashTable->hashTable[i]->numberOfProbes, hashTable->hashTable[i]->value);
        }
    }
}

void printNumberOfWords(HashTable* hashTable)
{
    printf("number of words - %d\n", hashTable->elementCount);
}

void printNumberOfEmptyBucket(HashTable* hashTable)
{
    int numberOfEmptyBucket = 0;
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] != used) {
            numberOfEmptyBucket++;
        }
    }
    printf("number of empty bucket - %d\n", numberOfEmptyBucket);
}

void printAverageProbeNumber(HashTable* hashTable)
{
    int countProbe = 0;
    int sumProbe = 0;
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] == used) {
            countProbe++;
            sumProbe += hashTable->hashTable[i]->numberOfProbes;
        }
    }
    printf("average probe number - %f\n", (float)(sumProbe / (float)countProbe));
}

int getMaxValue(int* UnsortedArray, int size)
{
    int maxValue = 0;
    int maxValueIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (UnsortedArray[i] > maxValue) {
            maxValue = UnsortedArray[i];
            maxValueIndex = i;
        }
    }
    UnsortedArray[maxValueIndex] = 0;
    return maxValue;
}

void printKeysByProbe(HashTable* hashTable, int probe)
{
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] == used && hashTable->hashTable[i]->numberOfProbes == probe) {
            for (int j = 0; hashTable->hashTable[i]->key[j] != '\0'; ++j) {
                printf("%c", hashTable->hashTable[i]->key[j]);
            }
            printf(" - %d \n", probe);
        }
    }
}

void printKeysByValue(HashTable* hashTable, int value)
{
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] == used && hashTable->hashTable[i]->value == value) {
            for (int j = 0; hashTable->hashTable[i]->key[j] != '\0'; ++j) {
                printf("%c", hashTable->hashTable[i]->key[j]);
            }
            printf("- %d \n", value);
        }
    }
}

void printMaxProbe(HashTable* hashTable)
{
    int maxProbe = 0;
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] == used) {
            maxProbe = max(maxProbe, hashTable->hashTable[i]->numberOfProbes);
        }
    }
    printf("max probe number - %d, words:\n", maxProbe);
    printKeysByProbe(hashTable, maxProbe);
}

void printTopWords(HashTable* hashTable, int topNumber)
{
    int* valuesArray = calloc(hashTable->elementCount, sizeof(int));
    int toPushIndex = 0;
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] == used) {
            valuesArray[toPushIndex] = hashTable->hashTable[i]->value;
            toPushIndex++;
        }
    }

    int* valuesArraySort = calloc(min(hashTable->elementCount, topNumber), sizeof(int));
    for (int i = 0; i < min(hashTable->elementCount, topNumber); ++i) {
        valuesArraySort[i] = (getMaxValue(valuesArray, hashTable->elementCount));
    }
    for (int i = 0; i < min(hashTable->elementCount, topNumber); ++i) {
        if (i > 0 && valuesArraySort[i] == valuesArraySort[i - 1]) {
            continue;
        }
        printKeysByValue(hashTable, valuesArraySort[i]);
    }
    free(valuesArray);
    free(valuesArraySort);
}

void printInfoAboutTable(HashTable* hashTable)
{
    printNumberOfEmptyBucket(hashTable);
    printNumberOfWords(hashTable);
    printAverageProbeNumber(hashTable);
    printMaxProbe(hashTable);
    printf("loadFactor - %f\n", getLoadFactor(hashTable));
}
