#                                      ___               __
#                                     / _ \___ ___  ___ / /__  ___  ___
#                                    / ___/ -_) _ \/ -_) / _ \/ _ \/ -_)
#                                   /_/   \__/_//_/\__/_/\___/ .__/\__/
#                                   by: acroue              /_/

SRCS =	penelope_tools.c \
		penelope.c

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Objs
OBJDIR = objs
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

# Info
NAME = penelope.a
RM = rm -rf

all: ${NAME}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@${RM} ${OBJDIR}

fclean: clean
	@${RM} ${NAME}

re: fclean all

${NAME} : ${OBJS}
	@ar rcs ${NAME} ${OBJS}
