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

int cmd_echo(t_shell_sack ****sack_orig, char **line)
{
    t_shell_sack    **sack;
    int             flag = 0;
    int             i = 1;
    
    sack = (**sack_orig);
    if ((*sack)->new_pipes[1] != 1 )
        if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
            perror_free_exit("Dup2 error echo OUT", &(**sack_orig));
    if (line && line[i])
    {
        if (!ft_strncmp(line[i], "-n", 2))
        {
            flag = 1;
            i++;
        }
        while (line[i])
        {
            if (line[i])
                ft_putstr_fd(line[i], (*sack)->new_pipes[1]);  
            if (line[i + 1])
            ft_putstr_fd(" ", (*sack)->new_pipes[1]); 
            i++;
        }
    }
    if (flag == 0)
        ft_putstr_fd("\n", (*sack)->new_pipes[1]); 
    return (0);
}
