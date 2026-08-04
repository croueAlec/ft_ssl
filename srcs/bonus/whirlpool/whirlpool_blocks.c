#include "ft_ssl.h"
#include "bonus/ft_whirlpool.h"
#include "bonus/ft_whirlpool_algorithm.h"

static void length_to_bytes(t_block_whirlpool *block)
{
	p_print_trace("\ttotal length to add as bytes : %zu\n", block->total_length);
	block->total_length *= 8;

	for (size_t i = 0; i < 8; i++) {
		block->chunk[63 - i] = (block->total_length & 0xff);
		block->total_length >>= 8;
	}
}

static void fill_block_metadata(t_block_whirlpool *block, bool add_separator, bool is_last_block)
{
	if (add_separator == true) {
		block->chunk[block->buffer_length] = whirlpool_SEPARATOR;
		p_print_trace("\tAdding the separator to current Whirlpool block\n");
	}

	if (is_last_block == true) {
		length_to_bytes(block);
		p_print_trace("\tAdding length in bytes to current Whirlpool block\n");
	}
}

static void get_next_chunk(t_block_whirlpool *block)
{
	size_t chunk_length = (ft_safe_strlen(block->input_string) - block->total_length < sizeof(uint8_t) * whirlpool_CHUNK_SIZE) ? ft_safe_strlen(block->input_string) - block->total_length : sizeof(uint8_t) * whirlpool_CHUNK_SIZE;
	if (block->input_fd == UNDEFINED_FD)
		p_print_debug("Copying at most %zu bytes from input\n", chunk_length);

	if (block->input_fd != UNDEFINED_FD) {
		block->buffer_length = (size_t)read(block->input_fd, block->chunk, whirlpool_CHUNK_SIZE);
	} else {
		memcpy(block->chunk, &block->input_string[block->total_length], chunk_length);
		block->buffer_length = ft_safe_strlen((char *)block->chunk);
	}
}

/**
 * @brief The general whirlpool Loop. It extracts chunks of at most 64 bytes from the input to the block.
 * It then calls whirlpool_update(); to apply the algorithm on this chunk
 */
void whirlpool_loop(t_block_whirlpool *block)
{
	bool append_separator = true;
	bool last_block_reached = false;

	do {
		get_next_chunk(block);

		block->total_length += block->buffer_length;
		if (block->buffer_length < whirlpool_PADDED_CHUNK_SIZE) {
			p_print_info("Processing block containing %d bytes from the buffer, separator, and length\n", block->buffer_length);
			fill_block_metadata(block, block->total_length, append_separator);
			last_block_reached = true;

		} else if (block->buffer_length < whirlpool_CHUNK_SIZE) {
			p_print_info("Processing penultimate block containing %d bytes from the buffer, and the separator\n", block->buffer_length);
			block->chunk[block->buffer_length] = 0x80;
			append_separator = false;

		} else if (block->buffer_length >= whirlpool_CHUNK_SIZE) {
			p_print_info("Processing default full block containing 64 bytes from the buffer\n");
			;
		}

		whirlpool_update(block);
		memcpy(block->H, block->result, MATRIX_SIZE * MATRIX_SIZE);
		if (last_block_reached == true) {
			break;
		}
	} while (true);
}
