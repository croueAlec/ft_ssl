#include "ft_ssl.h"

static bool	parse_flags(t_ssl *ssl, const char *arg, bool *is_str)
{
	bool	exit_loop = false;
	for (size_t i = 1; arg[i] && !exit_loop; i++)
	{
		switch (arg[i])
		{
		case 's':
			if (!arg[i + 1])
				*is_str = true;
			else
				add_hash_node(STRING, ssl, &arg[i + 1], NULL);
			exit_loop = true;
			break;

		case 'q':
			ssl->general_flags |= QUIET;
			break;

		case 'r':
			ssl->general_flags |= REVERSE;
			break;

		case 'p':
			add_hash_node(STDIN, ssl, NULL, NULL);
			break;
		}
	}

	return ;
}

bool	parse_arguments(t_ssl *ssl, char const *argv[])
{
	if (!argv[0])
	{
		add_hash_node(STDIN, ssl, NULL, NULL);
		return (SUCCESS);
	}

	bool	is_previous_str = 0;

	for (size_t i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '-')
			parse_flags(ssl, argv[i], &is_previous_str);
		else if (is_previous_str)
			add_hash_node(STRING, ssl, argv[i], NULL);
		else
			add_hash_node(INFILE, ssl, NULL, argv[i]);
	}

	return (SUCCESS);
}
