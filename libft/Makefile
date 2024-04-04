# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daviles- <daviles-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 13:03:04 by cmateos-          #+#    #+#              #
#    Updated: 2023/11/21 21:34:14 by daviles-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -C -Wall -Wextra -Werror // error con -c en MAC
LIB = ar rc
SRC = ft_isalpha.c \
	  ft_isspace.c ft_strposchr.c ft_print_strarray.c ft_arrtostr.c \
	  ft_split_minishell.c  ft_split_minishell_utils.c \
	  ft_freematrix.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_strlen.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strncmp.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_calloc.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew_bonus.c \
	  ft_lstadd_front_bonus.c \
	  ft_lstsize_bonus.c \
	  ft_lstlast_bonus.c \
	  ft_lstdelone_bonus.c \
	  ft_lstclear_bonus.c \
	  ft_lstadd_back_bonus.c \
	  ft_lstiter_bonus.c \
	  ./ft_printf/ft_printf.c \
	  ./ft_printf/ft_putchr_pf.c \
	  ./ft_printf/ft_putstr_pf.c \
	  ./ft_printf/ft_putnbr_pf.c \
	  ./ft_printf/ft_putptr_pf.c \
	  ./ft_printf/ft_puthex.c \
	  ./ft_printf/ft_putun.c \
	  ./gnl-david/get_next_line.c \
	  ft_sarrlen.c \
	  ft_sarrcpy.c \
	  ft_sarradd.c \
	#   ./get_next_line/get_next_line.c \
	#   ./get_next_line/get_next_line_utils.c
SRC_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstiter_bonus.c 
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
PRINTF = printf

# SRC_COUNT_TOT := $(shell expr $(shell echo -n 50 | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
# ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
# 	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
# endif
# SRC_COUNT := 0
# SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIB) $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
# @$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
# @$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling libft $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
# @$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) $(CDEBUG) -c $< -o $@
clean:
	@rm -rdf $(OBJ)
	@rm -rdf $(OBJ_BONUS)

fclean: clean
	@rm -rdf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus
