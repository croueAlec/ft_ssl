#include "./includes/md5.h"
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

t_block	*fill_msg_blocks(char *message, t_block *previous_block)
{
	t_block	*block = calloc(1, sizeof(t_block));
	if (!block)
		return NULL;

	if (previous_block)
		previous_block->next = block;

	memcpy(block->chunk, message, sizeof(uint8_t) * CHUNK_SIZE);

	return block;
}

char	*slide_message(char *message)
{
	size_t	message_length = strlen(message);
	size_t	new_start = (message_length < CHUNK_SIZE) ? message_length : CHUNK_SIZE;

	message = &message[new_start];

	return message;
}

void	length_to_bytes(t_block *block, const size_t original_message_length)
{
	for (size_t i = 0; i < 8; i++)
	{
		// block->chunk[(CHUNK_SIZE - 1) - i] = ((original_message_length >> (i * 8)) & 0b11111111) << 3; // is it litte or big endian ?
		block->chunk[(PADDED_CHUNK_SIZE) + i] = ((original_message_length >> (i * 8)) & 0b11111111); // it was little endian
	}
}

t_block	*fill_tail_block(char *message, const size_t original_message_length, bool separator_added)
{
	size_t	message_length = strlen(message);
	t_block	*block = calloc(1, sizeof(t_block));
	if (!block)
		return NULL;

	// printf("a a a\n");

	memcpy(block->chunk, message, sizeof(uint8_t) * message_length);

	if (separator_added == false)
		block->chunk[message_length] = SEPARATOR;

	// printf("b b b\n");

	length_to_bytes(block, original_message_length * 8);

	// printf("c c c\n");

	return block;
}

size_t	count_blocks(const size_t original_message_length, bool *add_separator)
{
	size_t	block_count = (original_message_length / CHUNK_SIZE);
	if ((original_message_length % CHUNK_SIZE) > (PADDED_CHUNK_SIZE - 1)) { // verifier ici
		block_count++;
		*add_separator = true;
	}

	return block_count;
}

t_block	*separate_message_in_blocks(char *message)
{
	// printf("a a\n");

	t_block	*first_block = NULL;
	t_block	*previous_block = NULL;
	char	*new_message = message;

	bool	add_separator = false;
	const size_t	original_message_length = strlen(message);
	const size_t	block_count = count_blocks(original_message_length, &add_separator);


	// printf("b b block count :%zu\n", block_count);

	for (size_t i = 0; i < block_count; i++)
	{
		previous_block = fill_msg_blocks(new_message, previous_block);
		if (!previous_block)
			return (NULL); // gerer free

		if (i == 0)
			first_block = previous_block;

		new_message = slide_message(new_message);
	}

	// printf("c c\n");

	if (add_separator == true)
		previous_block->chunk[strlen((char*)(previous_block->chunk))] = SEPARATOR;

	t_block	*last_block = fill_tail_block(new_message, original_message_length, add_separator);
	if (!last_block)
		return NULL; // gerer free

	if (first_block == NULL)
		first_block = last_block;
	else
		previous_block->next = last_block;

	// printf("d d\n");

	return first_block;
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

void	print_msg_blocks(t_block *blocks)
{
	t_block	*node = blocks;

	while (node)
	{
		for (size_t i = 0; i < 64; i++)
		{
			print_bits((uint8_t)(node->chunk[i]));
			if ((i+1) % 8 == 0)
				printIF("\t\t%08x\t%08x\n", print_hex(&node->chunk[i-7]), print_hex(&node->chunk[i-3]));
			else if (i != 63)
				printIF(" ");
		}
		printIF("\n");
		node = node->next;
	}
}

int	err(char *err_msg)
{
	dprintf(2, "Error : %s\n", err_msg);

	return 1;
}

void	free_blocks(t_block *blocks)
{

	t_block	*next_node = blocks;

	while (next_node)
	{
		blocks = next_node;
		next_node = next_node->next;
		free(blocks);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return err("Bad argument count");

	t_block	*list = separate_message_in_blocks(argv[1]);
	if (!list)
		return err("Malloc fail");

	print_msg_blocks(list);

	md5(list);

	free_blocks(list);

	return 0;
}
