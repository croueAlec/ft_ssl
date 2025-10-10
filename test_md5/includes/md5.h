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
	uint8_t	chunk[CHUNK_SIZE];
	uint8_t	_pad;
	struct block_512_bits	*next;
}	t_block;

/* 		Utils		 */
void		printIF(const char *format, ...);
void		print_bits(uint8_t ch);
uint32_t	print_hex(uint8_t *buf);
void		print_msg_blocks(t_block *blocks);
int			err(char *err_msg);
void		free_blocks(t_block *blocks);

#endif
