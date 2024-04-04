/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_isbiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:59:15 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/06 00:59:17 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/* @brief return 0 if ok or 1 if error. Exit to ft_perror_free_exit
*/
int	execute_builtin(t_shell_sack ***sack, t_tree *node)
{
	char	*cmd;

	if (!ft_strncmp(cmd, "echo", ft_strlen(node->content->cmds[0])))
		(**sack)->last_exit = echo(node->content->cmds);
	else
	{
		remove_quotes_arr_cmds(node->content, (*sack));
		cmd = node->content->cmds[0];
		if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
			(**sack)->last_exit = cmd_exit(sack, node->content->cmds);
		if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
			(**sack)->last_exit = cd(**sack, node->content->cmds);
		else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
			(**sack)->last_exit = print_pwd((**sack));
		else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
			(**sack)->last_exit = export((**sack)->env, node->content->cmds[1]);
		else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
			(**sack)->last_exit = print_env(&sack);
		else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
			(**sack)->last_exit = unset((**sack)->env,
					node->content->cmds[1], 2);
		else if (ft_strchr(cmd, '='))
			(**sack)->last_exit = pre_export_new_variable((**sack)->env, cmd);
	}
	return ((**sack)->last_exit);
}

// @brief Check if the builtin have to execute in parent process.
// @return 1 is has to execute in a parent process. 
int	check_builtinparent(t_tree *node)
{
	char	*cmd;

	cmd = node->content->cmds[0];
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (1);
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (0);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")
			&& ft_sarrlen(node->content->cmds) < 2))
		return (0);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env"))
		&& ft_sarrlen(node->content->cmds) == 1 && ft_strlen(cmd) == 3)
		return (0);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (1);
	else if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (0);
	else if (ft_strchr(cmd, '=') && !is_valid_to_export(cmd))
		return (1);
	return (0);
}

int	check_isbuiltin(t_tree *node)
{
	char	*cmd;

	cmd = node->content->cmds[0];
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (0);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		return (0);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env"))
		&& ft_sarrlen(node->content->cmds) == 1 && ft_strlen(cmd) == 3)
		return (0);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (0);
	else if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (0);
	else if (ft_strchr(cmd, '=') && !is_valid_to_export(cmd))
		return (0);
	return (1);
}
