#include <stdio.h>
#include "test_sha256.h"

t_penelope_log_level	P_LOG_LEVEL = LOG_LEVEL;

static void	init_block(t_block_sha256 *block, char *argv)
{
	block->input_string = argv;
}



int main(int argc, char *argv[])
{
	if (argc != 2)
		return (p_print_error("sha256 error : Invalid argument count\n"), 1);

	t_block_sha256	block = {0};
	init_block(&block, argv[1]);

	sha256_loop(&block);

	return (0);
}
