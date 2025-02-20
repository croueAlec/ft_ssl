#include "ft_ssl.h"

t_hash_type	set_hash_type(const char *cmd)
{
	if (!cmd)
		return (INVALID);

	if (strcmp(cmd, "md5") == 0)
		return (MD5);

	if (strcmp(cmd, "sha256") == 0)
		return (SHA256);

	return (INVALID);
}

int main(__attribute__((unused)) int argc, char const *argv[])
{
	t_ssl	ssl = {0};

	ssl.hash_type = set_hash_type(argv[1]);
	printf("%d\n", ssl.hash_type);

	return 0;
}
