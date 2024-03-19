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

int check_bad_exit(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (1);
    while (s[i])
    {
        if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+')
        {
            ft_putstr_fd("minishell: error: numeric argument required\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

int cmd_exit(t_shell_sack ***sack, char **cmd)
{
    long exitcode = 0;
    char *s;

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
        if (check_bad_exit(s) == 1)
            return(free(s), 2);
        else
            exitcode = ft_atoi(s);
        free (s);
    }
    else
        exitcode = (**sack)->last_exit;
    ft_clearenv((**sack));
    free_sack(&(**sack));
    exit(exitcode); //check error code for exit
}