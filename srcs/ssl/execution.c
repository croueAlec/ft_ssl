#include "ft_ssl.h"

static hash_func_array *define_algorithm_array(void)
{
	hash_func_array	*arr = calloc(MAX_HASH_NBR, sizeof(hash_func_array));
	if (!arr)
		return (NULL);

	arr[INVALID] = NULL;
	arr[MD5] = md5;
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
		// printf("%s\n%s\n", message, algorithm[ssl->hash_type](node));
		printf("executing\n");
		algorithm[ssl->hash_type](node);
		node = tmp;
	}

	return (SUCCESS);
}
