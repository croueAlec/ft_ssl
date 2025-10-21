#include "ft_ssl.h"
#include "ft_md5.h"

static void	init_block(t_block *block, t_hash *node)
{
	block->input_string = node->input;
	block->input_fd = node->infile_fd;

	p_print_debug("Initializing block input values to file descriptor : %d\n or string to : %s\n\n", block->input_fd, block->input_string);
}

#include <stdio.h>
#include <stdint.h>

void vectors_to_str(context_vectors const *vectors, char *output) {
	const char hex_chars[] = "0123456789abcdef";

	p_print_debug("Converting our context_vectors to a digest stored in node->digest\n");

	const uint32_t *context_vectors_array = (const uint32_t *)vectors;	// Interpret our context_vectors as an array.

	for (size_t i = 0; i < MD5_DIGEST_SIZE; i++)
	{
		uint32_t value = context_vectors_array[i / 8];		// Iterate through our array changing vector every 8 iteration.
		int shift = (7 - i) * 4;
		output[i] = hex_chars[(value >> shift) & 0x0F];
	}
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

	vectors_to_str(&(block.vectors), node->digest);
}
