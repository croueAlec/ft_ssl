SRC = md5_algorithm.c md5_blocks_utils.c md5_blocks.c md5_constants.c
INCLUDES = includes/

all:
	cc -Wall -Werror -Wextra -g3 $(SRC) -I$(INCLUDES)

debug:
	cc -g3 -DDEBUG=0 $(SRC) -I$(INCLUDES)
