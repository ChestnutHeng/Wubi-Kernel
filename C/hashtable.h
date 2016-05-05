#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stdint.h"
#include "string.h"
#include "stdlib.h"

#define HASHTABLE_NUM 1217
#define HASHTABLE_MAX_ITEM_NUM 2500
#define HASHTABLE_MAX_ITEM_SIZE 200

typedef struct HashUnit
{
    char word[HASHTABLE_MAX_ITEM_SIZE];
    int32_t next;
}HashUnit;

typedef struct HashTable
{
    HashUnit *hashUnit;
    uint8_t *hashFlag;
    int32_t hashEmpty;
}HashTable;

HashTable ** GetHashTable();

void InitHashTable(HashTable *ht);

int32_t HashTableInsert(HashTable *ht, const char *str);

void FreeHashTable(HashTable **ht);

#endif
