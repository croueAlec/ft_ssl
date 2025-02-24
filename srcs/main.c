#include "ft_ssl.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void print_hash_list(t_ssl *ssl)
{
	if (!ssl)
		return ;

	printf("Hash type : %d\n", ssl->hash_type);
	printf("General flags : "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(ssl->general_flags));
	printf("                     rqp\n");

	t_hash	*tmp = NULL;
	t_hash *node = ssl->hash_list;
	while (node)
	{
		tmp = node->next;
		printf("[\nInput type : %d\n", node->input_type);
		printf("Local flags : "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(node->local_flags));
		if (node->input)
			printf("Input: %s\n", node->input);
		if (node->file)
			printf("Filename: %s\n", node->file);
		printf("]\n");
		node = tmp;
	}
	printf("Debug end\n============================================\n");
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

int	main(__attribute__((unused)) int argc, char const *argv[])
{
	t_ssl	ssl = {0};

	ssl.hash_type = set_hash_type(argv[1]);
	printf("%d\n", ssl.hash_type);
	if (ssl.hash_type == 0)
		return (1);

	if (parse_arguments(&ssl, &argv[2]) == ERROR)
	{
		free_hash_list(&ssl);
		return (1);
	}

	print_hash_list(&ssl);

	return 0;
}
