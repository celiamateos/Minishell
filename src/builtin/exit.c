/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:04:34 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/08 01:04:36 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void    ms_cmd_exit(char *s)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(s, 2);
    ft_putstr_fd(" numeric argument required\n", 1);
}

int cmd_exit(t_shell_sack ***sack, char **cmd)
{
    int exitcode;
    char *s;
    int i;

    i = 0;
    if (ft_arraylen(cmd) > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    else if (cmd[1])
    {
        s = remove_quotes_cmd(cmd[1]);
        if (!s)
            return (1);
        while (s[i])
        {
            if (!ft_isalnum(s[i]) && s[i] != '-' && s[i] != '+')
            {
                ms_cmd_exit(s);
                return (free(s), 2);
            }
            i++;
        }
        exitcode = ft_atoi(s);
        free (s);
    }
    ft_clearenv((**sack));
    free_sack(&(**sack));
    exit(exitcode); //check error code for exit
}