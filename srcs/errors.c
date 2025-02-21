#include "ft_ssl.h"

void	print_usage(void)
{
	dprintf(2, "usage: ft_ssl command [flags] [file/string]\n");
}

void	error_invalid_cmd(const char *cmd)
{
	dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n", cmd);
}
