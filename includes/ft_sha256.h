#ifndef FT_SHA256_H
# define FT_SHA256_H

#include <stdint.h>

#include "ft_ssl.h"

#include "../libs/penelope/penelope.h"
#include "../libs/libft/libft.h"

#ifndef LOG_LEVEL
# define LOG_LEVEL P_LOG_DEFAULT
#endif

#define sha256_CHUNK_SIZE 64
#define sha256_PADDED_CHUNK_SIZE 56
#define sha256_SEPARATOR 0b10000000

#define sha256_SCHEDULE_SIZE 64
#define sha256_DIGEST_SIZE 64

#define UNDEFINED_FD -2

#define ROTATE_RIGHT(x, n) (((uint32_t)(x) >> (n)) | ((uint32_t)(x) << (32 - (n))))

typedef struct	hashes t_hash;

extern const uint32_t	sha256_k_constant[64];

typedef uint32_t	hash_values[8];
typedef enum	e_hash_values_index
{
	A = 0,
	B = 1,
	C = 2,
	D = 3,
	E = 4,
	F = 5,
	G = 6,
	H = 7
}				t_hash_values_index;

typedef struct	block_512_bits_sha256
{
	uint8_t			chunk[sha256_CHUNK_SIZE + 1];
	uint32_t		schedule_array[sha256_SCHEDULE_SIZE + 1];
	size_t			total_length;
	size_t			buffer_length;
	int				input_fd;
	char			*input_string;

	hash_values		h_values;
}	t_block_sha256;

/* 			Utils			 */

uint32_t	uint8_to_uint32_big_endian(const uint8_t *buf);
void		print_sha256_block_chunk(const t_block_sha256 *block, size_t separator_index);

/* 			Schedule Array	 */

void		build_schedule_array(t_block_sha256 *block);

/* 			sha256			 */

void		sha256_loop(t_block_sha256 *block);
void		sha256_update(t_block_sha256 *block);
void		sha256(t_hash *node);

#endif
