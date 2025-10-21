#include "ft_ssl.h"
#include <fcntl.h>
#include <unistd.h>

static char	*read_stdin(int fd)
{
	char	*tmp = get_next_line(fd);
	char	*file_str = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		file_str = ft_sep_join(file_str, tmp, NULL);
		(free(tmp), tmp = NULL);
		if (!file_str)
			return (NULL);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (file_str);
}

static char	*handle_stdin(t_hash *node, t_ssl *ssl)
{
	int		fd = STDIN_FILENO;
	char	*str = NULL;

	if (fd < 0) {
		error_open_infile(ssl, node, true);

		return (NULL);

	} else {
		str = read_stdin(fd);
		if(!str)
			str = calloc(1, sizeof(char));

		return (str);
	}
}

void	free_hash_list(t_ssl *ssl)
{
	t_hash	*tmp = NULL;
	t_hash *node = ssl->hash_list;
	while (node)
	{
		tmp = node->next;
		if (node->input)
			(free(node->input), node->input = NULL);
		if (node->file)
			(free(node->file), node->file = NULL);
		if (node->infile_fd != UNDEFINED_FD && node->infile_fd >= 0)
			(close(node->infile_fd), node->infile_fd = UNDEFINED_FD, free(node->input), node->input = NULL);
		(free(node), node = NULL);
		node = tmp;
	}
}

static	t_hash *set_node_last(t_ssl *ssl, t_hash *node)
{
	t_hash	*head = ssl->hash_list;
	while (head->next)
		head = head->next;
	head->next = node;
	return (node);
}

static t_hash	*allocate_new_node(t_ssl *ssl)
{
	t_hash	*node = calloc(sizeof(t_hash), 1);
	if (!node)
		return (NULL);

	if (!ssl->hash_list)
	{
		ssl->hash_list = node;
		return (node);
	} else
	{
		return (set_node_last(ssl, node));
	}
}

int	add_hash_node(t_input_type type, t_ssl *ssl, char const *string, char const *filename)
{
	t_hash	*new_hash = allocate_new_node(ssl);
	if (!new_hash)
		return (ERROR);
	printf("adding node type %d\t%s\t%s\n", type, string, filename);

	new_hash->input_type = type;
	new_hash->local_flags = ssl->general_flags;
	new_hash->infile_fd = UNDEFINED_FD;

	if (string) {
		new_hash->input = strdup(string);
		if (!new_hash->input)
			return (ERROR);

	} else if (filename) {
		new_hash->file = strdup(filename);
		if (!new_hash->file)
			return (ERROR);

		new_hash->infile_fd = open(new_hash->file, O_RDONLY);
		if (new_hash->infile_fd == -1)
			return (error_open_infile(ssl, new_hash, false));

	} else if (new_hash->input_type == STDIN)
	{
		new_hash->input = handle_stdin(new_hash, ssl);
		printf("\t\t\tstdin string : '%s'\n", new_hash->input);
		if (!new_hash->input)
			return (ERROR);
	}

	return (SUCCESS);
}
