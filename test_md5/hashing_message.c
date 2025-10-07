#include <stdio.h>
#include <stdint.h>

/*
	This constant is documented in the MD5 rfc1321 as magic values.
*/
const uint32_t k_constant[4][16] = {
	{ 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821	},

	{ 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453, 0xd8a1e681, 0xe7d3fbc8,
	  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a	},

	{ 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665		},

	{ 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391	}
};

#define INIT_VECTOR_A 0x01234567
#define INIT_VECTOR_B 0x89abcdef
#define INIT_VECTOR_C 0xfedcba98
#define INIT_VECTOR_D 0x76543210

/*
	input_order_array specifies the order in which each word in the block is input.
	This order is documented in the MD5 rfc1321 as x[0..15].
*/
const short input_order_array[4][16] = {
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
	{ 1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12 },
	{ 5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2 },
	{ 0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9 }
};

/*
	shift_array specifies the per-round shift amounts.
	This is documented in the MD5 rfc1321 as S1 to S4.
*/
const short shift_array[4][16] = {
	{ 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22 },
	{ 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20 },
	{ 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23 },
	{ 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 }
};

typedef struct	initialization_vectors
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				init_vectors;

typedef enum	e_round_number
{
	ROUND1 = 0,
	ROUND2 = 1,
	ROUND3 = 2,
	ROUND4 = 3
}				t_round_nbr;

#define F(b, c, d) (((b) & (c)) | ((~b) & (d)))
#define G(b, c, d) (((b) & (d)) | ((c) & (~d)))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) ((c) ^ ((b) | (~d)))
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

init_vectors	set_default_vectors(void)
{
	init_vectors	vectors;

	vectors.a = INIT_VECTOR_A;
	vectors.b = INIT_VECTOR_B;
	vectors.c = INIT_VECTOR_C;
	vectors.d = INIT_VECTOR_D;

	return (vectors);
}

/**
 * @brief This function implements the green square in [Figure 2] of the README
 *
 * @param vec current state of the md5 vectors
 * @param round_nbr specifies which function depending on round number
 * @return * uint32_t value added to A
 */
uint32_t	apply_core_function(init_vectors const *vec, t_round_nbr round_nbr)
{
	switch (round_nbr)
	{
	case ROUND1:
		return (F(vec->b, vec->c, vec->d));

	case ROUND2:
		return (G(vec->b, vec->c, vec->d));

	case ROUND3:
		return (H(vec->b, vec->c, vec->d));

	case ROUND4:
		return (I(vec->b, vec->c, vec->d));
	}
}

/**
 * @brief returns the input order depending on round number and current index
 */
short	input_order(t_round_nbr round_nbr, size_t i)
{
	return (input_order_array[round_nbr][i]);
}

// FF(a, b, c, d, Mi, s, Ki) {
// 	(a) += F ((b), (c), (d)) + (Mi) + (UINT4)(Ki);
// 	(a) = ROTATE_LEFT ((a), (s));
// 	(a) += (b);
// }

/**
 * @brief This is function implements the steps of [Figure 2] of the README.
 *
 * @param vec current state of the md5 vectors
 * @param round_nbr specifies which function to apply in F
 * @param message_word 32bit word from message corresponds to Mi
 * @param current_k_constant corresponds to Ki
 * @param rotation_amount corresponds to <<<s
 */
void	operation(
	init_vectors *vec, t_round_nbr round_nbr,
	uint32_t message_word,
	uint32_t current_k_constant,
	short rotation_amount )
{
	init_vectors	tmp = *vec;

	tmp.a += apply_core_function(&tmp, round_nbr);
	tmp.a += message_word;
	tmp.a += current_k_constant;
	tmp.a = ROTATE_LEFT ((tmp.a), rotation_amount);
	tmp.a += tmp.b;

	vec->a = tmp.d;
	vec->b = tmp.a;
	vec->c = tmp.b;
	vec->d = tmp.c;
}

/**
 * @brief This function implements the main md5 loop as seen in [Figure 1] of the README
 *
 * @param message current block split in 16 uint32_t blocks
 * @param vec current state of the md5 vectors
 * @param round_nbr current round number
 */
void	rounds(uint32_t const message[16], init_vectors *vec, t_round_nbr round_nbr)
{
	for (size_t i = 0; i < 16; i++)
	{
		printf("%zu\n", i);
		operation(
			vec, round_nbr,
			message[input_order(round_nbr, i)],
			k_constant[round_nbr][i],
			shift_array[round_nbr][i]);
	}

}

void	print_vector(init_vectors const *vec)
{
	printf("%x%x%x%x\n", vec->a, vec->b, vec->c, vec->d);
}

#include "hashing.h"

int	main(void)
{
	init_vectors	vec = set_default_vectors();

	// printf("%d\n%d\n",vec.a, F(vec.b, vec.c, vec.d));

	rounds(empty_example_block, &vec, ROUND1);
	rounds(empty_example_block, &vec, ROUND2);
	rounds(empty_example_block, &vec, ROUND3);
	rounds(empty_example_block, &vec, ROUND4);

	print_vector(&vec);

	return 0;
}
