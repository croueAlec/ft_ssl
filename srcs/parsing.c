#include "ft_ssl.h"

static bool	parse_flags(t_ssl *ssl, const char *arg, bool *is_str)
{
	for (size_t i = 1; arg[i]; i++)
	{
		switch (arg[i])
		{
		case 's':
			if (!arg[i + 1])
				*is_str = true;
			else
				return (add_hash_node(STRING, ssl, &arg[i + 1], NULL));
			break;

		case 'q':
			ssl->general_flags |= QUIET;
			break;

		case 'r':
			ssl->general_flags |= REVERSE;
			break;

		case 'p':
			return (add_hash_node(STDIN, ssl, NULL, NULL));
			break;
		}
	}

	return (SUCCESS);
}

bool	parse_arguments(t_ssl *ssl, char const *argv[])
{
	if (!argv[0])
	{
		return (add_hash_node(STDIN, ssl, NULL, NULL));
	}

	bool	is_previous_str = false;
	bool	is_file_only = false;

	for (size_t i = 0; argv[i]; i++)
	{
		printf("verif ici %s\nprevious_str %d\n", argv[i], is_previous_str);
		if (argv[i][0] == '-' && is_file_only == false) {
			if (parse_flags(ssl, argv[i], &is_previous_str) == ERROR)
				return (ERROR);
		} else if (is_previous_str) {
			is_previous_str = false;
			if (add_hash_node(STRING, ssl, argv[i], NULL) == ERROR)
				return (ERROR);
		} else {
			is_file_only = true;
			if (add_hash_node(INFILE, ssl, NULL, argv[i]) == ERROR)
				return (ERROR);
		}
	}

		if (is_previous_str) {
			if (add_hash_node(STRING, ssl, NULL, NULL) == ERROR)
				return (ERROR);
		}

	return (SUCCESS);
}
