#include "ft_ssl.h"

void	print_usage(void)
{
	dprintf(2, "usage: ft_ssl command [flags] [file/string]\n");
}

void	error_invalid_cmd(const char *cmd)
{
	dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n", cmd);
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

int main(__attribute__((unused)) int argc, char const *argv[])
{
	t_ssl	ssl = {0};

	ssl.hash_type = set_hash_type(argv[1]);
	printf("%d\n", ssl.hash_type);
	if (ssl.hash_type == 0)
		return (1);

	return 0;
}
