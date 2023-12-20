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


int  execute_builtin(t_shell_sack ***sack, t_tree *node)
{
    char *cmd;

    cmd = node->content->cmds[0];
    
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
        return (cd(**sack, node->content->cmds[1]));
    if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
        return (get_pwd());
    if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
        return(export((**sack)->env, node->content->cmds[1]));
    if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
        return (print_env((**sack)->env->env));
    if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
        return (unset((**sack)->env, node->content->cmds[1], 2));
    if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
        return (cmd_echo(&sack, node->content->cmds[1]));
    
    // if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))

    // printf("PUTO node: %s", node->content->cmds[1]);
    perror_free_exit("Builtin error", &(*sack));
    // exit (0);
    return (0);
}

int  check_isbuiltin(t_shell_sack **sack, t_tree *node)
{
    char *cmd;

    cmd = node->content->cmds[0];
    
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)) && (ft_strlen(cmd)) == 2)
        return (0);
    else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)) && (ft_strlen(cmd)) == 3)
         return (0);
    else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)) && (ft_strlen(cmd)) == 6)
         return (0);
    else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)) && (ft_strlen(cmd)) == 3)
         return (0);
    else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)) && (ft_strlen(cmd)) == 5)
         return (0);
    else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)) && (ft_strlen(cmd)) == 4)
         return (0);
    else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
    {
	    free ((*sack)->line);
        exit(1);


    }
    return (1);
    // if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))

    // printf("PUTO node: %s", node->content->cmds[1]);
}