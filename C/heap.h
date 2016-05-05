/***************************
 *
 * Binary Max Heap
 *
 * Author: FallingFlowers
 *
 * Sep. 6th, 2010 
 *
 **************************/
#ifndef HEAP
#define HEAP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t HeapSizeType;

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

struct Heap
{
    void** item;
    HeapSizeType n;
    HeapSizeType nmax;
    int32_t (*compare)(const void*, const void*);
};

int32_t HeapInit(struct Heap* pHeap, HeapSizeType n, int32_t (*cmp)(const void*, const void*));

int32_t HeapFree(struct Heap* pHeap);

HeapSizeType HeapCapacity(struct Heap* pHeap);

void HeapResize(struct Heap* pHeap, const HeapSizeType sz);

void HeapClear(struct Heap* pHeap);

int32_t HeapFull(struct Heap* pHeap);

int32_t HeapEmpty(struct Heap* pHeap);

void* HeapTop(struct Heap* pHeap);

HeapSizeType HeapSize(struct Heap* pHeap);

int32_t HeapPush(struct Heap* pHeap, void* pNewItem);

void* HeapPop(struct Heap* pHeap);

#endif

