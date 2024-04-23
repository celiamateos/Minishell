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
CFLAGS = -Werror -Wextra -Wall -g3
CCLANG = -lreadline 
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
progress := 2

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
	@printf "\r$(COLOR_GREEN)[$(COLOR_GREEN_N) %d%%%*.*s $(COLOR_GREEN)] $(COLOR_PURPLE_N)Minishell $(COLOR_PURPLE)Compiling 🛠️  😸$(COLOR_RESET)" $(progress) $(CHARS_LEN) $(CHARS)
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	$(eval progress=$(shell echo $$(($(progress) + 1))))
	$(call print_progress)


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