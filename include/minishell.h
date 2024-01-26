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


/* ---------------------- MAIN AND EXIT------------------------*/
int sack_init(t_shell_sack *sack, char *line);

/* ---------------------- PARSE ------------------------*/
int     check_errors_initsack(t_shell_sack *sack);
int     check_open_quotes(char *s);
int check_errors_opers(t_dlist *list);



/* ---------------------- EXPANDER ------------------------*/
char    *remove_quotes(char *old, char c);
int     expand_line(t_shell_sack *sack);
char    *expand_dolar(t_shell_sack *sack, char *old, int i);
int	check_expand_dolar(char *old, int i);
// int	    expand_quotes(t_shell_sack *sack);
char *get_varname(t_shell_sack *sack, char *old);

int	    search_char(char *s, char c, int i);
char    *get_varcontent(char *var);
// char    *expand_wildcard(t_shell_sack *sack, char *old, int i);
char    *remove_quotes_cmd(char *s);
void	remove_quotes_arr_cmds(t_token *token, t_shell_sack **sack);

// signals
void    main_sig_handler(void);
// void    sigint_handler(int signum);
// void    heredoc_sig_handler(void);

/* ---------------------- TOKENS AND TREE------------------------*/
t_dlist	*init_tokens(char *line);
void    init_tree(t_shell_sack **sack);

//tokens_utils.c
void	save_redir_filename(char *line, int *i);
void	get_cmd_args(t_shell_sack **sack);
void 	*get_last_cmd(t_dlist **token_list);
char	*fix_tokenvalues(char **value);
void	ft_cpypipes(int *old_pipe, int *new_pipe);

//isvalid_var_tokens.c 
// A estas funciones solamente las llamas en tokens_init.c:35 y está comentado.
//Si no se va a usar borrar archivo
int     valid_varname(char *value, int *i);
int	    valid_varformat(char *value, int *i);
int	    isvalid_var(char *value);

//print_tokens.c
void	print_tokenlist(t_dlist *list);
void	print_token(char *msj, t_token	*token);
void	print_token_args(t_dlist *token_list);
// print_tree.c
void 	print_preorder(t_tree *node);
void	print2D(t_tree* root);
void	print2DUtil(t_tree *root, int space);


/* ---------------------- EXECUTE -----------------------*/
// execute.c
void	execute(t_shell_sack **sack);
void    run_oper(t_tree *node);
// execute_utils
void	ft_close(int fd1, int fd2);
int 	check_redirect(t_shell_sack ***sack, t_tree *node);
int     open_redirect(t_shell_sack ****sack_orig, t_tree *node);
void    ft_heredoc(t_shell_sack *****sack_orig, char *eof);
t_tree *findnext_cmdleaf(t_tree **node);
int		check_opercondition(t_shell_sack **sack, t_tree **node);
//path.c
int		check_route(char *av);
int		check_path(char **env);
char	*get_path(char *cmd, char **env);
// char	*getcmd_withpath(t_shell_sack *sack, char *cmd, char **cmds, char **env);
char	*getcmd_withpath(char *cmd, char **env);

int	execute_cmd(char *cmd, char **envp);
/* ---------------------- BUILTINS ------------------------*/
//enviroment.c and //enviroment_utils.c
int     env_init(t_shell_sack *sack, char **envp);
int     search_env_pos(char **env, char *word, char limit);
size_t 	ft_arraylen(char **array);
void    ft_free_env(char **env);
int     print_env(t_shell_sack ****sack_orig);
void	ft_free_error_arr(char **mem, long i);
//export.c
int     export(t_env *env, char *new);
int     is_valid_to_export(char *s);
char    **realloc_export_add(t_env *env, char *new);
//print_export_list.c
void    print_export_list(t_env *env);
//pre_export.c
void    pre_export_new_variable(t_env *env, char *line);
int 	already_added_pre_export_list(t_env *env, char *new);
//unset.c
int		unset(t_env *env, char *del, int check);
//pwd.c
// int     get_pwd(void);
int print_pwd(t_shell_sack *sack);
//cd.c
int     cd(t_shell_sack *sack, char **pathname);

//cd_utils.c
char    *remove_slash(char *path);
void    cd_mserror(char *cmd);
int     check_pathroot(char *path);
int     update_oldpwd(t_shell_sack *sack);
//echo.c
int     echo(char **line);
//check_isbuiltin.c
int     check_isbuiltin(t_tree *node);
int     execute_builtin(t_shell_sack ***sack, t_tree *node);
//exit.c
int cmd_exit(t_shell_sack ***sack, char **cmd);


/* ---------------------- CLEAN AND EXIT ------------------------*/
void	ft_free_pruebas(t_shell_sack **sack);
void	ft_clearenv(t_shell_sack *sack);
void    free_token(void *content);
void    free_sack(t_shell_sack **sack);
void    free_tree(t_tree **node);
int		wait_exitcode(int last_pid);
int     read_exit(char *line); //Change to builtin exit
void	perror_free_exit(char *msj, t_shell_sack ***sack);

void    free_exit(char **cmds, t_shell_sack ***sack, int msj);
void	ft_pustr_msjerror(int n, char *cmd);

/* ---------------------- LISTS ------------------------*/
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist *ft_dlstfirst(t_dlist *lst);
int		ft_dlstsize(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst, void (*del_dlst)(void *));
void	ft_dlstdelone(t_dlist *lst, void (*del_dlst)(void *));
void	del_dlst(void *content);



/*---------------------SIGNALS------------------*/
void	sighandler(void);


#endif
