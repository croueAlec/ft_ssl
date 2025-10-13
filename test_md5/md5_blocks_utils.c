#include "ft_md5.h"
#include <stdarg.h>  // Required for variadic arguments

#ifndef DEBUG
# define DEBUG 1
#endif

void printIF(const char *format, ...) {
	if (DEBUG == 1) {
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

void	print_bits(uint8_t ch)
{
	printIF("%d%d%d%d%d%d%d%d",
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
			printIF("\t\t%08x\t%08x\n", print_hex(&block->chunk[i-7]), print_hex(&block->chunk[i-3]));
		else if (i != 63)
			printIF(" ");
	}
	printIF("\n");
}

int	err(char *err_msg)
{
	dprintf(2, "Error : %s\n", err_msg);

	return 1;
}

void	free_blocks(t_block *block)
{
	if (block->input_fd >= 0)
		close(block->input_fd);
	if (block->input_string)
		free(block->input_string);
}

t_block	init_block(char *argv)
{
	t_block	block = {0};
	block.input_string = strdup(argv);
	block.input_fd = UNDEFINED_FD;

	return (block);
}
