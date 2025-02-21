#include "ft_ssl.h"

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
	printf("%d\n", ssl.hash_type);
	if (ssl.hash_type == 0)
		return (1);

	if (parse_arguments(&ssl, &argv[2]) == ERROR)
	{
		free_hash_list(&ssl);
		return (1);
	}

	return 0;
}
