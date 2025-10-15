#include "ft_md5.h"
#include <stdarg.h>  // Required for variadic arguments

void	print_bits(uint8_t ch)
{
	printf("%d%d%d%d%d%d%d%d",
		(ch >> 7) & 1, (ch >> 6) & 1, (ch >> 5) & 1, (ch >> 4) & 1,
		(ch >> 3) & 1, (ch >> 2) & 1, (ch >> 1) & 1, (ch & 1));
}

uint32_t	print_hex(uint8_t *buf)
{
	uint32_t val = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
	// printf(" ");
	// print_bits(buf[1]);
	// printf(" ");
	// print_bits(buf[0]);
	return val;
}

void	print_msg_blocks(t_block *block)
{
	for (size_t i = 0; i < 64; i++)
	{
		print_bits((uint8_t)(block->chunk[i]));
		if ((i+1) % 8 == 0)
			printf("\t\t%08x\t%08x\n", print_hex(&block->chunk[i-7]), print_hex(&block->chunk[i-3]));
		else if (i != 63)
			printf(" ");
	}
	printf("\n");
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
		p_print_trace("Closing file descriptor %d\n", block->input_fd);
		close(block->input_fd);
		block->input_fd = UNDEFINED_FD;
	}
	if (block->input_string) {
		p_print_trace("Freeing input string %s\n", block->input_string);
		free(block->input_string);
		block->input_string = NULL;
	}
}

t_block	init_block(char *argv)
{
	t_block	block = {0};
	block.input_string = strdup(argv);
	block.input_fd = UNDEFINED_FD;

	p_print_debug("Initializing block input values to file descriptor : %d\n and string to : %s\n", block.input_fd, block.input_string);

	return (block);
}
