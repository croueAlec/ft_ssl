#include "test_sha256.h"

static uint32_t	xor_rotate(uint32_t value, bool sX)
{
	int	rotate_index[3] = { 7 , 18 , 3 };

	p_print_usr_output1("\tDefault value :\n\t\t");
	p_print_bits_uint32(P_LOG_USR_OUTPUT1, value, false, "", false);
	if (sX == 1)
		rotate_index[0] = 17, rotate_index[0] = 19, rotate_index[0] = 10;

	uint32_t	value_rotated_0 = ROTATE_RIGHT(value, rotate_index[0]);
	uint32_t	value_rotated_1 = ROTATE_RIGHT(value, rotate_index[1]);
	uint32_t	value_rotated_2 = ROTATE_RIGHT(value, rotate_index[2]);

	uint32_t	return_value =	value_rotated_0 ^
								value_rotated_1 ^
								value_rotated_2;

	p_print_usr_output1("\tXor of the rotated values :\n\t\t");
	p_print_bits_uint32(P_LOG_USR_OUTPUT1, return_value, false, "", false);
}

static void	extend_schedule_array(t_block_sha256 *block)
{
	uint32_t	*schedule_array = block->schedule_array;
	uint8_t		*chunk = block->chunk;

	for (size_t i = 16; i < 64; i++)
	{
		uint32_t w0 = schedule_array[i - 16];
		uint32_t s0 = xor_rotate(schedule_array[i - 15], 0);
		uint32_t w9 = schedule_array[i - 2];
		uint32_t s1 = xor_rotate(schedule_array[i - 15], 1);

		schedule_array[i] = w0 + s0 + w9 + s1;
		p_print_debug("\tAddition result : \t");
		p_print_bits_uint32(P_LOG_DEBUG, schedule_array[i], false, "", false);
	}
	
}

static void	build_schedule_array(t_block_sha256 *block)
{
	uint32_t	*schedule_array = block->schedule_array;
	uint8_t		*chunk = block->chunk;

	p_print_debug(" First quarter of schedule_array\n");
	for (size_t j = 0; j < 16; j++)
	{
		schedule_array[j] = uint8_to_uint32_big_endian(&chunk[j * 4]);
		p_print_trace("\titeration number %zu :\t 0x%08x\n", j, schedule_array[j]);
	}

	extend_schedule_array(block);
}

void	sha256_update(t_block_sha256 *block)
{
	p_print_debug("Updating block\n");
	build_schedule_array(block);
}
