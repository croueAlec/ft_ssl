#include "ft_ssl.h"
#include "ft_arguments.h"

void print_userdata(cli_context *list)
{
	if (!list)
		return ((void)printf("no list created, exiting\n"));

	t_arguments args = {0};

	printf("hash: [%s]\n", ((t_arguments *)list->userdata)->str);

	int nbr_p = 0;
	list = list->next;
	do {
		if (!list)
			return;
		t_arguments *userdata = list->userdata;
		if (userdata->str)
			printf("input %s\n", userdata->str);

		nbr_p += userdata->flag_print_stdin;
		args.flag_quiet ^= userdata->flag_quiet;
		args.flag_reverse ^= userdata->flag_reverse;

		list = list->next;
	} while (list);

	if (nbr_p != 0)
		printf("-p enabled %d\n", nbr_p);
	if (args.flag_quiet)
		printf("-q enabled\n");
	if (args.flag_reverse)
		printf("-r enabled\n");
}

void interpret_arguments(t_ssl *ssl, cli_context *list)
{
	t_arguments *userdata = (t_arguments *)list->userdata;

	ssl->hash_type = set_hash_type(userdata->str);
	if (ssl->hash_type == INVALID)
		return; // error invalid command

	list = list->next;
	bool expect_string = false;
	bool filenames_only = false;
	while (list) {
		userdata = (t_arguments *)list->userdata;

		if (filenames_only == true) {
			add_hash_node(INFILE, ssl, NULL, userdata->str);
			continue;
		}

		if (userdata->flag_print_stdin == true) {
			ssl->general_flags += ECHO;
			add_hash_node(STDIN, ssl, NULL, NULL);
			continue;

		} else if (userdata->flag_quiet == true) {
			ssl->general_flags += QUIET;

		} else if (userdata->flag_reverse == true) {
			ssl->general_flags += REVERSE;

		} else if (userdata->flag_str == true) {
			if (userdata->str == NULL) {
				expect_string = true;
			} else if (expect_string == true) {
				expect_string = false;
				add_hash_node(STRING, ssl, userdata->str, NULL);
				continue;
			} else {
				filenames_only = true;
				add_hash_node(INFILE, ssl, NULL, userdata->str);
				continue;
			}
		}
	};

	(void)ssl;
	(void)list;
}

bool arglib_api(t_ssl *ssl, size_t argument_count, char **arguments)
{
	const char *cli_flags_error_message = is_cli_flag_handler_valid(flags);
	if (cli_flags_error_message != NULL) {
		printf("%s\n", cli_flags_error_message);
		return (1);
	}

	cli_context *list = NULL;

	list = arglib(argument_count, arguments);
	if (list != (cli_context *)0x1) {
		printf("list created : %p\n", list);
		print_userdata(list);

		interpret_arguments(ssl, list);
		return false;
	} else {
		printf("no arguments, exiting\n");
		return true;
	}
}

const cli_flag_config flag_config = {true, false};

const cli_flag_handler flags[] = {
	{{'p', "", NO_FLAG_ARG, "echo STDIN to STDOUT and append the checksum to STDOUT"}, flag_print_stdin_handle		  },
	{{'q', "", NO_FLAG_ARG, "quiet mode"},											 flag_quiet_handle				},
	{{'r', "", NO_FLAG_ARG, "reverse the format of the output"},						 flag_reverse_handle				},
	{{'s', "", MANDATORY_FLAG_ARG, "print the sum of the given string"},				 flag_str_handle					},
	{{'\0', "", STR_FLAG_ARG, ""},													 flag_default_string_option_handle},
	{{0, NULL, 0, NULL},															   NULL							 }
};
