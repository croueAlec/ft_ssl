#include "ft_ssl.h"


static char	*open_stdin(void)
{
	int fd = STDIN_FILENO;
	char	*str = read_file(fd);
	if (!str)
		return (calloc(0, sizeof(char)));
	else
		return (str);
}

char	*get_message(t_hash *node, t_ssl *ssl)
{
	switch (node->input_type)
	{
	case STDIN:
		return (open_stdin());
		break;

	case STRING:
		return (node->input);
		break;

	case INFILE:
		return (open_infile(node, ssl));
		break;
	}
}
