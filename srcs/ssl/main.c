#include "ft_ssl.h"

t_penelope_log_level	P_LOG_LEVEL = LOG_LEVEL;
char					hash_list[3][8] = { "Invalid", "md5", "sha256"};

t_hash_type	set_hash_type(const char *cmd)
{
	t_hash_type	type = INVALID;
	if (!cmd)
		return (print_usage(), INVALID);

	if (strcmp(cmd, hash_list[MD5]) == 0)
		type = MD5;
	else if (strcmp(cmd, hash_list[SHA256]) == 0)
		type = SHA256;
	else {
		error_invalid_cmd(cmd);
		return (INVALID);
	}

	if (type == INVALID)
		error_disabled_hash(cmd);
	return (type);
}

int	main(__attribute__((unused)) int argc, char const *argv[])
{
	t_ssl	ssl = {0};

	ssl.hash_type = set_hash_type(argv[1]);
	if (ssl.hash_type == INVALID)
		return (1);

	if (parse_arguments(&ssl, &argv[2]) == ERROR)
	{
		if (ssl.error_status != 1)
			p_print_fatal("ft_ssl: Fatal error: malloc() failed\n");
		ssl.error_status = 1;
		free_hash_list(&ssl);

		return (ssl.error_status);
	}

	print_hash_list(&ssl);

	execution(&ssl);

	print_hash_list_digests(&ssl);

	free_hash_list(&ssl);

	return (ssl.error_status);
}
