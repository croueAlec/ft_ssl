#include "ft_ssl.h"

t_penelope_log_level	P_LOG_LEVEL = LOG_LEVEL;

static void print_flags(char *message, uint8_t flags)
{
	p_print_debug(message);
	p_print_bits_uint8(P_LOG_DEBUG, flags, "", false);
	p_print_debug("                0b     rqp\n");
}

void print_hash_list(t_ssl *ssl)
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

t_hash_type	set_hash_type(const char *cmd)
{
	if (!cmd)
		return (print_usage(), INVALID);

	if (strcmp(cmd, "md5") == 0)
		return (MD5);

	if (strcmp(cmd, "sha256") == 0)
		return (SHA256);

	error_invalid_cmd(cmd);
	return (INVALID);
}

int	main(__attribute__((unused)) int argc, char const *argv[])
{
	t_ssl	ssl = {0};

	ssl.hash_type = set_hash_type(argv[1]);
	if (ssl.hash_type == 0)
		return (1);

	if (parse_arguments(&ssl, &argv[2]) == ERROR)
	{
		p_print_error("Error, freeing everything\n");
		free_hash_list(&ssl);
		return (1);
	}

	print_hash_list(&ssl);

	execution(&ssl);

	free_hash_list(&ssl);

	return (0);
}
