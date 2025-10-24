#ifndef FT_MD5_H
# define FT_MD5_H

#include "ft_ssl.h"

#include "ft_md5_algorithm.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#define CHUNK_SIZE 64
#define PADDED_CHUNK_SIZE 56
#define SEPARATOR 0b10000000

#define RED "\033[0;91m"
#define BYELLOW "\033[1;33m"
#define CLEAR "\033[0;m"

typedef struct	hashes t_hash;

typedef struct	block_512_bits
{
	uint8_t			chunk[CHUNK_SIZE + 1];
	size_t			total_length;
	size_t			buffer_length;
	int				input_fd;
	char			*input_string;
	size_t			block_number;

	context_vectors	vectors;

}	t_block;

/* 		Block Utils		 */

void		print_md5_block_chunk(const t_block *block, size_t separator_index);

/* 		Main MD5 Algorithm */

void		md5_update(t_block *block);
void		md5_loop(t_block *block);
void		md5(t_hash *node);

#endif
