#include "heap.h"
#include "string.h"

static void swap(void** first, void** second)
{
    void* tmp = *first;
    *first = *second;
    *second = tmp;
}

int32_t HeapInit(struct Heap* pHeap, HeapSizeType n, int32_t (*cmp)(const void*, const void*))
{
    pHeap->n = 0u;
    pHeap->nmax = n;
    pHeap->compare = cmp;
    pHeap->item = (void**)calloc(n, sizeof(void*));
    if (NULL == pHeap)
    {
        return -1;
    }
    return 0;
}

int32_t HeapFree(struct Heap* pHeap)
{
    pHeap->n = 0u;
    pHeap->nmax = 0u;
    pHeap->compare = NULL;
    free(pHeap->item);
    pHeap->item = NULL;
    return 0;
}

HeapSizeType HeapCapacity(struct Heap* pHeap)
{
    return pHeap->nmax;
}

/**
 * CAUTION: This function is dangerous because it doesn't realloc pHeap->item to fit a new pHeap->nmax.
 * It's just used to avoid memory fragmentation caused by frequent malloc and free operation now. 
 * You can make it safer and stronger if necessary.
 */
void HeapResize(struct Heap* pHeap, const HeapSizeType sz)
{
    pHeap->nmax = sz;
}

void HeapClear(struct Heap* pHeap)
{
    pHeap->n = 0u;
    memset(pHeap->item, 0, pHeap->nmax * sizeof(void*));
}


int32_t HeapEmpty(struct Heap* pHeap)
{
    return 0 == pHeap->n ? TRUE : FALSE;
}

int32_t HeapFull(struct Heap* pHeap)
{
    return pHeap->n == pHeap->nmax ? TRUE : FALSE;
}

void* HeapTop(struct Heap* pHeap)
{
    return pHeap->item[0];
}

HeapSizeType HeapSize(struct Heap* pHeap)
{
    return pHeap->n;
}

int32_t HeapPush(struct Heap* pHeap, void* pNewItem)
{
    HeapSizeType i;
    HeapSizeType j;
    if (TRUE == HeapFull(pHeap))
    {
        return FALSE;
    }
    i = pHeap->n++;
    while (i > 0u)
    {
        j = ((i - 1u) >> 1u);
        if (0 < pHeap->compare((const void*)pNewItem, (const void*)pHeap->item[j]))
        {
            swap(&pHeap->item[i], &pHeap->item[j]);
            i = j;
        }
        else
        {
            break;
        }
    }
    swap(&pHeap->item[i], &pNewItem);
    return TRUE;
}

void* HeapPop(struct Heap* pHeap)
{
    HeapSizeType i = 0u;
    HeapSizeType j;
    if (TRUE == HeapEmpty(pHeap))
    {
        return NULL;
    }
    --pHeap->n;
    /**
     * "(1 << 1u) | 1u" is equal to "i * 2 + 1"
     */
    while ((j = ((i << 1u) | 1u)) < pHeap->n)
    {
        if (j + 1u < pHeap->n && 0 > pHeap->compare((const void*)pHeap->item[j], (const void*)pHeap->item[j + 1u]))
        {
            ++j;
        }
        if (0 > pHeap->compare((const void*)pHeap->item[pHeap->n], (const void*)pHeap->item[j]))
        {
            swap(&pHeap->item[i], &pHeap->item[j]);
            i = j;
        }
        else
        {
            break;
        }
    }
    swap(&(pHeap->item[i]), &(pHeap->item[pHeap->n]));
    return pHeap->item[pHeap->n];
}

