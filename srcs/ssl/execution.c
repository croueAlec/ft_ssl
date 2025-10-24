#include "ft_ssl.h"

static void	define_algorithm_array(hash_func_array *algorithm_array)
{
	algorithm_array[INVALID] = NULL;
	algorithm_array[MD5] = md5;
	algorithm_array[SHA256] = sha256;
	algorithm_array[MAX_HASH_NBR + 2] = NULL;
}

bool	execution(t_ssl *ssl)
{
	hash_func_array	algorithm[MAX_HASH_NBR + 2] = {0};	// Adding 2 for INVALID add NULL terminating.
	define_algorithm_array(algorithm);

	t_hash	*tmp = NULL, *node = ssl->hash_list;
	size_t	node_count = 0;
	p_print_info("%d\n", ssl->hash_type);

	while (node)
	{
		tmp = node->next;
		p_print_debug("Processing node number : %zu\n", node_count);
		algorithm[ssl->hash_type](node);
		node = tmp;
		node_count++;
	}

	return (SUCCESS);
}
