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

// bool	parse_flags(t_ssl *ssl, bool *is_str, size_t i)
void parse_flags()
{
	return ;
}

void	add_stdin_node(void)
{
	return ;
}

void	add_str_node(void)
{
	return ;
}

void	add_file_node(void)
{
	return ;
}

bool	parse_arguments(t_ssl *ssl, char const *argv[])
{
	if (!argv[0])
	{
		add_stdin_node();
		return (SUCCESS);
	}

	bool	is_previous_str = 0;

	for (size_t i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '-')
			parse_flags();
		else if (is_previous_str)
			add_str_node();
		else
			add_file_node();
	}

	return (SUCCESS);
}

int	main(__attribute__((unused)) int argc, char const *argv[])
{
	t_ssl	ssl = {0};

	ssl.hash_type = set_hash_type(argv[1]);
	printf("%d\n", ssl.hash_type);
	if (ssl.hash_type == 0)
		return (1);

	if (parse_arguments(&ssl, &argv[2]) == ERROR)
		return 1;

	return 0;
}
