SRC = test_message_digest.c hashing_message.c md5_constants.c
INCLUDES = includes/

all:
	cc -Wall -Werror -Wextra -g3 $(SRC) -I$(INCLUDES)

debug:
	cc -g3 -DDEBUG=0 $(SRC) -I$(INCLUDES)
