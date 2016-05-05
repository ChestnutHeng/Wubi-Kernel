#ifndef __PQ_H__
#define __PQ_H__

#include <stdlib.h>
#include <stdbool.h>

//  Callback function type.
typedef int (*PQ_COMPARE_CALLBACK_FN)(const void *, const void *);

//  ADT(s).
typedef struct {
	size_t capacity, count, data_sz;
	char *pool;
	PQ_COMPARE_CALLBACK_FN cmp_fn;
} pq_t;

//  Public declares.
bool PriorityQueueInitialize(pq_t*, size_t, size_t, PQ_COMPARE_CALLBACK_FN);
void PriorityQueueDestroy(pq_t*);
void PriorityQueueHeapify(pq_t*, int);
void PriorityQueuePush(pq_t*, const void*);
void* PriorityQueueGetTop(pq_t*);
void PriorityQueuePop(pq_t*, void*);
size_t PriorityQueueGetItemCount(pq_t*);

#endif
