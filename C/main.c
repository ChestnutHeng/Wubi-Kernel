#include "hash.h"
#include "load_dict.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define new(x) (x*)malloc(sizeof(x)) 
#define delete(x) free(x)

int main(int argc, char const *argv[])
{
	ht_hash_t *uni_hash = new(ht_hash_t);
	ht_hash_t *bi_hash = new(ht_hash_t);
	ht_hash_t *co_hs = new(ht_hash_t);

	load_dicts(uni_hash, bi_hash, co_hs, "unigram.dict","bifram.dict", "code.dict");

	char input[256];
	scanf("%s",input);

	ht_finalize(uni_hash);
	ht_finalize(bi_hash);
	ht_finalize(co_hs);

	delete(uni_hash);
	delete(bi_hash);
	delete(co_hs);

	return 0;
}
