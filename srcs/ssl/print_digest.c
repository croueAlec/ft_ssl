#include "ft_ssl.h"

const char	capitalized_hash_list[3][8] = { "INVALID", "MD5", "SHA256"};

static bool	check_flag(uint8_t value, t_flags flag)
{
	if ((value & flag) > NONE)
		return true;
	else
		return false;
}

static void	print_stdin_output(const t_hash *node, const char *hash_name)
{
	if (check_flag(node->local_flags, QUIET) == true)
	{
		if (check_flag(node->local_flags, ECHO) == true) {
			p_print_default("%s\n", node->input);
		}
		p_print_default("%s\n", node->digest);

	} else {

		if (check_flag(node->local_flags, ECHO) == true ) {
			p_print_default("%s(\"%s\")= ", hash_name, node->input);
			p_print_default("%s\n", node->digest);

		 } else {

			if (check_flag(node->local_flags, REVERSE) == true) {
				p_print_default("%s", node->digest);
				p_print_default("  stdin");
			} else {
				p_print_default("%s(stdin)= ", hash_name);
				p_print_default("%s\n", node->digest);
			}
		}
	}
}

static void	print_file_output(const t_hash *node, const char *hash_name)
{
	if (check_flag(node->local_flags, QUIET) == true)
	{
		p_print_default("%s\n", node->digest);

	} else {

		if (check_flag(node->local_flags, REVERSE) == true)
		{
			p_print_default("%s");
			p_print_default("  %s", node->file);
		} else {
			p_print_default("%s(%s)= ", hash_name, node->file);
			p_print_default("%s\n", node->digest);
		}
	}
}

static void	print_string_output(const t_hash *node, const char *hash_name)
{
	if (check_flag(node->local_flags, QUIET) == true)
	{
		p_print_default("%s\n", node->digest);

	} else {
		if (check_flag(node->local_flags, REVERSE) == true)
		{
			p_print_default("%s", node->digest);
			p_print_default(" \"%s\"", node->input);

		} else {
			p_print_default("%s(\"%s\")= ", hash_name, node->input);
			p_print_default("%s\n", node->digest);
		}
	}
}

static void	select_output(const t_hash *node, const char *hash_name)
{
	switch (node->input_type)
	{
	case STDIN:
		print_stdin_output(node, hash_name);
		break;

	case INFILE:
		print_file_output(node, hash_name);
		break;

	case STRING:
		print_string_output(node, hash_name);
		break;
	}
}

void	print_hash_list_digests(const t_ssl *ssl)
{
	t_hash	*node = ssl->hash_list;

	while (node)
	{
		select_output(node, capitalized_hash_list[ssl->hash_type]);
		node = node->next;
	}
}
