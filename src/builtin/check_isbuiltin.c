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
//LOS BUILTINS TIENEN QUE RETORNAR INT 0 SI TODO VA BIEN, FT_PERROR_FREE_eXIT SI HAY ALGUN FALLO. PENDIENTE
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
        return (cmd_echo(&sack, node->content->cmds));
    if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
        perror_free_exit("Builtin error", &(*sack));
    if (ft_strchr(cmd, '='))
    {
        pre_export_new_variable((**sack)->env, cmd);
        return (0);
    }

    // printf("PUTO node: %s", node->content->cmds[1]); // ENTONCES EL EXIT K COÑO PASAAAA???
    // exit (0);
    return (0);
}

int  check_isbuiltin(t_shell_sack **sack, t_tree *node)
{
    char *cmd;

    cmd = node->content->cmds[0];

    if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
        return (0);
    else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
         return (0);
    else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
         return (0);
    else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
         return (0);
    else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
         return (0);
    else if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
         return (0);
    else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
    {
	    free ((*sack)->line);
        exit(1);
    }
    else if (ft_strchr(cmd, '='))
    {
        return (0);
    }
    return (1);
}