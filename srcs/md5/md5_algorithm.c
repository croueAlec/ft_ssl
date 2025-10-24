#include "ft_md5.h"
#include "ft_md5_algorithm.h"
#include <string.h>

/**
 * @brief This function implements the green square in [Figure 2] of the README
 *
 * @param vec current state of the md5 vectors
 * @param round_nbr specifies which function depending on round number
 * @return * uint32_t value added to A
 */
static uint32_t	apply_core_function(const context_vectors *vec, t_round_nbr round_nbr)
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
 * @brief This is function implements the steps of [Figure 2] of the README.
 *
 * @param vec current state of the md5 vectors
 * @param round_nbr specifies which function to apply in F
 * @param message_word 32bit word from message corresponds to Mi
 * @param current_k_constant corresponds to Ki
 * @param rotation_amount corresponds to <<<s
 */
static void	operation(
	context_vectors *vec, t_round_nbr round_nbr,
	uint32_t message_word,
	uint32_t current_k_constant,
	short rotation_amount )
{
	context_vectors	tmp = *vec;
	p_print_trace("\ta:%s%08x\n%s", BYELLOW, tmp.a, CLEAR);

	tmp.a += apply_core_function(&tmp, round_nbr);		p_print_trace("\ta:%08x  %08x\t\t<core function\n", tmp.a,  apply_core_function(&tmp, round_nbr));
	tmp.a += message_word;								p_print_trace("\ta:%08x  %08x\t\t<Mi\n", tmp.a, message_word);
	tmp.a += current_k_constant;						p_print_trace("\ta:%08x  %08x\t\t<k const\n", tmp.a, current_k_constant);
	tmp.a = ROTATE_LEFT ((tmp.a), rotation_amount);		p_print_trace("\ta:%08x  %d\t\t\t<Rotation\n", tmp.a, rotation_amount);
	tmp.a += tmp.b;										p_print_trace("\ta:%s%08x%s  %08x\t\t<adding b\n", RED, tmp.a, CLEAR, tmp.b);

	vec->a = tmp.d;
	vec->b = tmp.a;
	vec->c = tmp.b;
	vec->d = tmp.c;
	p_print_debug("   End of step vectors a:%s%08x%s\tb:%s%08x%s\tc:%08x\td:%08x\n\n", BYELLOW,vec->a,CLEAR, RED, vec->b, CLEAR, vec->c, vec->d);
}

/**
 * @brief This function implements the main md5 loop as seen in the blue step of [Figure 1] in the README
 *
 * @param message current block split in 16 uint32_t blocks
 * @param vec current state of the md5 vectors
 * @param round_nbr current round number
 */
static void	rounds(const uint32_t message[16], context_vectors *vec, t_round_nbr round_nbr)
{
	p_print_debug("[Round %zu] beginning vectors :", round_nbr + 1);
	print_vector(vec, "", true, P_LOG_DEBUG);
	for (size_t i = 0; i < 16; i++)
	{
		p_print_debug(" [Round : %zu | Step : %zu]\n", round_nbr + 1, i + 1);
		operation(
			vec, round_nbr,
			message[input_order(round_nbr, i)],
			md5_k_constant[round_nbr][i],
			md5_shift_array[round_nbr][i]);
	}
	p_print_debug(" [Round %zu] end vectors :", round_nbr + 1);
	print_vector(vec, "", true, P_LOG_DEBUG);
}

static void	add_start_of_step_vectors(context_vectors *vec, const context_vectors *start_of_step_vectors)
{
	print_vector(start_of_step_vectors, "Start of step vectors :\n", true, P_LOG_DEBUG);
	print_vector(vec, "Current vectors :\n", true, P_LOG_DEBUG);
	vec->a += start_of_step_vectors->a;
	vec->b += start_of_step_vectors->b;
	vec->c += start_of_step_vectors->c;
	vec->d += start_of_step_vectors->d;
	print_vector(vec, "New state of vectors after adding start of step vectors :\n", true, P_LOG_DEBUG);
}

/**
 * @brief The main MD5 algorithm as shown in [Figure 1]
 */
void	md5_update(t_block *block)
{
	p_print_debug("[Block %zu]\n", block->block_number);
	context_vectors	vec = init_vectors(block);

	uint32_t		little_endian_message[16];

	context_vectors	start_of_step_vectors = {0};
	memcpy(&start_of_step_vectors, &vec, sizeof(context_vectors));

	big_to_little_endian(little_endian_message, block->chunk);

	rounds(little_endian_message, &vec, ROUND1);
	rounds(little_endian_message, &vec, ROUND2);
	rounds(little_endian_message, &vec, ROUND3);
	rounds(little_endian_message, &vec, ROUND4);

	add_start_of_step_vectors(&vec, &start_of_step_vectors);

	
	memcpy(&block->vectors, &vec, sizeof(context_vectors));
	little_to_big_endian(&vec);

	print_vector(&vec, "", false, P_LOG_DEBUG);
}

// block64 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789--"
