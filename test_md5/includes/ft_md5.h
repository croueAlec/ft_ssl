#ifndef MD5_H
# define MD5_H

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "ft_md5_algorithm.h"
#include "../../libs/penelope/penelope.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#define CHUNK_SIZE 64
#define PADDED_CHUNK_SIZE 56
#define SEPARATOR 0b10000000
#define	UNDEFINED_FD -2

#ifndef LOG_LEVEL
# define LOG_LEVEL P_LOG_DEFAULT
#endif

typedef struct	block_512_bits
{
	uint8_t	chunk[CHUNK_SIZE + 1];
	size_t	total_length;
	size_t	buffer_length;
	int		input_fd;
	char	*input_string;

}	t_block;

/* 		Block Utils		 */

void		print_block_chunk(t_block *block, size_t separator_index);
int			err(char *err_msg);
void		free_blocks(t_block *block);
t_block		init_block(char *argv);

/* 		Main MD5 Algorithm */

void		md5_update(t_block *block);
void		md5(char *str);

#endif
