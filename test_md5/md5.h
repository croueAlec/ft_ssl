#ifndef MD5_H
# define MD5_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hashing.h"

#define CHUNK_SIZE 64
#define PADDED_CHUNK_SIZE 56
#define SEPARATOR 0b10000000

typedef struct	block_512_bits
{
	char	chunk[CHUNK_SIZE];
	char	_pad;
	struct block_512_bits	*next;
}	t_block;

#endif
