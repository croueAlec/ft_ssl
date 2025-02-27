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

static hash_func_array *define_algorithm_array(void)
{
	hash_func_array	*arr = calloc(MAX_HASH_NBR, sizeof(hash_func_array));
	if (!arr)
		return (NULL);

	arr[INVALID] = NULL;
	arr[MD5] = placeholder_md5;
	arr[SHA256] = placeholder_sha256;

	return (arr);
}

bool	execution(t_ssl *ssl)
{
	char			*message = NULL;
	hash_func_array	*algorithm = define_algorithm_array();

	t_hash	*tmp = NULL, *node = ssl->hash_list;
	while (node)
	{
		tmp = node->next;
		message = get_message(node, ssl);
		printf("%s\n%s\n", message, algorithm[ssl->hash_type](node));
		node = tmp;
	}

	return (SUCCESS);
}
