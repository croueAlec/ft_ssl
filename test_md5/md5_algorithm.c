#include "ft_md5.h"

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
	return (0x00000000);
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

	tmp.a += apply_core_function(&tmp, round_nbr);		printIF("a:%08x  %08x\t\t<core function\n", tmp.a,  apply_core_function(&tmp, round_nbr));
	tmp.a += message_word;								printIF("a:%08x  %08x\t\t<Mi\n", tmp.a, message_word);
	tmp.a += current_k_constant;						printIF("a:%08x  %08x\t\t<k const\n", tmp.a, current_k_constant);
	tmp.a = ROTATE_LEFT ((tmp.a), rotation_amount);		printIF("a:%08x  %d\t\t\t<Rotation\n", tmp.a, rotation_amount);
	tmp.a += tmp.b;										printIF("a:%08x  %08x\t\t<adding b\n", tmp.a, tmp.b);

	vec->a = tmp.d;
	vec->b = tmp.a;
	vec->c = tmp.b;
	vec->d = tmp.c;
	printIF("new  a:%08x\tb:\033[1;33m%08x\033[0m\tc:%08x\td:%08x\n\n", vec->a, vec->b, vec->c, vec->d);
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
		printIF("Step %zu\n", 1+i+16*(round_nbr));
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

void	add_start_of_step_vectors(context_vectors *vec, context_vectors const *start_of_step_vectors)
{
	printIF("before og a:%08x%08x%08x%08x\n", vec->a, vec->b, vec->c, vec->d);
	printIF("before og a:%08x%08x%08x%08x\n", start_of_step_vectors->a, start_of_step_vectors->b, start_of_step_vectors->c, start_of_step_vectors->d);
	vec->a += start_of_step_vectors->a;
	vec->b += start_of_step_vectors->b;
	vec->c += start_of_step_vectors->c;
	vec->d += start_of_step_vectors->d;
	printIF("after og a:%08x%08x%08x%08x\n", vec->a, vec->b, vec->c, vec->d);
}


// int	main(void)
int	md5(t_block *list)
{
	context_vectors	vec = init_vectors();

	uint32_t		little_endian_message[16];

	while (list)
	{
		context_vectors	start_of_step_vectors = {0};
		memcpy(&start_of_step_vectors, &vec, sizeof(context_vectors));

		big_to_little_endian(little_endian_message, list->chunk);
		// memcpy(little_endian_message, list->chunk, sizeof(uint32_t)*16);
		(void)empty_example_block;

		rounds(little_endian_message, &vec, ROUND1);
		rounds(little_endian_message, &vec, ROUND2);
		rounds(little_endian_message, &vec, ROUND3);
		rounds(little_endian_message, &vec, ROUND4);

		add_start_of_step_vectors(&vec, &start_of_step_vectors);
		list = list->next;
	}

	little_to_big_endian(&vec);

	print_vector(&vec);

	return 0;
}
