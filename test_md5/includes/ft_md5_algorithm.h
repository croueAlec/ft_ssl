#ifndef FT_MD5_ALGORITHM_H
# define FT_MD5_ALGORITHM_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../libs/penelope/penelope.h"

#define INIT_VECTOR_A 0x67452301
#define INIT_VECTOR_B 0xefcdab89
#define INIT_VECTOR_C 0x98badcfe
#define INIT_VECTOR_D 0x10325476

#define F(b, c, d) (((b) & (c)) | ((~b) & (d)))
#define G(b, c, d) (((b) & (d)) | ((c) & (~d)))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) ((c) ^ ((b) | (~d)))

#define ROTATE_LEFT(x, n) (((uint32_t)(x) << (n)) | ((uint32_t)(x) >> (32 - (n))))

#define L_TO_BIG_ENDIAN(x) (((x & 0x000000FF) << 24) | ((x & 0x0000FF00) << 8) | ((x & 0x00FF0000) >> 8) | ((x & 0xFF000000) >> 24))

typedef struct	md5_context_vectors
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				context_vectors;

typedef enum	e_round_number
{
	ROUND1 = 0,
	ROUND2 = 1,
	ROUND3 = 2,
	ROUND4 = 3
}				t_round_nbr;

typedef struct	block_512_bits t_block;

extern const uint32_t	k_constant[4][16];
extern const short		input_order_array[4][16];
extern const short		shift_array[4][16];
extern const uint32_t	empty_example_block[16];

/* 		Algorithm Utils		 */
context_vectors	init_vectors(void);
short			input_order(t_round_nbr round_nbr, size_t i);
void			print_vector(context_vectors const *vec, char const *message, bool verbose, t_penelope_log_level log_level);
void			big_to_little_endian(uint32_t *dest, uint8_t const *src);
void			little_to_big_endian(context_vectors *vec);

#endif
