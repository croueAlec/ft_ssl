#include "ft_sha256.h"

t_penelope_log_level	P_LOG_LEVEL = LOG_LEVEL;

static void	init_block(t_block_sha256 *block, const t_hash *node)
{
	block->input_string = node->input;
	block->input_fd = node->infile_fd;
	p_print_debug("Initializing block input values to file descriptor : %d\n or string to : %s\n\n", block->input_fd, block->input_string);
}

static void	init_hash_values(uint32_t h_values[8])
{
	h_values[0] = 0x6a09e667;
	h_values[1] = 0xbb67ae85;
	h_values[2] = 0x3c6ef372;
	h_values[3] = 0xa54ff53a;
	h_values[4] = 0x510e527f;
	h_values[5] = 0x9b05688c;
	h_values[6] = 0x1f83d9ab;
	h_values[7] = 0x5be0cd19;
}

static void	hash_values_to_str(const hash_values h_values, char *output)
{
	const char hex_chars[] = "0123456789abcdef";

	p_print_debug("Converting our hash_values to a digest stored in node->digest\n");

	for (size_t i = 0; i < sha256_DIGEST_SIZE; i++)
	{
		uint32_t value = h_values[i / 8];		// Iterate through our array changing vector every 8 iteration.
		int shift = (7 - i) * 4;
		output[i] = hex_chars[(value >> shift) & 0x0F];
	}
}

void	sha256(t_hash *node)
{
	t_block_sha256	block = {0};
	init_block(&block, node);

	init_hash_values(block.h_values);

	sha256_loop(&block);

	char	digest[sha256_DIGEST_SIZE] = {0};

	hash_values_to_str(block.h_values, digest);

	p_print_info("%s\n", digest);

	return (0);
}
