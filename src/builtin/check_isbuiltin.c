/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_isbiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:59:15 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/06 00:59:17 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../../include/minishell.h"

int  check_isbuiltin(t_shell_sack **sack, t_tree *node)
{
    char *cmd;

    cmd = node->content->cmds[0];
    
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
        cd(*sack, node->content->cmds[1]);
    if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
        get_pwd();
    if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
        export((*sack)->env, node->content->cmds[1]);
    if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
        print_env((*sack)->env->env);
    if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
        unset((*sack)->env, node->content->cmds[1], 2);
    if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
        cmd_echo(*sack, node->content->cmds[1]);
    
    // if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))

    // printf("PUTO node: %s", node->content->cmds[1]);
    return (0);
}