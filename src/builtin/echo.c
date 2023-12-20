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

int cmd_echo(t_shell_sack ****sack_orig, char *line)
{
    t_shell_sack    **sack;
    
    sack = (**sack_orig);
    if ((*sack)->new_pipes[1] != 1 )
        if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
            perror_free_exit("Dup2 error echo OUT", &(**sack_orig));
    if (line)
    { 
        // ft_putstr_fd(line, 1);  
        // ft_putstr_fd("\n", 1); 
        ft_putstr_fd(line, (*sack)->new_pipes[1]);  
        ft_putstr_fd("\n", (*sack)->new_pipes[1]); 
    }
    else
    {
        ft_putstr_fd("\n", (*sack)->new_pipes[1]); 
        // ft_putstr_fd("\n", 1); 
        // exit (1); 
    }

    return (0);
}