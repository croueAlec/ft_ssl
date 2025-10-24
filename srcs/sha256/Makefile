SRC =	main_sha256.c \
		sha256_algorithm.c \
		sha256_blocks_utils.c \
		sha256_blocks.c \
		sha256_constants.c \
		sha256_schedule_array.c \
		../../libs/penelope/penelope.a \
		../../libs/libft/libft.a
INCLUDES = .

all:
	cc -Wall -Werror -Wextra -g3 -DLOG_LEVEL=P_LOG_DEFAULT $(SRC) -I$(INCLUDES)

debug:
	cc -g3 -DLOG_LEVEL=P_LOG_DEBUG $(SRC) -I$(INCLUDES)

trace:
	cc -g3 -DLOG_LEVEL=P_LOG_TRACE $(SRC) -I$(INCLUDES)

info:
	cc -g3 -DLOG_LEVEL=P_LOG_INFO $(SRC) -I$(INCLUDES)
