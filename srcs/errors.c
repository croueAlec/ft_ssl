#include "ft_ssl.h"

void	print_usage(void)
{
	dprintf(2, "usage: ft_ssl command [flags] [file/string]\n");
}

void	error_invalid_cmd(const char *cmd)
{
	dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n", cmd);
}

bool	error_missing_string_argument(t_ssl *ssl)
{
	dprintf(2, "ft_ssl: %s: option requires an argument -- %c\n", ssl->hash_type == MD5 ? "md5" : "sha256", 's');
	return (ERROR);
}
