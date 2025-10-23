#ifndef TEST_SHA256_H
# define TEST_SHA256_H

#include <stdint.h>

#include "../../libs/penelope/penelope.h"
#include "../../libs/libft/libft.h"

#ifndef LOG_LEVEL
# define LOG_LEVEL P_LOG_DEFAULT
#endif

#define sha256_CHUNK_SIZE 64
#define sha256_PADDED_CHUNK_SIZE 56
#define sha256_SEPARATOR 0b10000000

#define sha256_SCHEDULE_SIZE 64

#define UNDEFINED_FD -2

typedef struct	sha256_hash_values
{
	uint32_t	h0;
	uint32_t	h1;
	uint32_t	h2;
	uint32_t	h3;
	uint32_t	h4;
	uint32_t	h5;
	uint32_t	h6;
	uint32_t	h7;
}				hash_values;


typedef struct	block_512_bits_sha256
{
	uint8_t			chunk[sha256_CHUNK_SIZE + 1];
	uint32_t		schedule_array[sha256_SCHEDULE_SIZE + 1];
	size_t			total_length;
	size_t			buffer_length;
	// int				input_fd;
	char			*input_string;
	// size_t			block_number;
	
	hash_values		h_values;
	
}	t_block_sha256;

uint32_t	uint8_to_uint32_big_endian(const uint8_t *buf);
void		print_block_chunk(const t_block_sha256 *block, size_t separator_index);
void		sha256_loop(t_block_sha256 *block);
void		sha256_update(t_block_sha256 *block);

#endif
