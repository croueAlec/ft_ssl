#include "ft_sha256.h"

static void	add_working_vars_to_original(uint32_t original[8], const uint32_t working_vars[8])
{
	for (size_t i = 0; i < 8; i++)
	{
		original[i] += working_vars[i];
	}
}

static void	set_hash_values(uint32_t working_vars[8], const uint32_t h_values[8])
{
	for (size_t i = 0; i < 8; i++)
	{
		working_vars[i] = h_values[i];
	}
}

void	compression_main_loop(uint32_t working_vars[8], uint32_t *schedule_array)
{
	uint32_t	_[8] = {0};

	uint32_t	S1 = 0;
	uint32_t	ch = 0;
	uint32_t	temp1 = 0;
	uint32_t	S0 = 0;
	uint32_t	maj = 0;
	uint32_t	temp2 = 0;

	for (size_t i = 0; i < 64; i++)
	{
		set_hash_values(_, working_vars);

		S1 = ( (ROTATE_RIGHT(_[E], 6)) ^ (ROTATE_RIGHT(_[E], 11)) ^ (ROTATE_RIGHT(_[E], 25)) );
		ch = ( (_[E] & _[F]) ^ ((~_[E]) & _[G]) );
		temp1 = ( _[H] + S1 + ch + sha256_k_constant[i] + schedule_array[i] );
		S0 = ( (ROTATE_RIGHT(_[A], 2)) ^ (ROTATE_RIGHT(_[A], 13)) ^ (ROTATE_RIGHT(_[A], 22)) );
		maj = ( (_[A] & _[B]) ^ (_[A] & _[C]) ^ (_[B] & _[C]) );
		temp2 = S0 + maj;

		p_print_trace("E\t : %08x\n", _[E]);
		p_print_trace("S1\t : %08x\n", S1);
		p_print_trace("ch\t : %08x\n", ch);
		p_print_trace("temp1\t : %08x\n", temp1);
		p_print_trace("S0\t : %08x\n", S0);
		p_print_trace("maj\t : %08x\n", maj);
		p_print_trace("temp2\t : %08x\n\n", temp2);

		p_print_debug(" Shuffling working vars, round : %zu\n", i);
		working_vars[H] = _[G];
		working_vars[G] = _[F];
		working_vars[F] = _[E];
		working_vars[E] = _[D] + temp1;
		working_vars[D] = _[C];
		working_vars[C] = _[B];
		working_vars[B] = _[A];
		working_vars[A] = temp1 + temp2;

		p_print_debug("w%zu ", i);
		p_print_debug("A\t : %08x\n\n\n", working_vars[A]);
	}
}

void	sha256_update(t_block_sha256 *block)
{
	p_print_info("Updating block\n");
	build_schedule_array(block);

	uint32_t	working_vars[8] = {0};
	p_print_info("Initializing working_vars\n");
	set_hash_values(working_vars, block->h_values);

	p_print_info("Compression main loop :\n");
	compression_main_loop(working_vars, block->schedule_array);

	add_working_vars_to_original(block->h_values, working_vars);
}
