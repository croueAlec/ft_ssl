#include "ft_ssl.h"

static void	define_algorithm_array(hash_func_array *algorithm_array)
{
	algorithm_array[INVALID] = NULL;
	algorithm_array[MD5] = md5;
	algorithm_array[SHA256] = placeholder_sha256;
	algorithm_array[MAX_HASH_NBR - 1] = NULL;
}

bool	execution(t_ssl *ssl)
{
	char			*message = NULL;
	hash_func_array	algorithm[MAX_HASH_NBR] = {0};
	define_algorithm_array(algorithm);

	t_hash	*tmp = NULL, *node = ssl->hash_list;
	while (node)
	{
		tmp = node->next;
		message = get_message(node, ssl);
		// printf("%s\n%s\n", message, algorithm[ssl->hash_type](node));
		printf("executing\n");
		printf("input string : %s\n", node->input);
		algorithm[ssl->hash_type](node);
		node = tmp;
	}

	return (SUCCESS);
}
