#include "md5.h"

context_vectors	init_vectors(void)
{
	context_vectors	vectors;

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
uint32_t	apply_core_function(context_vectors const *vec, t_round_nbr round_nbr)
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
	context_vectors *vec, t_round_nbr round_nbr,
	uint32_t message_word,
	uint32_t current_k_constant,
	short rotation_amount )
{
	context_vectors	tmp = *vec;

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

void	print_vector(context_vectors const *vec)
{
	printf("%08x%08x%08x%08x\n", vec->a, vec->b, vec->c, vec->d);
}

/**
 * @brief This function implements the main md5 loop as seen in [Figure 1] of the README
 *
 * @param message current block split in 16 uint32_t blocks
 * @param vec current state of the md5 vectors
 * @param round_nbr current round number
 */
void	rounds(uint32_t const message[16], context_vectors *vec, t_round_nbr round_nbr)
{
	for (size_t i = 0; i < 16; i++)
	{
		operation(
			vec, round_nbr,
			message[input_order(round_nbr, i)],
			k_constant[round_nbr][i],
			shift_array[round_nbr][i]);
	}
}

/**
 * @brief Converts src to little endian in dest using a buffer.
 * @param buf="ABCD";
 * @param tmp=buf[0];		tmp=="   A";
 * @param tmp+=buf[1]<<8;	tmp=="  BA";
 * @param tmp+=buf[2]<<16;	tmp==" CBA";
 * @param tmp+=buf[3]<<24;	tmp=="DCBA";
 * @note We do this every 4 byte word
 */
void	big_to_little_endian(uint32_t *dest, char const *src)
{
	uint32_t	tmp = 0;
	uint8_t		buffer[64] = {0};
	memcpy(buffer, src, sizeof(char) * 64);

	for (int i = 0; i < 16; i++) {
		tmp =
			((uint32_t)buffer[i * 4])       |
			((uint32_t)buffer[i * 4 + 1] << 8)  |
			((uint32_t)buffer[i * 4 + 2] << 16) |
			((uint32_t)buffer[i * 4 + 3] << 24);
		dest[i] = tmp;
	}
}

void	little_to_big_endian(context_vectors *vec)
{
	vec->a = L_TO_BIG_ENDIAN(vec->a);
	vec->b = L_TO_BIG_ENDIAN(vec->b);
	vec->c = L_TO_BIG_ENDIAN(vec->c);
	vec->d = L_TO_BIG_ENDIAN(vec->d);
}

void	add_original_vectors(context_vectors *vec)
{
	vec->a += INIT_VECTOR_A;
	vec->b += INIT_VECTOR_B;
	vec->c += INIT_VECTOR_C;
	vec->d += INIT_VECTOR_D;
}


// int	main(void)
int	md5(t_block *list)
{
	context_vectors	vec = init_vectors();

	uint32_t		little_endian_message[16];

	big_to_little_endian(little_endian_message, list->chunk);
	(void)empty_example_block;

	rounds(little_endian_message, &vec, ROUND1);
	rounds(little_endian_message, &vec, ROUND2);
	rounds(little_endian_message, &vec, ROUND3);
	rounds(little_endian_message, &vec, ROUND4);

	add_original_vectors(&vec);

	little_to_big_endian(&vec);

	print_vector(&vec);

	return 0;
}
