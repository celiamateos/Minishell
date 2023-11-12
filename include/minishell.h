/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:09:14 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/08 22:31:19 by daviles-         ###   ########.fr       */
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

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
    struct s_token  *prev;
}					t_token;

typedef struct s_tree
{
	
}					t_tree;

typedef struct s_env
{
	char ***variables;
	char **array;
	size_t	env_elements;
}					t_env;

int		main(int ac, char **av, char **envp);

//ENVIROMENT
int	init_env(char **envp, t_env *env);

int export(t_env *env, char *new);
char **realloc_export_exchange(t_env *env, char *new, size_t pos);
char **realloc_export_add(t_env *env, char *new);
int is_valid_to_export(char *s);
int	search_env_pos(char **env, char *word, char limit);

int unset(t_env *env, char *del);
char **realloc_unset(t_env *env, size_t pos);

void ft_free_env(char **env);
void	ft_free_error_arr(char **mem, long i);
void print_env(char **env);
size_t ft_arraylen(char **array);

//FUNCIONES LISTAS
t_token	*ft_dlstnew(void *content);
void	ft_dlstadd_back(t_token **lst, t_token *new);
void	ft_dlstadd_front(t_token **lst, t_token *new);
t_token	*ft_dlstlast(t_token *lst);
t_token *ft_dlstfirst(t_token *lst);
int		ft_dlstsize(t_token *lst);

// parser
t_token	*init_tokens(char *line);
#endif
