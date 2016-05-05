#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

void ht_initialize(ht_hash_t *ht, uint32_t item_size, ht_compare_callback_t comparer, ht_hash_callback_t hasher) {
	memset(ht->buckets, 0, HT_BUCKET_SIZE * sizeof(ht_hash_node_t*));
	ht->comparer = comparer;
	ht->hasher = hasher;
	ht->item_size = item_size;
}

void ht_finalize(ht_hash_t *ht) {
	unsigned int i;
	for (i = 0; i < HT_BUCKET_SIZE; ++i) {
		ht_hash_node_t *p = ht->buckets[i];
		while(p) {
			ht_hash_node_t *next = p->next;
			
			free(p);
			
			p = next;
		}
	}
}

bool ht_add(ht_hash_t *ht, void *data) {
	uint32_t hash = ht->hasher(data);
	
	uint32_t bucket = hash % HT_BUCKET_SIZE;
//	printf("hash.c: Bucket %d\n", (int)bucket);
	ht_hash_node_t *p = ht->buckets[bucket];
	
	while(p) {
		if (p->hash == hash && ht->comparer(data, p->data) == true) {
			//printf("Duplicated!\n");
			return false;
		}
		p = p->next;
	}
	
	
	p = (ht_hash_node_t*)malloc(sizeof(ht_hash_node_t) + ht->item_size);
	if (!p) return false;
	p->data = p + 1;
	p->hash = hash;
	p->next = ht->buckets[bucket];
	ht->buckets[bucket] = p;
	
	
	memcpy(p->data, data, ht->item_size);
}

bool ht_find(ht_hash_t *ht, void *io) {
	uint32_t hash = ht->hasher(io);
	
	uint32_t bucket = hash % HT_BUCKET_SIZE;
	
	ht_hash_node_t *p = ht->buckets[bucket];
	
	while(p) {
		if (p->hash == hash && ht->comparer(io, p->data) == true) {
			memcpy(io, p->data, ht->item_size);
			return true;
		}
		p = p->next;
	}
	
	return false;
}

// typedef struct {
// 	int key;
// 	char word[256];
// } xxx;


// bool xxx_compare(const void *p1, const void *p2) {
// 	return ((const xxx*)p1)->key ==  ((const xxx*)p2)->key;
// }

// uint32_t xxx_hash(const void *p) {
// 	return (uint32_t)(((const xxx*)p)->key);
// }


// int main() {
// 	ht_hash_t hs;
	
// 	ht_initialize(&hs, sizeof(xxx), xxx_compare, xxx_hash);
	
// 	xxx haha;
// 	haha.key = 1;
// 	strcpy(haha.word, "Fuck");
// 	ht_add(&hs, &haha);
	
// 	int i;
// 	for(i = 0; i < 10; ++i) {
// 		int kk;
// 		scanf("%d", &kk);
// 		haha.key = kk;
// 		if (!ht_find(&hs, &haha)) {
// 			printf("NOT FOUND\n");
// 		} else {
// 			printf("%s\n", haha.word);
// 		}
// 	}
	
	
// 	ht_finalize(&hs);
	
	
	
// 	return 0;
// }
