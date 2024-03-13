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
#ifndef MINISHELL2_H

# define MINISHELL2_H

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
# include <readline/rlstdc.h>
# include <signal.h>

# define CMD 0
# define CREATE_VAR 1
# define PIPE 2
# define OPER 3
# define PARENT_OP 4
# define PARENT_CL 5
# define HEREDOC 6
# define REDIR_IN 7
# define REDIR_OUT 8
# define APPEND_OUT 9
# define FN_ERROR 10
# define STRING 11

# define AND 21
# define OR 22
# define COUNT 10 //to check priunt2Dtree

# define D_QUOTES 34
# define S_QUOTES 39

# define COMANDNOTFOUND 101
# define PERMISSIONDENIED 102
# define NOSUCHFILEORDIRECTORY 103
# define STANDAR 104
# define ISDIRECTORY 105

// Declaración de la variable global para señalización... 
extern volatile sig_atomic_t	g_received_signal;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct s_token
{
	char		*value;
	char		**cmds;
	int			type;
	int			oper;
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
	char	*pwd;
	char	*oldpwd;
	char	*shlvl;	
	size_t	index;
	size_t	count;
	size_t	i;
}					t_env;

typedef struct s_shell_sack
{
	char			*line;
	char			*l_expanded;
	char			**split_line;
	int				pos;
	struct s_dlist	*token_list;
	struct s_tree	*tree_list;
	char			*cmd_rmquotes;
	int				new_pipes[2];
	int				old_pipes[2];
	int				redirs[2];
	int				heredoc;
	int				now_pid;
	int				last_pid;
	int				last_exit;
	int				history_fd;
	int				is_string;
	int				d_quotes;
	int				s_quotes;
	int				len_expand;
	char			**envp;
	int				pipe_wc;
	struct s_env	*env;
	struct s_token	token;
	int				oper_state;
}	t_shell_sack;

#endif