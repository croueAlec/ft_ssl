#include "dynamic_input.h"

char	*handle_stdin(void)
{
	int	fd = STDIN_FILENO;

	char	*str = get_all_lines(fd);

	return (str);
}

int	handle_file(char **argv)
{
	int fd = open(argv[1], O_RDONLY);

	if (fd >= 0)
		return (fd);

	dprintf(2, "Error: couldn't open file %s\n", argv[1]);
	exit(1);
}

char	*handle_string(char **argv)
{
	char	*str = NULL;

	str = strdup(argv[2]);
	if (str)
		return (str);

	dprintf(2, "Error: malloc fail when duping string input\n");
	exit(1);
}

t_input	handle_inputs(int argc, char **argv)
{

	t_input	input = {-2, NULL};

	if (argc == 1)
		input.str = handle_stdin();
	else if (argc == 2)
		input.fd = handle_file(argv);
	else if (argc == 3)
		input.str = handle_string(argv);

	return (input);
}

void	get_next_stack(t_input *input, uint8_t *buffer, size_t total_len)
{
	if (input->fd != -2)
		read(input->fd, buffer, BLOCK_SIZE);
	else
		memcpy(buffer, &input->str[total_len], sizeof(uint8_t) * BLOCK_SIZE);
}

void	length_to_bytes(uint8_t *buffer, const size_t total_length)
{
	for (size_t i = 0; i < 8; i++)
	{
		buffer[(BLOCK_SIZE - 8) + i] = ((total_length >> (i * 8)) & 0b11111111);
	}
}

void	fill_full_final_block(uint8_t *buffer, size_t total_length, size_t buflen)
{
	buffer[buflen] = SEPARATOR;
	length_to_bytes(buffer, total_length);
}

void	fill_block(uint8_t *buffer, size_t buflen, size_t total_length, bool add_separator, bool is_last_block)
{
	if (add_separator == true)
		buffer[buflen] = SEPARATOR;

	if (is_last_block)
		length_to_bytes(buffer, total_length);
}

void	process_block(uint8_t *buffer)
{
	printf("[%s]\n", (char*)buffer);
}

void	loop(t_input *input)
{
	size_t	total_len = 0;
	uint8_t	buffer[BLOCK_SIZE + 1] = {0};
	bool	last_block_reached = false;
	size_t buflen = 0;

	while (last_block_reached == false || buflen)
	{
		get_next_stack(input, buffer, total_len);
		buflen = strlen((char*)buffer);
		total_len += buflen;

		if (buflen < BLOCK_SIZE - 8 && last_block_reached == false) {
			fill_full_final_block(buffer, total_len, buflen);
			last_block_reached = true;
			buflen = 0;

		} else if (buflen >= BLOCK_SIZE - 8 && buflen < BLOCK_SIZE) {
			fill_block(buffer, buflen, total_len, true, false);
			last_block_reached = true;

		} else if (buflen == 0 && last_block_reached == true) {
			fill_block(buffer, buflen, total_len, false, true);
		}

		process_block(buffer);
		bzero(buffer, BLOCK_SIZE);
	}
}

void	end(t_input	*input)
{
	if (input->fd >= 0)
		close(input->fd);
	if (input->str)
		free(input->str);
}

int main(int argc, char *argv[])
{
	if (argc != 1 && argc != 2 && argc != 3)
		return dprintf(2, "Error\n");

	t_input	input = handle_inputs(argc, argv);

	loop(&input);

	end(&input);

	return (0);
}


/*
buflen 0-55 >> add SEP + LEN					>> fill_full_final_block then process & exit

buflen 56-63 >>> add SEP + new block LEN		>>

buflen 64 >>> continue process


block0 = ""
block0-55 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
block0-55 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012"
block56-63 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123"
block56-63 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-"
block64 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789--"
*/
