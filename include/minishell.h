/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:09:14 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/19 20:47:52 by daviles-         ###   ########.fr       */
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
# define OPER 2
# define HEREDOC 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define APPEND_OUT 6

# define COUNT 10 //to check priunt2Dtree

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

typedef struct s_env
{
	char	**pre_export; //Export list
	char	**env; //El enviroment
	size_t	env_elements;
	size_t	pre_export_elements;
	char	*order; //print_cmd_export. Falta incluir fd para pipex
	size_t		index;
	size_t	count;
	size_t		i;
}					t_env;

typedef struct s_shell_sack
{
	char			*line;
	char			*l_expanded;
	struct s_dlist	*token_list;
	struct s_tree	*tree_list;
	int				last_exit;
	int				history_fd;
	char			**envp; //Usar t_env *env en su lugar
	struct s_env			*env; //Usar t_env *env en su lugar
}	t_shell_sack;

int		main(int ac, char **av, char **envp);
//ENVIROMENT
int	init_env(char **envp, t_env *env);

void export(t_env *env, char *new);
char **realloc_export_exchange(t_env *env, char *new, size_t pos);
char **realloc_export_add(t_env *env, char *new);
int is_valid_to_export(char *s);
int	search_env_pos(char **env, char *word, char limit);
char **realloc_unset_pre_export_list(t_env *env, size_t pos);
char **realloc_add_pre_export_list(t_env *env, char *line);
void pre_export_new_variable(t_env *env, char *line);
void    print_export_list(t_env *env);
void 	already_added_pre_export_list(t_env *env, char *new, long pos);
int unset(t_env *env, char *del, int check);
char **realloc_unset(t_env *env, size_t pos);

//PWD
void    get_pwd(void);


void ft_free_env(char **env);
void	ft_free_error_arr(char **mem, long i);
void print_env(char **env);
size_t ft_arraylen(char **array);

//FUNCIONES LISTAS
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist *ft_dlstfirst(t_dlist *lst);
int		ft_dlstsize(t_dlist *lst);

// init_sack
int	clean_init(t_shell_sack **sack);
void	init_sack(t_shell_sack *sack, char *line, char **envp);
char	*expand_line(char *line, char **envp);
char	*expand_var(char *line, int i, char **envp);
char	*get_varname(char *expanded, int i);
// init_tokens
t_dlist	*lexer(char *line);
t_dlist	*init_tokens(char *line);
void	*get_next_token(char *line, int *i);
int		ft_isoperator(char	c, int *quotes);
int		get_token_type(char *value);
// token_utils
void	print_next(t_dlist **tokens);
void	print_prev(t_dlist **tokens);
void	print_tokenlist(t_dlist *list);
void	print_token(char *msj, t_token	*token);
// init_tree
void    init_tree(t_shell_sack **sack);
void	insert_leaf(t_tree **tree, t_dlist **token_list, t_dlist *token_end);
t_tree  *new_leaf(t_token *token);
// init_tree
void	leaf_iscmd(t_tree ***root, t_dlist *token_list);
void	leaf_ispipe(t_tree ***root, t_dlist *token_list);
void	leaf_isredirect(t_tree ***root, t_dlist *token_list);
void	leaf_isoper(t_tree ***root, t_dlist *token_list);

// tree_utils
void 	print_preorder(t_tree *node);
void	print2D(t_tree* root);
void	print2DUtil(t_tree *root, int space);

#endif
