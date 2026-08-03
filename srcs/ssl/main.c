#include "ft_ssl.h"

t_penelope_log_level P_LOG_LEVEL = LOG_LEVEL;

const char hash_list[8][16] = {
	"Invalid",
	"md5",
	"sha256",
#ifdef BONUS
	"whirlpool",
#endif
	"",
};

t_hash_type set_hash_type(const char *cmd)
{
	t_hash_type type = INVALID;
	if (!cmd)
		return (print_usage(), INVALID);

	if (strcmp(cmd, hash_list[MD5]) == 0) {
		type = MD5;
	} else if (strcmp(cmd, hash_list[SHA256]) == 0) {
		type = SHA256;
		printf("sha256\n");
	} else if (WHIRLPOOL < max_hash_nbr) {
		if (strcmp(cmd, hash_list[WHIRLPOOL])) {
			type = WHIRLPOOL;
		}
	} else {
		error_invalid_cmd(cmd);
		return (INVALID);
	}

	if (type >= max_hash_nbr)
		error_unavailable_hash(cmd);
	return (type);
}

void v()
{
	for (size_t i = 0; strlen(hash_list[i]) > 0; i++) {
		printf("%s\n", hash_list[i]);
	}
}

int main(__attribute__((unused)) int argc, const char *argv[])
{
	printf("%p %p %p\n", algorithm[0], algorithm[1], algorithm[2]);
	v();
	t_ssl ssl = {0};
	printf("%zu\n", max_hash_nbr);

	ssl.hash_type = set_hash_type(argv[1]);
	if (ssl.hash_type == INVALID)
		return (1);

	if (parse_arguments(&ssl, &argv[2]) == ERROR) {
		if (ssl.error_status != 1)
			p_print_fatal("ft_ssl: Fatal error: malloc() failed\n");
		ssl.error_status = 1;
		free_hash_list(&ssl);

		return (ssl.error_status);
	}

	print_hash_list(&ssl);

	execution(&ssl);

	print_hash_list_digests(&ssl);

	free_hash_list(&ssl);

	return (ssl.error_status);
}
