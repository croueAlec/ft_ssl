#include "ft_ssl.h"
#include <fcntl.h>
#include <unistd.h>

static char	*read_file(int fd)
{
	char	*tmp = get_next_line(fd);
	char	*file_str = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		file_str = ft_sep_join(file_str, tmp, NULL);
		tmp = NULL;
		if (!file_str)
			return (NULL);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (file_str);
}

static char	*open_infile(t_hash *node, t_ssl *ssl)
{
	int fd = open(node->file, O_RDONLY);
	if (fd < 0) {
		error_open_infile(ssl);
		return (NULL);
	} else {
		return (read_file(fd));
	}
}

char	*get_message(t_hash *node, t_ssl *ssl)
{
	switch (node->input_type)
	{
	case STDIN:
		return ("STDIN");
		break;

	case STRING:
		return (node->input);
		break;

	case INFILE:
		return (open_infile(node, ssl));
		break;
	}
}
