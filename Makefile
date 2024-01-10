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
CFLAGS = -g3 #-fsanitize=address #-Werror -Wextra -Wall
CCLANG = -lreadline #-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib
#Pa detectar leaks y movidas: valgrind --leak-check=full ./minishell
RM = rm -f
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC_DIR = src
OBJ_DIR = obj

SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

INCLUDE = include/minishell.h include/minishell2.h

# all: $(NAME)

$(NAME):$(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) $(CCLANG) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)



CHARS_LEN := 0
CHARS := 0
progress := 4

define print_progress
	@printf "\r$(COLOR_GREEN)[$(COLOR_GREEN_N) %d%%%*.*s $(COLOR_GREEN)] $(COLOR_PURPLE_N)Minishell $(COLOR_PURPLE)Compiling 🛠️$(COLOR_RESET)" $(progress) $(CHARS_LEN) $(CHARS)
endef

# Ejemplo de uso
all:
	$(call print_progress)
	$(eval progress := 50)
	$(call print_progress)
	$(eval progress := 100)
	$(call print_progress)
	@echo ""


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	$(eval progress=$(shell echo $$(($(progress) + 3))))
	$(call print_progress)

# @echo "$(COLOR_BLUE) Created! 😸 $(COLOR_RESET)"

clean:
	@rm -rf $(OBJ_DIR) $(LIBFT)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(COLOR_RED_N) Cleaned all! 🧹 $(COLOR_RESET)"

normi:
	norminette

re: fclean all

.PHONY: all, clean, fclean, re
