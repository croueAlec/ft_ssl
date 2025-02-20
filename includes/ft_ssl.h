#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ERROR 0
#define SUCCESS 1

typedef enum	e_input_types
{
	STDIN = 0,
	STRING = 1,
	FILE = 2
}	t_input_type;

typedef struct hashes
{
	t_input_type	input_type;
	char			*input;
	char			*file;
	t_hash			*next;
}		t_hash;

typedef enum	e_hash_types
{
	INVALID = 0,
	MD5	= 1,
	SHA256	= 2
}		t_hash_type;

typedef struct	ft_ssl
{
	t_hash_type	hash_type;
	bool		flag_echo;
	bool		flag_quiet;
	bool		flag_reverse;
}		t_ssl;

#endif
