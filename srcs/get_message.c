#include "ft_ssl.h"

char	*get_message(t_hash *node)
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
