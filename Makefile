# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 17:06:22 by cmateos-          #+#    #+#              #
#    Updated: 2023/11/08 22:32:46 by daviles-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RESET = \x1b[0m
COLOR_RED = \x1b[0;31m
COLOR_RED_N = \x1b[1;31m
COLOR_GREEN = \x1b[1;32m
COLOR_YELLOW = \x1b[1;33m
COLOR_BLUE = \x1b[1;34m
COLOR_MAGENTA = \x1b[1;35m
COLOR_CYAN = \x1b[0;36m
BLANCO_T = \x1b[37m
BLANCO_F = \x1b[47m
MAGENTA = \033[0;95m
BROWN =	\033[0;38;2;184;143;29m
PURPLE = \x1b[1;35m


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CCLANG = -lreadline
RM = rm -f
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, main.c parse.c ft_double_list.c enviroment.c \
	  init_tokens.c enviroment_utils.c unset.c export.c)

OBJ = $(SRC:.c=.o)
INCLUDE = include/minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJ) $(CCLANG) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "${COLOR_BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(COLOR_YELLOW)$<"
	@make -C $(LIBFT_DIR)
	@echo "$(COLOR_GREEN) Created libft $(COLOR_RESET)"

%.o: %.c
	@echo "${BLANCO_T} ◎ $(BROWN)Compiling 🛠️  ${MAGENTA}→   $(COLOR_CYAN)$< $(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(COLOR_BLUE) Created! 😸 $(COLOR_RESET)"

clean:
	@rm -f $(OBJ) $(LIBFT)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(COLOR_RED_N) Cleaned all! 🧹 $(COLOR_RESET)"

normi:
	norminette

re: fclean all

.PHONY: all, clean, fclean, re
