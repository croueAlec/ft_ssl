#include "ft_ssl.h"

static void	print_flags(char *message, uint8_t flags)
{
	p_print_debug(message);
	p_print_bits_uint8(P_LOG_DEBUG, flags, "", false);
	p_print_debug("                0b     rqp\n");
}

void	print_hash_list(t_ssl *ssl)
{
	if (!ssl)
		return ;

	p_print_debug("Main SSL struct : current hash [%d]\n", ssl->hash_type);
	print_flags(" General flags : ", ssl->general_flags);

	t_hash	*tmp = NULL;
	t_hash *node = ssl->hash_list;
	while (node)
	{
		tmp = node->next;
		p_print_debug("[\n Input type : %d\n", node->input_type);
		if (node->input)
		p_print_debug(" Input: %s\n", node->input);
		if (node->file)
		p_print_debug(" Filename: %s\n", node->file);
		print_flags(" Local flags : ", node->local_flags);
		p_print_debug("]\n\n");
		node = tmp;
	}
}
