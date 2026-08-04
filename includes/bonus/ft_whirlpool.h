#ifndef FT_WHIRLPOOL_H
#define FT_WHIRLPOOL_H

#include "ft_ssl.h"

#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 64
#endif

#define whirlpool_CHUNK_SIZE 64
#define whirlpool_PADDED_CHUNK_SIZE 32
#define whirlpool_SEPARATOR 0b10000000

#define RED "\033[0;91m"
#define BYELLOW "\033[1;33m"
#define CLEAR "\033[0;m"

#define MATRIX_SIZE 8

typedef uint8_t whirlpool_matrix[MATRIX_SIZE][MATRIX_SIZE];

typedef struct hashes t_hash;

typedef struct block_512_bits_whirlpool
{
	uint8_t chunk[whirlpool_CHUNK_SIZE + 1];
	size_t	total_length;
	size_t	buffer_length;
	int		input_fd;
	char   *input_string;
	size_t	block_number;

	whirlpool_matrix H;
	whirlpool_matrix result;

} t_block_whirlpool;

/* 		Main Whirlpool Algorithm */

void whirlpool_loop(t_block_whirlpool *block);
void whirlpool(t_hash *node);

#endif
