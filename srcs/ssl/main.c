#include "ft_ssl.h"

t_penelope_log_level P_LOG_LEVEL = LOG_LEVEL;

const t_hash_pattern hash_commands[] = {
	{"Invalid",	INVALID,	 NULL	 },
	{"md5",		MD5,		 md5		},
	{"sha256",	   SHA256,	   sha256	 },
#ifdef BONUS	 /* v bonus hash commands v */
	{"whirlpool", WHIRLPOOL, whirlpool},
#endif
	{"",		  INVALID,	  NULL	  }
};

const size_t max_hash_nbr = (sizeof(hash_commands) / sizeof(hash_commands[0]));

t_hash_type set_hash_type(const char *cmd)
{
	t_hash_type type = INVALID;
	if (!cmd)
		return (print_usage(), INVALID);

	for (size_t i = 1; i < max_hash_nbr; i++) {
		if (strcmp(cmd, hash_commands[type + i].name) == 0) {
			type = type + i;
			break;
		}
	}

	if (type == INVALID)
		error_unavailable_hash(cmd);
	return (type);
}

int main(int argc, char *argv[])
{

	t_ssl ssl = {0};

	return (arglib_api(&ssl, (size_t)argc - 1, &argv[1]));

	// ssl.hash_type = set_hash_type(argv[1]);
	// if (ssl.hash_type == INVALID)
	// 	return (1);

	// if (parse_arguments(&ssl, ((const char **)&argv[2])) == ERROR) {
	// 	if (ssl.error_status != 1)
	// 		p_print_fatal("ft_ssl: Fatal error: malloc() failed\n");
	// 	ssl.error_status = 1;
	// 	free_hash_list(&ssl);

	// 	return (ssl.error_status);
	// }

	print_hash_list(&ssl);

	execution(&ssl);

	print_hash_list_digests(&ssl);

	free_hash_list(&ssl);

	(void)argc;

	return (ssl.error_status);
}
