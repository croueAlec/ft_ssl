SRC = md5_algorithm.c md5_blocks_utils.c md5_blocks.c md5_constants.c ../libs/penelope/penelope.a
INCLUDES = includes/

all:
	cc -Wall -Werror -Wextra -g3 -DLOG_LEVEL=P_LOG_DEFAULT $(SRC) -I$(INCLUDES)

debug:
	cc -g3 -DLOG_LEVEL=P_LOG_DEBUG $(SRC) -I$(INCLUDES)

trace:
	cc -g3 -DLOG_LEVEL=P_LOG_TRACE $(SRC) -I$(INCLUDES)
