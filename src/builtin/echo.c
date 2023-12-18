/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:57:07 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/10 01:57:08 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int cmd_echo(t_shell_sack *sack, char **line)
{
    int flag = 0;
    int i = 1;


    if (!ft_strncmp(line[i], "-n", 2))
    {
        flag = 1;
        i++;
    }

    if (line[i])
    { 
        while (line[i])
        {
            if (line[i])
                ft_putstr_fd(line[i], 1);
            if (line[i + 1])
                ft_putstr_fd(" ", 1);
            i++;
        }

    }
    if (flag == 0)
        ft_putstr_fd("\n", 1); 

    // perror_free_exit("", &sack);
    // perror_free_exit("", (t_shell_sack***)&sack);


    return (0);
}