#include "ft_md5.h"

t_penelope_log_level	P_LOG_LEVEL = LOG_LEVEL;

void	length_to_bytes(t_block *block)
{
	for (size_t i = 0; i < 8; i++)
	{
		block->chunk[(PADDED_CHUNK_SIZE) + i] = ((block->total_length >> (i * 8)) & 0b11111111);
	}
}

void	fill_block_metadata(t_block *block, bool add_separator, bool is_last_block)
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

void	get_next_chunk(t_block *block)
{
	if (block->input_fd != UNDEFINED_FD)
		read(block->input_fd, block->chunk, CHUNK_SIZE);
	else
		memcpy(block->chunk, &block->input_string[block->total_length], sizeof(uint8_t) * CHUNK_SIZE);
}

void	md5_block_building(t_block *block)
{
	bool	last_block_reached = false;


	while (last_block_reached == false || block->buffer_length)
	{
		get_next_chunk(block);
		block->buffer_length = strlen((char*)block->chunk);
		block->total_length += block->buffer_length;

		if (block->buffer_length < PADDED_CHUNK_SIZE && last_block_reached == false) {
			p_print_debug("Processing full MD5 trailing block\n");
			fill_block_metadata(block, true, true);
			last_block_reached = true;
			block->buffer_length = 0;

		} else if (block->buffer_length >= PADDED_CHUNK_SIZE && block->buffer_length < CHUNK_SIZE) {
			p_print_debug("Processing penultimate MD5 block containing the separator\n");
			fill_block_metadata(block, true, false);
			last_block_reached = true;

		} else if (block->buffer_length == 0 && last_block_reached == true) {
			p_print_debug("Processing trailing MD5 block containing byte length only\n");
			fill_block_metadata(block, false, true);
		}

		print_msg_blocks(block);

		md5(block);
		bzero(block->chunk, CHUNK_SIZE);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (err("Bad argument count"));

	t_block	block = init_block(argv[1]);
	md5_block_building(&block);

	free_blocks(&block);

	return (0);
}
