#	Program name
NAME = ft_ssl

#	Colors
DEFAULT    = \033[0m
BLACK    = \033[0;30m
RED        = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
BWHITE    = \033[1;37m

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEP_FLAGS = -MMD -MP
RM = rm -rf
LIB_FLAGS = --no-print-directory --silent

#	Directories
LIBS_DIR = libs
SRCS_DIR = srcs
INCS_DIR = includes
OBJS_DIR = objs
LIBFT_DIR = $(LIBS_DIR)/libft

#	Files
LIBFT = $(LIBFT_DIR)/libft.a

LIB :=	$(LIBFT)

INCLUDES := $(INCS_DIR) \
			$(LIBFT_DIR)

INCLUDES_FLAGS := $(addprefix -I , $(INCLUDES))

SRC :=	\
	errors.c \
	execution.c \
	get_message.c \
	hash_list.c \
	main.c \
	parsing.c

OBJ := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
DEPS := $(patsubst %.c,$(OBJS_DIR)/%.d,$(SRC))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES_FLAGS) -o $@

-include %(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(DEP_FLAGS) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

clean:
	@echo "$(RED)! Removing$(DEFAULT) ${OBJS_DIR} files"
	@${RM} ${OBJS_DIR}

fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

re: fclean all

cre:
	@clear
	@make re --no-print-directory

$(LIBFT):
	@echo "$(CYAN)~ Compiling$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) $(LIB_FLAGS)

cleanlib:
	@echo "$(RED)! Removing$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make clean -C $(LIBFT_DIR) $(LIB_FLAGS)

fcleanlib:
	@echo "$(RED)! Removing$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make fclean -C $(LIBFT_DIR) $(LIB_FLAGS)

relib: fcleanlib $(LIBFT)
