#include "ft_ssl.h"
#include "ft_md5.h"

static void	init_block(t_block *block, t_hash *node)
{
	block->input_string = node->input;
	block->input_fd = node->infile_fd;

	p_print_debug("Initializing block input values to file descriptor : %d\n and string to : %s\n\n", block->input_fd, block->input_string);
}

/**
 * @brief The MD5 itself, inits the Block using the input values,
 * starts the hashing and free's everything at the end.
 */
void	md5(t_hash *node)
{
	t_block	block = {0};
	init_block(&block, node);

	md5_loop(&block);
}
