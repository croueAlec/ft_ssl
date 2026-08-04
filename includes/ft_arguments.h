#ifndef FT_ARGUMENTS_H
#	define FT_ARGUMENTS_H

#	include "ft_ssl.h"

#	include "../libs/arglib/arglib.h"

typedef struct cli_userdata
{
	bool flag_print_stdin;
	bool flag_quiet;
	bool flag_reverse;
	bool flag_str;
	bool flag_cut_str;

	char *str;
} t_arguments;

/*			main.c						*/

t_hash_type set_hash_type(const char *cmd);

/*			arglib_handlers_utils.c		*/

void		 free_arglib_node(cli_context *ctx);
void		 free_arglib_list(cli_context *ctx);
cli_context *new_context(cli_context *current_ctx);
cli_context *create_str_ctx_node(cli_context *ctx, char *str);

/*			arglib_handlers.c			*/

cli_context *flag_print_stdin_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag);
cli_context *flag_quiet_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag);
cli_context *flag_reverse_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag);
cli_context *flag_str_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag);
cli_context *flag_default_string_option_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_double_dash);

/*			arglib_user_utils.c			*/

const char			 *is_cli_flag_handler_valid(const cli_flag_handler *flags);
bool				  set_double_dash_separator();
size_t				  get_flag_list_length();
cli_context			 *get_first_ctx_node(cli_context *ctx);
flag_handler_function get_str_flag_handler(size_t flag_list_length);

#endif

/*
 -p, echo STDIN to STDOUT and append the checksum to STDOUT
• -q, quiet mode
• -r, reverse the format of the output.
• -s, print the sum of the given string
 */
