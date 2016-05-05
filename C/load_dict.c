#include "load_dict.h"

uint32_t lovely_hash(uint8_t *data, uint32_t size) {
	uint32_t i;
	uint32_t hash = 2333;
	for (i = 0; i < size; ++i) {
		hash = (hash << 5) + hash;
		hash += data[i];
	}
	return hash;
}

uint32_t normal_hash(const void *p){
	return (uint32_t)(((const wubi_word_unit*)p)->key ^ 0xABCDEF0C);
}

uint32_t bi_hash(const void *p){
	return lovely_hash((void*)p, sizeof(uint32_t) * 2);
}

uint32_t string_hash(const void *ptr) {
	char *pt = (char *)ptr;
	uint32_t hash = 2333;
	while(*pt) {
		hash = (hash << 5) + hash;
		hash += *pt;
		pt++;
	}
	return hash;
}

bool wubi_unit_compare(const void *p1,const void *p2){	
	return ((const wubi_word_unit *)p1) -> key == ((const wubi_word_unit *)p2) -> key;
}

bool wubi_bi_compare(const void *p1,const void *p2){
	return ((const bigram_unit *)p1) -> front == ((const bigram_unit *)p2) -> front
			&& ((const bigram_unit *)p1) -> behind == ((const bigram_unit *)p2) -> behind;
}

bool wubi_co_compare(const void *p1,const void *p2){
	return !strcmp(((const code_unit*)p1) -> code,((const code_unit*)p2) -> code);
}

bool load_dicts(ht_hash_t *hs,ht_hash_t *bi_hs, ht_hash_t *co_hs, const char *uni,const char *bi, const char *co){
	//dict uni
	
 	ht_initialize(hs, sizeof(wubi_word_unit), wubi_unit_compare, normal_hash);

 	FILE *unigram_file;

 	unigram_file = fopen("unigram.dict","r");
 	if(unigram_file == NULL){
 		printf("FILE pipe broken!\n");
 		return false;
 	}

 	wubi_word_unit read_unit;
 	while(fscanf(unigram_file,"%d%lf%s",&read_unit.key,&read_unit.unigram,read_unit.data) != EOF){
 		ht_add(hs, &read_unit);
 	}

 	fclose(unigram_file);

 	//dict bi
	
 	ht_initialize(bi_hs, sizeof(bigram_unit), wubi_bi_compare, bi_hash);

 	FILE *bigram_file;

 	bigram_file = fopen("bigram.dict","r");
 	if(bigram_file == NULL){
 		printf("FILE pipe broken!\n");
 		return false;
 	}

 	bigram_unit bi_read_unit;
 	while(fscanf(bigram_file,"%d%d%lf",&bi_read_unit.front,&bi_read_unit.behind,&bi_read_unit.bigram) != EOF){
 		ht_add(bi_hs, &bi_read_unit);
 	}

 	fclose(bigram_file);

 	//dict code 
	
 	ht_initialize(co_hs, sizeof(code_unit), wubi_co_compare, string_hash);

 	FILE *code_file;

 	code_file = fopen("code.dict","r");
 	if(code_file == NULL){
 		printf("FILE pipe broken!\n");
 		return false;
 	}

 	code_unit co_read_unit;
 	while(fscanf(code_file,"%s%d",co_read_unit.code,&co_read_unit.key) != EOF){
 		ht_add(co_hs, &co_read_unit);
 	}

 	fclose(code_file);

}

