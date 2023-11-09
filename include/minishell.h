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
	char **array;
	long	env_size;
	long	env_elements;
}					t_env;

int		main(int ac, char **av, char **envp);

//ENVIROMENT
int	init_env(char **envp, t_env *env);

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
