#include "test_sha256.h"

static void	init_hash_values(uint32_t h_values[8])
{
	h_values[0] = 0x6a09e667;
	h_values[1] = 0xbb67ae85;
	h_values[2] = 0x3c6ef372;
	h_values[3] = 0xa54ff53a;
	h_values[4] = 0x510e527f;
	h_values[5] = 0x9b05688c;
	h_values[6] = 0x1f83d9ab;
	h_values[7] = 0x5be0cd19;
}

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
	p_print_debug("Initializing tmp hash_values\n");

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

		p_print_debug("E\t : %08x\n", _[E]);
		p_print_debug("S1\t : %08x\n", S1);
		p_print_debug("ch\t : %08x\n", ch);
		p_print_debug("temp1\t : %08x\n", temp1);
		p_print_debug("S0\t : %08x\n", S0);
		p_print_debug("maj\t : %08x\n", maj);
		p_print_debug("temp2\t : %08x\n\n", temp2);

		// p_print_debug(" Shuffling working vars, round : %zu\n", i);
		// uint32_t	tmp_H = working_vars[H];
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
		// p_print_debug("B\t : %08x\n", working_vars[B]);
		// p_print_debug("C\t : %08x\n", working_vars[C]);
		// p_print_debug("D\t : %08x\n", working_vars[D]);
		// p_print_debug("E\t : %08x\n", working_vars[E]);
		// p_print_debug("F\t : %08x\n", working_vars[F]);
		// p_print_debug("G\t : %08x\n", working_vars[G]);
		// p_print_debug("H\t : %08x\n\n", working_vars[H]);
	}
}

void	sha256_update(t_block_sha256 *block)
{
	init_hash_values(block->h_values);

	p_print_debug("Updating block\n");
	build_schedule_array(block);

	uint32_t	working_vars[8] = {0};
	p_print_debug("Initializing working_vars\n");
	set_hash_values(working_vars, block->h_values);

	p_print_debug("Compression main loop :\n");
	compression_main_loop(working_vars, block->schedule_array);

	add_working_vars_to_original(block->h_values, working_vars);

	for (size_t i = 0; i < 8; i++)
	{
		p_print_debug("%08x", block->h_values[i]);
	}
}
