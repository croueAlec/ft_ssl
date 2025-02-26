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
	INFILE = 2
}	t_input_type;

typedef enum	e_flags
{
	NONE = 0b0,
	ECHO = 0b1,
	QUIET = 0b10,
	REVERSE = 0b100,
}				t_flags;

typedef struct hashes
{
	t_input_type	input_type;
	size_t			local_flags;
	char			*input;
	char			*file;
	struct hashes			*next;
}		t_hash;

#define MAX_HASH_NBR 2
typedef char	*(*hash_func_array)(t_hash*);
typedef enum	e_hash_types
{
	INVALID = 0,
	MD5	= 1,
	SHA256	= 2
}		t_hash_type;

typedef struct	ft_ssl
{
	t_hash_type	hash_type;
	size_t		general_flags;
	t_hash		*hash_list;
}		t_ssl;

/*			error.c			*/
void	print_usage(void);
void	error_invalid_cmd(const char *cmd);
bool	error_missing_string_argument(t_ssl *ssl);
/*			execution.c		*/
bool	execution(t_ssl *ssl);
/*			hash_list.c		*/
void	free_hash_list(t_ssl *ssl);
bool	add_hash_node(t_input_type type, t_ssl *ssl, char const *string, char const *filename);
/*			parsing.c		*/
bool	parse_arguments(t_ssl *ssl, char const *argv[]);

#endif
