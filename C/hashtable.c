#include "hashtable.h"

HashTable ** GetHashTable()
{
    static HashTable * ht = NULL;
    if(ht == NULL)
    {
        ht = (HashTable *)malloc(sizeof(HashTable));
        if(ht == NULL)return NULL;
        ht -> hashUnit = (HashUnit *)malloc(HASHTABLE_MAX_ITEM_NUM * sizeof(HashUnit));
        if(ht -> hashUnit == NULL)return NULL;
        ht -> hashFlag = (uint8_t *)malloc(HASHTABLE_NUM * sizeof(uint8_t));
        if(ht -> hashFlag == NULL)return NULL;
    }
    return &ht;
}

void InitHashTable(HashTable *ht)
{
    if (NULL == ht)
    {
        return;
    }

    memset(ht -> hashFlag, 0, sizeof(uint8_t) * HASHTABLE_NUM);
    ht -> hashEmpty = HASHTABLE_NUM;
}

//int hash table unit
void SetHash(HashTable *ht, int32_t key, const char *str)
{
    ht -> hashUnit[key].next = -1;
    strcpy(ht -> hashUnit[key].word, str);
}

//get hash value of str
static int32_t hash(const char *str)
{
    int32_t i, l = (strlen(str) + 1) >> 1;
    uint32_t ret = 0;
    unsigned short *s = (unsigned short*)str;
    for (i = 0; i < l; ++i)
        ret ^= s[i] << (i & 0x0F);
    return ret % HASHTABLE_NUM;
}

//insert a str to hash table
int32_t HashTableInsert(HashTable *ht, const char *str)
{
    int32_t key = hash(str);
    if(ht -> hashFlag[key] == 0)
    {
        ht -> hashFlag[key] = 1;
        SetHash(ht, key, str);
        return 0;
    }
    while(key != -1)
    {
        if(strcmp(ht -> hashUnit[key].word, str) == 0)
            return 1;
        if(ht -> hashUnit[key].next == -1)break;
        key = ht -> hashUnit[key].next;
    }
    ht -> hashUnit[key].next = ++(ht -> hashEmpty);
    SetHash(ht, ht -> hashEmpty, str);
    return 0;
}

void FreeHashTable(HashTable **ht)
{
    if(ht != NULL)
    {
        if((*ht) -> hashUnit != NULL)
        {
            free((*ht) -> hashUnit);
            (*ht) -> hashUnit = NULL;
        }
        if((*ht) -> hashFlag != NULL)
        {
            free((*ht) -> hashFlag);
            (*ht) -> hashFlag = NULL;
        }
        free(*ht);
        *ht = NULL;
    }
}

