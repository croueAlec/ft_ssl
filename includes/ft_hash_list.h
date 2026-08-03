#ifndef FT_HASH_LIST_H
#define FT_HASH_LIST_H

#include "ft_ssl.h"

/* When adding a new hash :
- add the hash name in the enum and the main.c file string array hash_list at the correct index
- add the hash comparison in the set_hash_type function in the main.c file
- increment MAX_HASH_NBR
- add your hash to the COMMAND_LIST to print the correct program usage on invalid command
*/

typedef struct hashes t_hash;

typedef void (*hash_func_array)(t_hash *);

typedef enum e_hash_types
{
	INVALID = 0,
	MD5 = 1,
	SHA256 = 2,
	MAX_HASH_NBR
} t_hash_type;

#define COMMAND_LIST "Commands:\nmd5\nsha256\n"

#endif
