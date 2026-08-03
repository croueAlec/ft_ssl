#ifndef FT_HASH_LIST_H
#define FT_HASH_LIST_H

#include "ft_ssl.h"

/* When adding a new hash :
- add the hash name in the enum and the main.c file string array hash_list at the correct index
- add the hash comparison in the set_hash_type function in the main.c file
- add your hash to the hash_func_array in execution.c
- add your hash to the COMMAND_LIST to print the correct program usage on invalid command
- in case of a bonus hash, put it in the ifdef check. The enum does not need an ifdef

- The hash_list array, t_hash_type enum, and hash_func_array array's order MUST match
*/

typedef struct hashes t_hash;

typedef void (*hash_func_array)(t_hash *);

extern const hash_func_array algorithm[];
extern const size_t			 max_hash_nbr;

typedef enum e_hash_types
{
	INVALID = 0,
	MD5 = 1,
	SHA256 = 2,
	WHIRLPOOL = 3,
} t_hash_type;

#define COMMAND_LIST "Commands:\nmd5\nsha256\n"

#endif
