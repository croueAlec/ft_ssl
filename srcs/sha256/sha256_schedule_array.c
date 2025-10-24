#include "ft_sha256.h"

static void	print_xor_rotate(t_penelope_log_level log_level, uint32_t value, uint32_t value_rotated_0, uint32_t value_rotated_1, uint32_t value_shifted, uint32_t return_value, int rotate_index[3])
{
	if (!level_verification(log_level))
		return ;

	p_print_trace("\tDefault value :\n\t\t");
	p_print_bits_uint32(P_LOG_TRACE, value, false, "", false);

	p_print_trace("shift values %zu; %zu; %zu;\n", rotate_index[0], rotate_index[1], rotate_index[2]);
	p_print_bits_uint32(P_LOG_TRACE, value_rotated_0, false, "", false);
	p_print_bits_uint32(P_LOG_TRACE, value_rotated_1, false, "", false);
	p_print_bits_uint32(P_LOG_TRACE, value_shifted, false, "", false);
	
	p_print_trace("\t Xor of the rotated values :\n\t\t");
	p_print_bits_uint32(P_LOG_TRACE, return_value, false, "", false);
}

static void	print_extend_schedule_array(uint32_t w0, uint32_t s0, uint32_t w9, uint32_t s1, uint32_t i, uint32_t schedule_i)
{
	p_print_trace("\tAdding :\n");
	p_print_bits_uint32(P_LOG_TRACE, w0, false, "", false);
	p_print_bits_uint32(P_LOG_TRACE, s0, false, "", false);
	p_print_bits_uint32(P_LOG_TRACE, w9, false, "", false);
	p_print_bits_uint32(P_LOG_TRACE, s1, false, "", false);

	p_print_debug("w%zu ", i);
	p_print_bits_uint32(P_LOG_DEBUG, schedule_i, false, "", false);
}

static uint32_t	xor_rotate(uint32_t value, bool sX)
{
	int	rotate_index[3] = { 7 , 18 , 3 };

	if (sX == 1)
		rotate_index[0] = 17, rotate_index[1] = 19, rotate_index[2] = 10;

	uint32_t	value_rotated_0 = ROTATE_RIGHT(value, rotate_index[0]);
	uint32_t	value_rotated_1 = ROTATE_RIGHT(value, rotate_index[1]);
	uint32_t	value_shifted = (value >> rotate_index[2]);

	uint32_t	return_value =	value_rotated_0 ^
								value_rotated_1 ^
								value_shifted;

	print_xor_rotate(P_LOG_TRACE, value, value_rotated_0, value_rotated_1, value_shifted, return_value, rotate_index);

	return (return_value);
}

static void	extend_schedule_array(t_block_sha256 *block)
{
	uint32_t	*schedule_array = block->schedule_array;
	// uint8_t		*chunk = block->chunk;

	for (size_t i = 16; i < 64; i++)
	{
		if (i % 16 == 0)
			p_print_debug(" schedule_array part %zu\n", (i / 16) + 1);
		p_print_trace("  Iteration nb %zu\n", i);
		uint32_t w0 = schedule_array[i - 16];
		uint32_t s0 = xor_rotate(schedule_array[i - 15], 0);
		uint32_t w9 = schedule_array[i - 7];
		uint32_t s1 = xor_rotate(schedule_array[i - 2], 1);

		schedule_array[i] = w0 + s0 + w9 + s1;
		print_extend_schedule_array(w0, s0, w9, s1, i, schedule_array[i]);
	}
}

void	build_schedule_array(t_block_sha256 *block)
{
	uint32_t	*schedule_array = block->schedule_array;
	uint8_t		*chunk = block->chunk;

	p_print_debug(" schedule_array part 1\n");
	for (size_t j = 0; j < 16; j++)
	{
		schedule_array[j] = uint8_to_uint32_big_endian(&chunk[j * 4]);
		p_print_debug("w%zu ", j);
		p_print_bits_uint32(P_LOG_DEBUG, schedule_array[j], false, "", false);
	}

	extend_schedule_array(block);
}
