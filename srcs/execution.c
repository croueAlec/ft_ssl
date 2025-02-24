#include "ft_ssl.h"

char	*placeholder_md5(t_hash *node)
{
	(void)node;
	return ("This is an md5\n");
}

char	*placeholder_sha256(t_hash *node)
{
	(void)node;
	return ("This is a sha256\n");
}

static char	*(*get_algorithm(t_hash_type type))(t_hash *)
{
	switch (type)
	{
	case INVALID:
		return (NULL);
	case MD5:
		return (placeholder_md5);
		break;

	case SHA256:
		return (placeholder_sha256);
		break;
	}
}

static char	*get_message(t_hash *node)
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

bool	execution(t_ssl *ssl)
{
	char	*message = NULL;
	char	*(*algorithm)(t_hash*) = get_algorithm(ssl->hash_type);

	t_hash	*tmp = NULL, *node = ssl->hash_list;
	while (node)
	{
		tmp = node->next;
		message = get_message(node);
		printf("%s\n%s\n", message, algorithm(node));
		node = tmp;
	}

	return (SUCCESS); //bug here ./ft_ssl md5 -s salut -qrssalut
}
