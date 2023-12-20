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

#include "minishell2.h"

//ENVIROMENT
int	init_env(char **envp, t_env *env);
int export(t_env *env, char *new);
char **realloc_export_exchange(t_env *env, char *new, size_t pos);
char **realloc_export_add(t_env *env, char *new);
int is_valid_to_export(char *s);
int	search_env_pos(char **env, char *word, char limit);
char **realloc_unset_pre_export_list(t_env *env, size_t pos);
char **realloc_add_pre_export_list(t_env *env, char *line);
void pre_export_new_variable(t_env *env, char *line);
void    print_export_list(t_env *env);
int 	already_added_pre_export_list(t_env *env, char *new, long pos);
int		unset(t_env *env, char *del, int check);
char 	**realloc_unset(t_env *env, size_t pos);
size_t 	ft_arraylen(char **array);
void    ft_free_env(char **env);
int    print_env(char **env);

//BUILTINS
int    get_pwd(void);
int    cd(t_shell_sack *sack, char *pathname);
int     cmd_echo(t_shell_sack ****sack_orig, char *line);
void	ft_free_error_arr(char **mem, long i);
int     check_isbuiltin(t_shell_sack **sack, t_tree *node);
int  execute_builtin(t_shell_sack ***sack, t_tree *node);


//FUNCIONES LISTAS
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist *ft_dlstfirst(t_dlist *lst);
int		ft_dlstsize(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst, void (*del_dlst)(void *));
void	ft_dlstdelone(t_dlist *lst, void (*del_dlst)(void *));
void	del_dlst(void *content);

// Clean exit
void	ft_free_pruebas(t_shell_sack **sack);
void	ft_clearenv(t_shell_sack *sack);
void    free_token(void *content);
void    free_sack(t_shell_sack **sack);
void    free_tree(t_tree **node);
void	perror_free_exit(char *msj, t_shell_sack ***sack); //error handling

// init_sack
int	clean_init(t_shell_sack **sack);
int sack_init(t_shell_sack *sack, char *line);
// char	*expand_line(char *line, char **envp);
// char	*expand_var(char *line, int i, char **envp);
// char	*get_varname(char *expanded, int i);

// init_tokens
t_dlist	*init_tokens(char *line);
void	*get_next_token(char *line, int *i);
int		ft_isoperator(char	c, int *quotes);
int		get_token_type(char *value);

// token_utils
void	print_tokenlist(t_dlist *list);
void	print_token(char *msj, t_token	*token);
void	print_token_args(t_dlist *token_list);
int		check_emptyorspace(char *str);
void	save_redir_filename(char *line, int *i);
void	get_cmd_args(t_shell_sack **sack);
void 	*get_last_cmd(t_dlist **token_list);
char	*fix_tokenvalues(char **value);
void	ft_cpypipes(int *old_pipe, int *new_pipe);
int     valid_varname(char *value, int *i);
int	valid_varformat(char *value, int *i);
int	isvalid_var(char *value);

// init_tree
void    init_tree(t_shell_sack **sack);
void	insert_leaf(t_tree **tree, t_dlist **token_list);
t_tree  *new_leaf(t_token *token);
// init_tree
void	leaf_iscmd(t_tree ***root, t_dlist *token_list);
void	leaf_isredirect(t_tree ***root, t_dlist *token_list);
void	leaf_isoperpipe(t_tree ***root, t_dlist *token_list);
void	leaf_isparenthesis_cl(t_tree ***root, t_dlist *token_list);
void	leaf_isparenthesis_op(t_tree ***root, t_dlist *token_list);
// tree_utils
void 	print_preorder(t_tree *node);
void	print2D(t_tree* root);
void	print2DUtil(t_tree *root, int space);
// execute
void	execute(t_shell_sack **sack);
void    run_preorder(t_tree *node, t_shell_sack **sack);
void    run_node(t_shell_sack **sack, t_tree **node);
void    run_cmd(t_shell_sack ***sack_orig, t_tree *node);
void    run_pipe(t_shell_sack ***sack_orig, t_tree *node);

void    run_oper(t_shell_sack ***sack_orig, t_tree *node);
// execute_utils
void	ft_close(int fd1, int fd2);
int 	check_redirect(t_shell_sack ***sack, t_tree *node);
int     open_redirect(t_shell_sack ****sack_orig, t_tree *node);
void    ft_heredoc(t_shell_sack *****sack_orig, char *eof);
t_tree *findnext_cmdleaf(t_tree **node);
int		check_opercondition(t_shell_sack **sack, t_tree **node);
// cmd_utils from pipex
int		check_route(char *av);
int		check_path(char **env);
char	*get_path(char *cmd, char **env);
char	*getcmd_withpath(char *cmd, char **cmds, char **env);

// main_utils 
int		wait_exitcode(int last_pid);
int	read_exit(char *line); //Change to builtin exit

//parse

//expander
char    *remove_quotes(char *old, char c);
int     expand_line(t_shell_sack *sack);
char *expand_dolar(t_shell_sack *sack, char *old, int i);
int	    expand_quotes(t_shell_sack *sack);
int     check_errors_initsack(t_shell_sack *sack);
void    check_open_quotes(t_shell_sack *sack, char *s);
int	    search_char(char *s, char c, int i);
char    *get_varcontent(char *var);

// signals
void    main_sig_handler(void);
void    sigint_handler(int signum);
void    heredoc_sig_handler(void);

#endif
