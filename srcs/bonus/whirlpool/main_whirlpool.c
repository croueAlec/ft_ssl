#include "ft_ssl.h"
#include "bonus/ft_whirlpool.h"

static void init_block(t_block_whirlpool *block, const t_hash *node)
{
	block->input_string = node->input;
	block->input_fd = node->infile_fd;
}

static void result_to_str(const char *str, char *digest)
{
	const char digits[] = "0123456789abcdef";

	for (size_t i = 0; i < 64; i++) {
		uint8_t b = ((uint8_t *)str)[i];
		digest[i * 2] = digits[b >> 4];
		digest[i * 2 + 1] = digits[b & 0x0F];
	}
}

/**
 * @brief The whirlpool itself, inits the Block using the input values,
 * starts the hashing and converts the result to the final digest.
 * The implementation is based on the paper
 * "The Whirlpool Secure Hash Function" by WILLIAM STALLINGS
 * function and variable names are based on it's naming convention
 */
void whirlpool(t_hash *node)
{
	t_block_whirlpool block = {0};
	init_block(&block, node);

	whirlpool_loop(&block);

	char tmp[whirlpool_CHUNK_SIZE + 1] = {0};
	memcpy(&tmp, block.result, whirlpool_CHUNK_SIZE);
	result_to_str(tmp, node->digest);

	return;
}
