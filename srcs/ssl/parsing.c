#include "ft_ssl.h"

static bool	parse_flags(t_ssl *ssl, const char *flags, bool *is_separate_string)
{
	for (size_t i = 1; flags[i]; i++)
	{
		switch (flags[i])
		{
		case 's':
			if (!flags[i + 1])
				*is_separate_string = true;
			else
				return (add_hash_node(STRING, ssl, &flags[i + 1], NULL));
			break;

		case 'q':
			ssl->general_flags |= QUIET;
			break;

		case 'r':
			ssl->general_flags |= REVERSE;
			break;

		case 'p':
			ssl->general_flags |= ECHO;
			return (add_hash_node(STDIN, ssl, NULL, NULL));
			break;
		}
	}

	return (SUCCESS);
}

/**
 * @brief This function parses the arguments and builds the linked-list of inputs.
 * The call to add_hash_node using the STRING enum in this function and in parse_flags handles two cases ["-s<string>" and "-s <string>"] (note the space that separates the flag and the string)
 * */
bool	parse_arguments(t_ssl *ssl, char const *argv[])
{
	if (!argv[0])
	{
		return (add_hash_node(STDIN, ssl, NULL, NULL));
	}

	bool	is_separate_string = false;
	bool	no_options_found = false;

	for (size_t i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '-' && no_options_found == false) {
			if (parse_flags(ssl, argv[i], &is_separate_string) == ERROR)
				return (ERROR);
		} else if (is_separate_string) {
			is_separate_string = false;
			if (add_hash_node(STRING, ssl, argv[i], NULL) == ERROR)
				return (ERROR);
		} else {
			no_options_found = true;
			if (add_hash_node(INFILE, ssl, NULL, argv[i]) != SUCCESS) // Checking for ERROR or INFILE_ERROR
				return (ERROR);
		}
	}

	if (is_separate_string)	// Handles trailing [-s] option with no string after
	{
		if (add_hash_node(STRING, ssl, "", NULL) == ERROR)
			return (ERROR);
	}

	if (ssl->hash_list == NULL)	// Handles '-r' or '-q' flags with nothing else, adds STDIN node
	{
		return (add_hash_node(STDIN, ssl, NULL, NULL));
	}

	return (SUCCESS);
}
