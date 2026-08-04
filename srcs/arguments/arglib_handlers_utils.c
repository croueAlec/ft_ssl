#include "ft_ssl.h"
#include "ft_arguments.h"

void free_arglib_node(cli_context *ctx)
{
	t_arguments *userdata = (t_arguments *)ctx->userdata;

	if (userdata) {
		if (userdata->str) {
			free(userdata->str);
		}
		free(userdata);
	}

	free(ctx);
}

void free_arglib_list(cli_context *ctx)
{
	cli_context *tmp = NULL;

	ctx = get_first_ctx_node(ctx);

	while (ctx && ctx->next) {
		tmp = ctx;
		ctx = ctx->next;
		free_arglib_node(tmp);
	}
}

cli_context *new_context(cli_context *current_ctx)
{
	cli_context *new = calloc(1, sizeof(cli_context));
	if (new == NULL)
		return (NULL);

	if (current_ctx != NULL) {
		current_ctx->next = new;
		new->prev = current_ctx;
	}

	new->userdata = calloc(1, sizeof(t_arguments));
	if (new->userdata == NULL)
		return (free(new), NULL);

	return (new);
}

cli_context *create_str_ctx_node(cli_context *ctx, char *str)
{
	cli_context *new = new_context(ctx);
	if (!new)
		return (NULL);

	t_arguments *userdata = new->userdata;

	userdata->str = strdup(str);
	if (userdata->str == NULL)
		return (free_arglib_node(ctx), NULL);

	return (new);
}
