#                                      ___               __
#                                     / _ \___ ___  ___ / /__  ___  ___
#                                    / ___/ -_) _ \/ -_) / _ \/ _ \/ -_)
#                                   /_/   \__/_//_/\__/_/\___/ .__/\__/
#                                   by: acroue              /_/

SRCS =	penelope_tools.c \
		penelope.c

# Compilation
CC = cc
LOG_LVL=P_LOG_DEFAULT
CFLAGS = -Wall -Wextra -Werror -g3 -DP_LOG_LEVEL=$(LOG_LVL)

# Objs
OBJDIR = objs
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

# Info
NAME = penelope.a
RM = rm -rf

all: fclean ${NAME}

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

fatal: fclean
	@$(MAKE) LOG_LVL=P_LOG_FATAL --no-print-directory

error: fclean
	@$(MAKE) LOG_LVL=P_LOG_ERROR --no-print-directory

default: fclean
	@$(MAKE) LOG_LVL=P_LOG_DEFAULT --no-print-directory

info: fclean
	@$(MAKE) LOG_LVL=P_LOG_INFO --no-print-directory

debug: fclean
	@$(MAKE) LOG_LVL=P_LOG_DEBUG --no-print-directory

trace: fclean
	@$(MAKE) LOG_LVL=P_LOG_TRACE --no-print-directory
