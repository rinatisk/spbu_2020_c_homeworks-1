#ifndef SPBU_2020_C_HOMEWORKS_1_HASH_TABLE_H
#define SPBU_2020_C_HOMEWORKS_1_HASH_TABLE_H

#include <stdbool.h>

typedef struct HashTable HashTable;

typedef struct HashElement HashElement;

HashElement* createHashElement(char* key);

HashTable* createHashTable(int polynomFactor);

int getHash(char* key, int polynomFactor, int module);

float getLoadFactor(HashTable* hashTable);

bool add(HashTable* table, char* key, int value);

bool getValue(HashTable* table, char* key, int* result);

void destroyHashTable(HashTable* table);

bool deleteElementFromKey(HashTable* table, char* key);

void printHashTable(HashTable* hashTable);

void printTopWords(HashTable* hashTable, int topNumber);

void printInfoAboutTable(HashTable* hashTable);

#endif //SPBU_2020_C_HOMEWORKS_1_HASH_TABLE_H
