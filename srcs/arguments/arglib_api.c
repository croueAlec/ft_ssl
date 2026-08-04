#include "ft_ssl.h"
#include "ft_arguments.h"

void print_userdata(cli_context *list)
{
	if (!list)
		return ((void)printf("no list created, exiting\n"));

	do {
		t_arguments *userdata = list->userdata;
		printf("\tprint stdin: %d\tquiet: %d\treverse: %d\tstr: [%s]\tcut str: %d\n", userdata->flag_print_stdin, userdata->flag_quiet, userdata->flag_reverse, userdata->str, userdata->flag_cut_str);
		list = list->next;
	} while (list);
}

bool arglib_api(size_t argument_count, char **arguments)
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
		return true;
	} else {
		printf("no arguments, exiting\n");
		return false;
	}
}

const cli_flag_config flag_config = {true, true};

const cli_flag_handler flags[] = {
	{{'p', "", NO_FLAG_ARG, "echo STDIN to STDOUT and append the checksum to STDOUT"}, flag_print_stdin_handle		  },
	{{'q', "", NO_FLAG_ARG, "quiet mode"},											 flag_quiet_handle				},
	{{'r', "", NO_FLAG_ARG, "reverse the format of the output"},						 flag_reverse_handle				},
	{{'s', "", MANDATORY_FLAG_ARG, "print the sum of the given string"},				 flag_str_handle					},
	{{'\0', "", STR_FLAG_ARG, ""},													 flag_default_string_option_handle},
	{{0, NULL, 0, NULL},															   NULL							 }
};
