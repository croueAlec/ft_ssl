#include "ft_ssl.h"
#include <errno.h>

extern char	hash_list[3][8];

void	print_usage(void)
{
	p_print_error("usage: ft_ssl command [flags] [file/string]\n");
}

void	error_invalid_cmd(const char *cmd)
{
	p_print_error("ft_ssl: Error: '%s' is an invalid command.\n\n%s\nFlags:\n-p -q -r -s\n", cmd, COMMAND_LIST);
}

void	error_disabled_hash(const char *cmd)
{
	p_print_error("ft_ssl: Error: '%s' is currently disabled. This setting can be changed in the Makefile.\n", cmd);
}

int	error_open_infile(const t_ssl *ssl, t_hash *hash, bool is_stdin)
{
	char	stdin_filename[] = "stdin";

	if (is_stdin == true)
		hash->file = stdin_filename;

	if (errno == 2)
		p_print_error("ft_ssl: %s: %s:No such file or directory\n", hash_list[ssl->hash_type], hash->file);
	else if (errno == 13)
		p_print_error("ft_ssl: %s: %s: Permission denied\n", hash_list[ssl->hash_type], hash->file);

	if (is_stdin == true)
		hash->file = NULL;

	return (INFILE_ERROR);
}
