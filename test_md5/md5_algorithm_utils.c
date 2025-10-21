#include "ft_md5.h"
#include "ft_md5_algorithm.h"
#include <string.h>

context_vectors	init_vectors(t_block *block)
{
	context_vectors	vectors;

	vectors.a = INIT_VECTOR_A;
	vectors.b = INIT_VECTOR_B;
	vectors.c = INIT_VECTOR_C;
	vectors.d = INIT_VECTOR_D;

	if (block->block_number == 1)
		return (vectors);
	else
		return (block->vectors);
}

/**
 * @brief returns the input order depending on round number and current index
 */
short	input_order(t_round_nbr round_nbr, size_t i)
{
	return (input_order_array[round_nbr][i]);
}

void	print_vector(context_vectors const *vec, char const *message, bool verbose, t_penelope_log_level log_level)
{
	if (!level_verification(log_level))
		return ;

	if (verbose == true)
		p_print_level(log_level, "%s a:%08x b:%08x c:%08x d:%08x\n\n", message, vec->a, vec->b, vec->c, vec->d);
	else
		p_print_level(log_level, "%08x%08x%08x%08x\n\n", vec->a, vec->b, vec->c, vec->d);
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
void	big_to_little_endian(uint32_t *dest, uint8_t const *src)
{
	uint32_t	tmp = 0;
	uint8_t		buffer[64] = {0};
	memcpy(buffer, src, sizeof(uint8_t) * 64);

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
