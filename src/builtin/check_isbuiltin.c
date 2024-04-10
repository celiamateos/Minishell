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

	if (!ft_strncmp(node->content->cmds[0], "echo\0", 5))
		(**sack)->last_exit = echo(node->content->cmds);
	else
	{
		remove_quotes_arr_cmds(node->content, (*sack));
		cmd = node->content->cmds[0];
		if (!ft_strncmp(cmd, "exit\0", 5))
			(**sack)->last_exit = cmd_exit(sack, node->content->cmds);
		else if (!ft_strncmp(cmd, "cd\0", 3))
			(**sack)->last_exit = cd(**sack, node->content->cmds);
		else if (!ft_strncmp(cmd, "pwd\0", 4))
			(**sack)->last_exit = print_pwd((**sack));
		else if (!ft_strncmp(cmd, "export\0", 7))
			(**sack)->last_exit = export((**sack)->env, node->content->cmds[1]);
		else if (!ft_strncmp(cmd, "env\0", 4))
			(**sack)->last_exit = print_env(&sack);
		else if (!ft_strncmp(cmd, "unset\0", 6))
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

	if (check_isbuiltin(node))
		return (0);
	cmd = node->content->cmds[0];
	if (!ft_strncmp(cmd, "echo\0", 5))
		return (0);
	else if (!ft_strncmp(cmd, "exit\0", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd\0", 3))
		return (1);
	else if (!ft_strncmp(cmd, "export\0", 7
			&& ft_sarrlen(node->content->cmds) < 2))
		return (1);
	else if (!ft_strncmp(cmd, "unset\0", 6))
		return (1);
	else if (ft_strchr(cmd, '=') && !is_valid_to_export(cmd))
		return (1);
	return (0);
}

int	check_isbuiltin(t_tree *node)
{
	char	*cmd;

	cmd = node->content->cmds[0];
	if (!ft_strncmp(cmd, "exit\0", 5))
		return (0);
	else if (!ft_strncmp(cmd, "cd\0", 3))
		return (0);
	else if (!ft_strncmp(cmd, "pwd\0", 4))
		return (0);
	else if (!ft_strncmp(cmd, "export\0", 7))
		return (0);
	else if (!ft_strncmp(cmd, "env\0", 4)
		&& ft_sarrlen(node->content->cmds) == 1 && ft_strlen(cmd) == 3)
		return (0);
	else if (!ft_strncmp(cmd, "unset\0", 6))
		return (0);
	else if (!ft_strncmp(cmd, "echo\0", 5))
		return (0);
	else if (ft_strchr(cmd, '=') && !is_valid_to_export(cmd))
		return (0);
	return (1);
}
