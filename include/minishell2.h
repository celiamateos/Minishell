/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:45:13 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/06 00:45:15 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_FUN_H

# define MINISHELL_FUN_H

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
# define PARENT_OP 3
# define PARENT_CL 4
# define HEREDOC 5
# define REDIR_IN 6
# define REDIR_OUT 7
# define APPEND_OUT 8
# define FN_ERROR 9

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
	size_t	index;
	size_t	count;
	size_t	i;
}					t_env;

typedef struct s_shell_sack
{
	char			*line;
	char			*l_expanded;
	struct s_dlist	*token_list;
	struct s_tree	*tree_list;
	int				new_pipes[2];
	int				old_pipes[2];
	int				redirs[2];
	t_token			*last_token;
	int				last_pid;
	int				last_exit;
	int				history_fd;
	char			**envp; 
	struct s_env	*env;
}	t_shell_sack;

#endif