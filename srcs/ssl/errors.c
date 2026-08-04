#include "ft_ssl.h"
#include <errno.h>

void print_usage(void)
{
	p_print_fatal("usage: ft_ssl command [flags] [file/string]\n");
}

void error_invalid_cmd(const char *cmd)
{
	p_print_fatal("ft_ssl: Error: '%s' is an invalid command.\n\n%s\nFlags:\n-p -q -r -s\n", cmd, COMMAND_LIST);
}

void error_unavailable_hash(const char *cmd)
{
	p_print_fatal("ft_ssl: Error: '%s' is unavailable. Try compiling with 'make bonus'.\n", cmd);
}

int error_open_infile(t_ssl *ssl, t_hash *hash, bool is_stdin)
{

	ssl->error_status = 1;
	if (is_stdin == true)
		p_print_fatal("ft_ssl: Fatal error: could not open stdin\n");

	hash->disabled = true;

	if (errno == 2)
		p_print_error("ft_ssl: %s: %s: No such file or directory\n", hash_commands[ssl->hash_type].name /* hash_list[ssl->hash_type] */, hash->file);
	else if (errno == 13)
		p_print_error("ft_ssl: %s: %s: Permission denied\n", hash_commands[ssl->hash_type].name /* hash_list[ssl->hash_type] */, hash->file);

	return (INFILE_ERROR);
}
