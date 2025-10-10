SRC = true.c gnl.c
# INCLUDES = includes/

all:
	@cc -Wall -Werror -Wextra -g3 $(SRC)

clean:
	@rm -f a.out

fclean: clean
	@rm -f a.out

re: fclean all

cre:
	@clear
	@make re --no-print-directory

debug:
	cc -g3 -DDEBUG=0 $(SRC) -I$(INCLUDES)
