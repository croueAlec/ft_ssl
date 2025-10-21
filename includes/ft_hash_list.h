#ifndef FT_HASH_LIST_H
# define FT_HASH_LIST_H

#include "ft_ssl.h"

/* When adding a new hash :
- add the ENABLE_* rule here as well as in the makefile. The value should be the previous index + 1
- add the hash name in the enum and the main.c file string array hash_list at the correct index
- add the hash comparison in the set_hash_type function in the main.c file
- increment MAX_HASH_NBR
- add your hash to the COMMAND_LIST to print the correct program usage on invalid command
*/

#if(ENABLE_MD5 == true)
# define MD5_index 1
#else
# define MD5_index 0
#endif

#if(ENABLE_SHA256 == true)
# define SHA256_index 2
#else
# define SHA256_index 0
#endif

#define MAX_HASH_NBR 2 +2 // Always add +2 to the hash_number to account for INVALID and the NULL terminating
typedef void	(*hash_func_array)(t_hash*);
typedef enum	e_hash_types
{
	INVALID = 0,
	MD5	= MD5_index,
	SHA256	= SHA256_index
}		t_hash_type;

#define COMMAND_LIST "Commands:\nmd5\nsha256\n"

#endif
