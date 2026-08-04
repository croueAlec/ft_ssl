#ifndef FT_HASH_LIST_H
#define FT_HASH_LIST_H

#include "ft_ssl.h"

/* When adding a new hash :
- add the hash name in the enum
- add the hash pattern in the hash_commands array in main.c
- the enum and hash_commands order MUST be identical
- the hash_commands array MUST start with Invalid and end with an empty string
- add your hash to the COMMAND_LIST at the bottom to print the correct program usage on invalid command
2- bonus hashes MUST be included in the 'bonus hash commands' parts of the enum, COMMAND_LIST, and hash_commands array
*/

typedef struct hashes t_hash;

typedef void (*hash_function)(t_hash *);

typedef enum e_hash_types
{
	INVALID = 0,
	MD5 = 1,
	SHA256 = 2,

	/* v bonus hash commands v */
	WHIRLPOOL = 3,
} t_hash_type;

typedef struct hash_pattern
{
	char		 *name;
	t_hash_type	  type;
	hash_function hash;
} t_hash_pattern;

extern const t_hash_pattern hash_commands[];
extern const size_t			max_hash_nbr;

#ifndef BONUS
#	define COMMAND_LIST "Commands:\nmd5\nsha256\n"
#else /* v bonus hash commands v */
#	define COMMAND_LIST "Commands:\nmd5\nsha256\nwhirlpool\n"
#endif

#endif
