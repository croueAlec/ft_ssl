#include "ft_ssl.h"
#include <errno.h>

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

int	error_open_infile(t_ssl *ssl, t_hash *hash, bool is_stdin)
{
	char	stdin_filename[] = "stdin";

	if (is_stdin == true)
		hash->file = stdin_filename;

	if (errno == 2)
		dprintf(2, "ft_ssl: %s: %s:No such file or directory\n", ssl->hash_type == MD5 ? "md5" : "sha256", hash->file);
	else if (errno == 13)
		dprintf(2, "ft_ssl: %s: %s: Permission denied\n", ssl->hash_type == MD5 ? "md5" : "sha256", hash->file);

	if (is_stdin == true)
		hash->file = NULL;

	return (INFILE_ERROR);
}
