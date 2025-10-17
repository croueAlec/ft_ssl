#include "ft_md5.h"
#include <stdarg.h>  // Required for variadic arguments

static void	print_chunk_uint8_t(uint8_t ch)
{
	p_print_trace("%d%d%d%d%d%d%d%d",
		(ch >> 7) & 1, (ch >> 6) & 1, (ch >> 5) & 1, (ch >> 4) & 1,
		(ch >> 3) & 1, (ch >> 2) & 1, (ch >> 1) & 1, (ch & 1));
}

static uint32_t	uint8_to_uint32(uint8_t *buf)
{
	uint32_t val = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
	return val;
}

/**
 * @brief Prints only on TRACE log_level
 */
void	print_block_chunk(t_block *block)
{
	if (!level_verification(P_LOG_TRACE))
		return ;

	for (size_t i = 0; i < 64; i++)
	{
		print_chunk_uint8_t((uint8_t)(block->chunk[i]));
		if ((i+1) % 8 == 0) {
			p_print_trace("\t   %08x  %08x\n", uint8_to_uint32(&block->chunk[i-7]), uint8_to_uint32(&block->chunk[i-3]));
		}
		else if (i != 63)
			p_print_trace(" ");
	}
	p_print_trace("\n");
}

int	err(char *err_msg)
{
	p_print_error(err_msg);

	return (1);
}

void	free_blocks(t_block *block)
{
	p_print_debug("Freeing block input values\n");
	if (block->input_fd >= 0) {
		p_print_trace(" Closing file descriptor %d\n", block->input_fd);
		close(block->input_fd);
		block->input_fd = UNDEFINED_FD;
	}
	if (block->input_string) {
		p_print_trace(" Freeing input string %s\n", block->input_string);
		free(block->input_string);
		block->input_string = NULL;
	}
}

t_block	init_block(char *argv)
{
	t_block	block = {0};
	block.input_string = strdup(argv);
	block.input_fd = UNDEFINED_FD;

	p_print_debug("Initializing block input values to file descriptor : %d\n and string to : %s\n\n", block.input_fd, block.input_string);

	return (block);
}
