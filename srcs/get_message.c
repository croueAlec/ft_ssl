#include "ft_ssl.h"
#include <fcntl.h>
#include <unistd.h>

char	*open_infile(t_hash *node, t_ssl *ssl)
{
	int fd = open(node->file, O_RDONLY);
	if (fd < 0) {
		error_open_infile(ssl);
		return (NULL);
	} else
	{
		close(fd);
		return (NULL);
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
		return (node->file);
		break;
	}
}
