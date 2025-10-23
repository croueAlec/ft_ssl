#include "test_sha256.h"

static void	build_schedule_array(t_block_sha256 *block)
{
	uint32_t	*schedule_array = block->schedule_array;
	uint8_t		*chunk = block->chunk;

	for (size_t i = 0; i < 4; i++)
	{
		p_print_debug(" Filling part number : %zu\n", i);
		for (size_t j = 0; j < 16; j++)
		{
			schedule_array[j * (i+1)] = uint8_to_uint32_big_endian(&chunk[j * 4]);
			p_print_trace("\titeration number %zu :\t %08x\n", j, schedule_array[j * (i+1)]);
		}
	}
	
}

void	sha256_update(t_block_sha256 *block)
{
	p_print_debug("Updating block\n");
	build_schedule_array(block);
}
