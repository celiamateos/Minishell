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

int echo(t_shell_sack ****sack_orig, char **line)
{
    t_shell_sack    **sack;
    int             flag = 0;
    int             i = 1;
    
    sack = (**sack_orig);  ///ESTO NO LO ESTOY USANDO
    // printf("new_pipes[1]: %d\n", (*sack)->new_pipes[1]);
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
                ft_putstr_fd(line[i], 1);  
            if (line[i + 1])
                ft_putstr_fd(" ", 1); 
            i++;
        }
    }
    if (flag == 0)
        ft_putstr_fd("\n", 1); 
    // if ((*sack)->new_pipes[1] != 1 )
    //     if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
    //         free_exit(&(**sack_orig));
    return (0);
}
