/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:09:14 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/10 15:11:40 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h> 
# include <stdlib.h> 
# include <fcntl.h>
# include <stdarg.h> 
# include <limits.h> 
# include <sys/wait.h> 
# include "../libft/libft.h" 
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD 0
# define PIPE 1
# define REDIR 2
# define OPER 3

typedef struct s_dlist
{
	void		*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct s_token
{
	char		*value;
	char		**cmds;
	int			type;
}					t_token;

typedef struct s_tree
{
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_token	*content;
}	t_tree;

typedef struct s_shell_sack
{
	char			*line;
	char			*l_expanded;
	struct s_dlist	*token_list;
	struct s_tree	*tree_list;
	int				last_exit;
	int				history_fd;
	char			**envp;
}	t_shell_sack;


//FUNCIONES LISTAS
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist *ft_dlstfirst(t_dlist *lst);
int		ft_dlstsize(t_dlist *lst);

// utils
void	print_next(t_dlist **tokens);
void	print_prev(t_dlist **tokens);
void	print_tokenlist(t_dlist *list);
// init_sack
void	clean_init(t_shell_sack *sack);
void	init_sack(t_shell_sack *sack, char *line, char **envp);
char	*expand_line(char *line, char **envp);
char	*expand_var(char *line, int i, char **envp);
char	*get_varname(char *expanded, int i);
// init_tokens
t_dlist	*lexer(char *line);
t_dlist	*init_tokens(char *line);
void	*get_next_token(char *line, int *i);
int		ft_isoperator(char	c);
int		get_token_type(char *value);
#endif
