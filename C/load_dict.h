#ifndef LOAD_DICT_H
#define LOAD_DICT_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

typedef struct{
	uint32_t key;
	double unigram;
	char data[256];
}wubi_word_unit;

typedef struct
{
	uint32_t front;
	uint32_t behind;
	double bigram;
}bigram_unit;

typedef struct
{
	char code[24];
	uint32_t key;
}code_unit;

uint32_t lovely_hash(uint8_t *data, uint32_t size);



#endif
