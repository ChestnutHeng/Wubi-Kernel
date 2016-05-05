#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "pq.h"

//  Macros
#define PQ_GET_PARENT_ID(x) ((x) >> 1)
#define PQ_GET_LEFT_ID(x) ((x) << 1)
#define PQ_GET_RIGHT_ID(x) (((x) << 1) + 1)
#define PQ_GET_ITEM_DATA_PTR(pq_ptr,item_ofx) ((pq_ptr)->pool + (item_ofx) * (pq_ptr)->data_sz)

//  Private declare(s).
void PriorityQueueSwapItemData(pq_t *ptr, int item_ofx1, int item_ofx2);

bool PriorityQueueInitialize(pq_t *ptr, \
                             size_t capacity, \
                             size_t item_data_sz, \
                             PQ_COMPARE_CALLBACK_FN cmp_handler) {
	ptr->capacity = capacity;
	ptr->count = 0;
	ptr->data_sz = item_data_sz;
	ptr->pool = (char*)malloc(item_data_sz * capacity);
	ptr->cmp_fn = cmp_handler;
	return(ptr->pool != NULL);
}

void PriorityQueueDestroy(pq_t *ptr) {
	free(ptr->pool);
}

void PriorityQueueHeapify(pq_t *ptr, int root_id) {
	int left_ofx, right_ofx, largest;
	while(root_id < ptr->count) {
		left_ofx = PQ_GET_LEFT_ID(root_id + 1) - 1;
		right_ofx = PQ_GET_RIGHT_ID(root_id + 1) - 1;
		if (left_ofx < ptr->count && \
		    ptr->cmp_fn(PQ_GET_ITEM_DATA_PTR(ptr, left_ofx), \
		                PQ_GET_ITEM_DATA_PTR(ptr, root_id)) < 0) {
			largest = left_ofx;
		} else {
			largest = root_id;
		}
		if (right_ofx < ptr->count && ptr->cmp_fn(PQ_GET_ITEM_DATA_PTR(ptr, right_ofx), \
		                                          PQ_GET_ITEM_DATA_PTR(ptr, largest)) < 0) {
			largest = right_ofx;
		}
		if (largest != root_id) {
			PriorityQueueSwapItemData(ptr, largest, root_id);
			root_id = largest;
		} else {
			break;
		}
	}
}

void PriorityQueuePush(pq_t *ptr, const void *data) {
	int work_id;
	memcpy(PQ_GET_ITEM_DATA_PTR(ptr, ptr->count), data, ptr->data_sz);
	work_id = ptr->count++;
	while (work_id > 0 && \
	       ptr->cmp_fn(PQ_GET_ITEM_DATA_PTR(ptr, PQ_GET_PARENT_ID(work_id + 1) - 1), \
	                   PQ_GET_ITEM_DATA_PTR(ptr, work_id)) > 0) {
		PriorityQueueSwapItemData(ptr, work_id, PQ_GET_PARENT_ID(work_id + 1) - 1);
		work_id = PQ_GET_PARENT_ID(work_id + 1) - 1;
	}
}

void* PriorityQueueGetTop(pq_t *ptr) {
	return(ptr->pool);
}

void PriorityQueuePop(pq_t *ptr, void *dest) {
	memcpy(dest, ptr->pool, ptr->data_sz);
	ptr->count--;
	if (ptr->count != 0) {
		memcpy(ptr->pool, PQ_GET_ITEM_DATA_PTR(ptr, ptr->count), ptr->data_sz);
	}
	PriorityQueueHeapify(ptr, 0);
}

size_t PriorityQueueGetItemCount(pq_t *ptr) {
	return(ptr->count);
}

void PriorityQueueSwapItemData(pq_t *ptr, int item_ofx1, int item_ofx2) {
	char t, *p1, *p2, *e;
	p1 = PQ_GET_ITEM_DATA_PTR(ptr, item_ofx1);
	p2 = PQ_GET_ITEM_DATA_PTR(ptr, item_ofx2);
	e = p1 + ptr->data_sz;
	while(p1 < e) {
		t = *p1;
		*(p1++) = *p2;
		*(p2++) = t;
	}
}

int cmp(const void *p1, const void *p2) {
	return *(const int*)p1 - *(const int*)p2;
}




int main() {
	pq_t xxx;
	int n;
	scanf("%d", &n);
	if (!PriorityQueueInitialize(&xxx, 1000, sizeof(int), cmp)) {
		printf("INIT FAIL\n");
		return 1;
	}
	
	int i;
	for (i = 0; i < n; ++i) {
		int num;
		scanf("%d", &num);
		PriorityQueuePush(&xxx, &num);
	}
	printf("---\n");
	while(PriorityQueueGetItemCount(&xxx) != 0) {
		int num;
		PriorityQueuePop(&xxx, &num);
		printf("%d\n", num);
	}
	
	PriorityQueueDestroy(&xxx);
	return 0;	
}
