#include "ft_md5.h"
#include <string.h>
#include <stdlib.h>

static void	print_chunk_uint8_t(uint8_t ch)
{
	p_print_trace("%d%d%d%d%d%d%d%d",
		(ch >> 7) & 1, (ch >> 6) & 1, (ch >> 5) & 1, (ch >> 4) & 1,
		(ch >> 3) & 1, (ch >> 2) & 1, (ch >> 1) & 1, (ch & 1));
}

static uint32_t	uint8_to_uint32(const uint8_t *buf)
{
	uint32_t val = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
	return val;
}

static void	set_byte_color(size_t separator_index, size_t current_index)
{
	p_print_trace("\033[0m");
	if (separator_index == current_index) {
		p_print_trace("\033[1;33m");
	} else if (current_index >= PADDED_CHUNK_SIZE && separator_index < PADDED_CHUNK_SIZE)
	{
		p_print_trace("\033[0;94m");
	}
	else if (current_index < separator_index)
	{
		p_print_trace("\033[0;32m");
	}
}

/**
 * @brief Prints only on TRACE log_level
 */
void	print_block_chunk(const t_block *block, size_t separator_index)
{
	if (!level_verification(P_LOG_TRACE))
		return ;

	for (size_t i = 0; i < 64; i++)
	{
		set_byte_color(separator_index, i);
		print_chunk_uint8_t((uint8_t)(block->chunk[i]));
		if ((i+1) % 8 == 0) {
			p_print_trace("\033[0;1m\t   0x%08x  0x%08x\033[0m\n", uint8_to_uint32(&block->chunk[i-7]), uint8_to_uint32(&block->chunk[i-3]));
		}
		else if (i != 63)
			p_print_trace(" ");
	}
	p_print_trace("\n");
}
