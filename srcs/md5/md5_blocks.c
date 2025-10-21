#include "ft_md5.h"
#include <string.h>

t_penelope_log_level	P_LOG_LEVEL = LOG_LEVEL;

static void	length_to_bytes(t_block *block)
{
	p_print_trace("\ttotal length to add as bytes : %zu\n", block->total_length);
	block->total_length *= 8;

	for (size_t i = 0; i < 8; i++)
	{
		block->chunk[(PADDED_CHUNK_SIZE) + i] = ((block->total_length >> (i * 8)) & 0b11111111);
	}
}

static void	fill_block_metadata(t_block *block, bool add_separator, bool is_last_block)
{
	if (add_separator == true) {
		block->chunk[block->buffer_length] = SEPARATOR;
		p_print_trace("\tAdding the separator to current MD5 block\n");
	}

	if (is_last_block) {
		length_to_bytes(block);
		p_print_trace("\tAdding length in bytes to current MD5 block\n");
	}
}

static void	get_next_chunk(t_block *block)
{
	size_t	chunk_length = (strlen(block->input_string) - block->total_length < sizeof(uint8_t) * CHUNK_SIZE) ?  strlen(block->input_string) - block->total_length : sizeof(uint8_t) * CHUNK_SIZE;
	p_print_debug("Reading at most %zu bytes from input\n", chunk_length);

	if (block->input_fd != UNDEFINED_FD)
		read(block->input_fd, block->chunk, CHUNK_SIZE);
	else
		memcpy(block->chunk, &block->input_string[block->total_length], chunk_length);
}

/**
 * @brief The general MD5 Loop. It extracts chunks from the input to the block as shown in [Figure 3] of the README.
 * It then calls md5_update(); to apply the algorithm on this chunk
 */
void	md5_loop(t_block *block)
{
	bool	last_block_reached = false;


	while (last_block_reached == false || block->buffer_length)
	{
		size_t	separator_index = CHUNK_SIZE + 1;
		get_next_chunk(block);
		block->buffer_length = strlen((char*)block->chunk);
		block->total_length += block->buffer_length;

		if (block->buffer_length < PADDED_CHUNK_SIZE && last_block_reached == false) {
			p_print_debug("Processing full MD5 trailing block containing %d bytes from the buffer\n", block->buffer_length);
			fill_block_metadata(block, true, true);
			last_block_reached = true;
			separator_index = block->buffer_length;
			block->buffer_length = 0;

		} else if (block->buffer_length >= PADDED_CHUNK_SIZE && block->buffer_length < CHUNK_SIZE) {
			p_print_debug("Processing penultimate MD5 block containing the separator and %d bytes from the buffer\n", block->buffer_length);
			fill_block_metadata(block, true, false);
			last_block_reached = true;
			separator_index = block->buffer_length;

		} else if (block->buffer_length == 0 && last_block_reached == true) {
			p_print_debug("Processing trailing MD5 block containing byte length only and 0 bytes from the buffer\n");
			fill_block_metadata(block, false, true);

		} else if (block->buffer_length == 64)
		{
			p_print_debug("Processing default full MD5 block containing 64 bytes from the buffer\n");
		}

		block->block_number++;

		print_block_chunk(block, separator_index);

		md5_update(block);
		bzero(block->chunk, CHUNK_SIZE);
	}

	little_to_big_endian(&block->vectors);
	p_print_debug("Final vectors : ");
	print_vector(&block->vectors, "", false, P_LOG_DEFAULT);
}
