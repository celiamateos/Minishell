# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 16:56:46 by cmateos-          #+#    #+#              #
#    Updated: 2024/01/05 16:56:48 by cmateos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# MAKEFILE CON BARRA Y COMPILANDO TO LO QUE SE LE PONE POR DELANTE
# Colors
COLOR_RESET = \033[0m
COLOR_RED = \033[0;31m
COLOR_RED_N = \033[1;31m
COLOR_GREEN = \033[0;32m
COLOR_GREEN_N = \033[1;32m
COLOR_YELLOW = \033[0;33m
COLOR_YELLOW_N = \033[1;33m
COLOR_BLUE = \033[0;34m
COLOR_BLUE_N = \033[1;34m
COLOR_PURPLE = \033[0;35m
COLOR_PURPLE_N = \033[1;35m

NAME = minishell
CC = gcc
CFLAGS = -g3 #-Werror -Wextra -Wall
#-g3 -fsanitize=address 
#Pa detectar leaks y movidas: valgrind --leak-check=full ./minishell
CCLANG = -lreadline 
#Esta mierda creo que hace falta pa -lreadline en 42
RM = rm -f
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
SRC_DIR = src
OBJ_DIR = obj
INCLUDE = include/minishell.h include/minishell2.h
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
CHANGES_MADE = 0
CHARS_LEN := 0
CHARS := 0
progress := 4

all: $(NAME)
	@if [ "$(CHANGES_MADE)" -eq "0" ]; then \
		echo "$(COLOR_RED)No hay cambios para hacer. $(COLOR_RESET)"; \
	fi
	$(call print_progress)
	$(eval progress := 50)
	$(call print_progress)
	$(eval progress := 100)
	$(call print_progress)
	@echo ""

$(NAME):$(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) $(CCLANG) $(LIBFT) -o $(NAME)
	@$(eval CHANGES_MADE=1)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null

define print_progress
	@printf "\r$(COLOR_GREEN)[$(COLOR_GREEN_N) %d%%%*.*s $(COLOR_GREEN)] $(COLOR_PURPLE_N)Minishell $(COLOR_PURPLE)Compiling 🛠️$(COLOR_RESET)" $(progress) $(CHARS_LEN) $(CHARS)
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	$(eval progress=$(shell echo $$(($(progress) + 3))))
	$(call print_progress)
# @echo "$(COLOR_BLUE) Created! 😸 $(COLOR_RESET)"

clean:
	@rm -rf $(OBJ_DIR) $(LIBFT) > /dev/null
	@make clean -C $(LIBFT_DIR) > /dev/null

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@echo "$(COLOR_RED_N) Cleaned all! 🧹 $(COLOR_RESET)"

normi:
	norminette

re: fclean all

.PHONY: all, clean, fclean, re


# #MAKEFILE NORMAL: 
# COLOR_RESET = \x1b[0m
# COLOR_RED = \x1b[0;31m
# COLOR_RED_N = \x1b[1;31m
# COLOR_GREEN = \x1b[1;32m
# COLOR_YELLOW = \x1b[1;33m
# COLOR_BLUE = \x1b[1;34m
# COLOR_MAGENTA = \x1b[1;35m
# COLOR_CYAN = \x1b[0;36m
# BLANCO_T = \x1b[37m
# BLANCO_F = \x1b[47m
# MAGENTA = \033[0;95m
# BROWN =	\033[0;38;2;184;143;29m
# PURPLE = \x1b[1;35m


# NAME = minishell
# CC = gcc
# CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address
# CCLANG = -lreadline
# RM = rm -f
# LIBFT_DIR = libft/
# LIBFT = $(LIBFT_DIR)libft.a

# SRC_DIR = src

# SRC = $(addprefix $(SRC_DIR)/, main/main.c main/clean_exit.c main/exitcode.c \
# 	parse/parse.c parse/parse_utils.c \
# 	expander/expander_dolar.c expander/expander_init.c expander/expander_quotes.c \
# 	expander/expander_wildcard.c \
# 	token_and_tree/tokens_init.c token_and_tree/tree_init.c \
# 	token_and_tree/ft_double_list.c token_and_tree/is_validvar_tokens.c \
# 	token_and_tree/print_tokens.c token_and_tree/print_tree.c token_and_tree/tokens_utils.c \
# 	execute/execute.c execute/execute_utils.c execute/path.c \
# 	builtin/cd.c builtin/cd_utils.c builtin/check_isbuiltin.c builtin/echo.c \
# 	builtin/enviroment.c builtin/enviroment_utils.c builtin/exit.c builtin/export.c \
# 	builtin/pre_export.c builtin/print_export_list.c builtin/pwd.c builtin/unset.c \
# 	signals/signals.c)



# OBJ = $(SRC:.c=.o)
# INCLUDE = include/minishell.h include/minishell2.h

# all: $(NAME)

# $(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
# 	$(CC) $(CFLAGS) $(OBJ) $(CCLANG) $(LIBFT) -o $(NAME)

# $(LIBFT):
# 	@echo "${COLOR_BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(COLOR_YELLOW)$<"
# 	@make -C $(LIBFT_DIR)
# 	@echo "$(COLOR_GREEN) Created libft $(COLOR_RESET)"

# %.o: %.c
# 	@echo "${BLANCO_T} ◎ $(BROWN)Compiling 🛠️  ${MAGENTA}→   $(COLOR_CYAN)$< $(COLOR_RESET)"
# 	@$(CC) $(CFLAGS) -c -o $@ $<
# 	@echo "$(COLOR_BLUE) Created! 😸 $(COLOR_RESET)"

# clean:
# 	@rm -f $(OBJ) $(LIBFT)
# 	@make clean -C $(LIBFT_DIR)

# fclean: clean
# 	@rm -f $(NAME)
# 	@make fclean -C $(LIBFT_DIR)
# 	@echo "$(COLOR_RED_N) Cleaned all! 🧹 $(COLOR_RESET)"

# normi:
# 	norminette

# re: fclean all

# .PHONY: all, clean, fclean, re
