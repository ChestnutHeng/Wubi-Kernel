#ifndef HASH_H_
#define HASH_H_

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define HT_BUCKET_SIZE 81920

typedef bool (*ht_compare_callback_t)(const void *p1, const void *p2);
typedef uint32_t (*ht_hash_callback_t)(const void *p);

typedef struct _ht_hash_node_t {
	struct _ht_hash_node_t *next;
	uint32_t hash;
	void *data;
} ht_hash_node_t;

typedef struct {
	ht_compare_callback_t comparer;
	ht_hash_callback_t hasher;
	
	uint32_t item_size;
	
	ht_hash_node_t *buckets[HT_BUCKET_SIZE];
} ht_hash_t;

void ht_initialize(ht_hash_t *ht, uint32_t item_size, ht_compare_callback_t comparer, ht_hash_callback_t hasher);

void ht_finalize(ht_hash_t *ht);

bool ht_add(ht_hash_t *ht, void *data);

bool ht_find(ht_hash_t *ht, void *io);


#endif
