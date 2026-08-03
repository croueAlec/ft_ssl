#include "ft_ssl.h"

const hash_func_array algorithm[] = {
	md5,
	sha256,
#ifdef BONUS
	whirlpool,
#endif
	NULL,
};

const size_t max_hash_nbr = (sizeof(algorithm) / sizeof(algorithm[0]));

bool execution(t_ssl *ssl)
{

	t_hash *tmp = NULL, *node = ssl->hash_list;
	size_t	node_count = 0;

	while (node) {
		tmp = node->next;
		if (node->disabled == false) {
			p_print_debug("Processing node number : %zu\n", node_count);
			algorithm[ssl->hash_type](node);
		} else {
			p_print_debug("Skipping disabled node number : %zu\n", node_count);
		}

		node = tmp;
		node_count++;
	}

	return (SUCCESS);
}
