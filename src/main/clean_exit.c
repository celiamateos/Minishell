/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_clearenv(t_shell_sack *sack)
{
	if (sack->env->pwd)
		free(sack->env->pwd);
	if (sack->env->oldpwd)
		free(sack->env->oldpwd);
	free(sack->env->shlvl);
	ft_free_env(sack->env->pre_export);
	ft_free_env(sack->env->env);
	free(sack->env);
}

void	free_tree(t_tree **node)
{
	if (*node != NULL && node != NULL)
	{
		free_tree(&(*node)->left);
		free_tree(&(*node)->right);
		free(*node);
	}
}

void	free_sack(t_shell_sack **sack)
{
	if (sack || *sack)
	{
		if ((*sack)->line)
			free((*sack)->line);
		if ((*sack)->token_list)
			ft_dlstclear(&(*sack)->token_list, &free_token);
		if ((*sack)->tree_list)
			free_tree(&(*sack)->tree_list);
	}
}

void	free_token_noargs(void *content)
{
	t_token	*token;
	char	*value;

	token = content;
	value = token->value;
	if (content)
	{
		if (value != NULL && token->value)
			free(token->value);
	}
	free(content);
}

void	free_token(void *content)
{
	t_token	*token;
	char	*value;

	token = content;
	value = token->value;
	if (content)
	{
		if (value != NULL && token->value)
			free(token->value);
		ft_freematrix(&token->cmds);
	}
	free(content);
}

/*VERSION MEJORADA perror_free_exit*/
void	free_exit(char **cmds, t_shell_sack ***sack, int msj)
{
	int		exitcode;
	int		status;
	char	*cmd;

	cmd = ft_arrtostr(cmds);
	if (WIFEXITED(status))
		(**sack)->last_exit = 127;
	if (WIFSIGNALED(status))
	{
		(**sack)->last_exit = 126;
		msj = ISDIRECTORY;
	}
	exitcode = (**sack)->last_exit;
	if (msj != 0)
		ft_pustr_msjerror(msj, cmd);
	ft_clearenv((**sack));
	free_sack(&(**sack));
	exit(exitcode);
}

void	ft_pustr_msjerror(int n, char *cmd)
{
	if (n == STANDAR)
		ft_putstr_fd(strerror(errno), 2);
	else if (n == COMANDNOTFOUND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
	else if (n == PERMISSIONDENIED)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
	else if (n == NOSUCHFILEORDIRECTORY)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
	else if (n == ISDIRECTORY)
	{
		ft_putstr_fd("minishell: is a directory: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
	ft_putstr_fd("\n", 2);
}

/*@brief Used to return error message and free everything before exit*/
void	perror_free_exit(char *msj, t_shell_sack ***sack)
{
	int	exitcode;

	perror(msj);
	exitcode = (**sack)->last_exit;
	ft_clearenv((**sack));
	free_sack(&(**sack));
	exit(exitcode);
}

// @brief Reset fds to standar.
void reset_pipes(int *old_pipes, int *new_pipes)
{
	old_pipes[0] = 0;
	old_pipes[1] = 1;
	new_pipes[0] = 0;
	new_pipes[1] = 1;
}
