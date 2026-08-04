#include "ft_ssl.h"
#include "ft_arguments.h"

cli_context *flag_print_stdin_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag)
{
	ctx = new_context(ctx);
	if (ctx == NULL)
		return (free_arglib_node(ctx), NULL);

	((t_arguments *)ctx->userdata)->flag_print_stdin = true;

	(void)clean_arg;
	(void)argv;
	(void)is_short_flag;
	return (ctx);
}

cli_context *flag_quiet_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag)
{
	ctx = new_context(ctx);
	if (ctx == NULL)
		return (free_arglib_node(ctx), NULL);

	((t_arguments *)ctx->userdata)->flag_quiet = true;

	(void)clean_arg;
	(void)argv;
	(void)is_short_flag;
	return (ctx);
}

cli_context *flag_reverse_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag)
{
	ctx = new_context(ctx);
	if (ctx == NULL)
		return (free_arglib_node(ctx), NULL);

	((t_arguments *)ctx->userdata)->flag_reverse = true;

	(void)clean_arg;
	(void)argv;
	(void)is_short_flag;
	return (ctx);
}

cli_context *flag_str_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_short_flag)
{
	ctx = new_context(ctx);
	if (ctx == NULL)
		return (free_arglib_node(ctx), NULL);

	((t_arguments *)ctx->userdata)->flag_str = true;

	(void)clean_arg;
	(void)argv;
	(void)is_short_flag;
	return (ctx);
}

cli_context *flag_default_string_option_handle(cli_context *ctx, char *clean_arg, char **argv, bool is_filename)
{
	ctx = create_str_ctx_node(ctx, clean_arg);
	if (ctx == NULL)
		return (free_arglib_node(ctx), NULL);

	((t_arguments *)ctx->userdata)->flag_str = true;
	((t_arguments *)ctx->userdata)->flag_cut_str = is_filename;

	(void)argv;
	return (ctx);
}
