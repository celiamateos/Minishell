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

int only_n(char *s)
{
    int i;

    i = 0;
    while (s[++i])
    {
        if (s[i] != 'n')
            break ;
    }
    if (s[i] != '\0')
        return (1);
    return (0);
}

int echo(char **arr_cmd)
{
    char            *line;
    char            *temp;
    int             flag = 0;
    int             i = 1;

    // ft_print_strarray(arr_cmd);
    if (arr_cmd[i] && !ft_strncmp(arr_cmd[i], "-n", 2) && only_n(arr_cmd[i]) == 0)
    {
        i++;
        flag = 1;
        while (arr_cmd[i] && !ft_strncmp(arr_cmd[i], "-n", 2) && only_n(arr_cmd[i]) == 0)
            i++;
    }
    if (arr_cmd && arr_cmd[i])
    {
        // printf("\narr_cmd[%d]:%s\n", i,  arr_cmd[i]);
        line = ft_strdup(arr_cmd[i]);
        if (!line)
            return (1);
        i++;
        if(arr_cmd[i])
        {
            while (arr_cmd[i])
            {
                // printf("\narr_cmd[%d]:%s\n", i, arr_cmd[i]);
                temp = ft_strjoin(line, " ");
                if (!temp)
                    return (free(line), 1);
                free (line);
                line = ft_strjoin(temp, arr_cmd[i]);
                if (!line)
                    return (free(temp), 1);
                free (temp);
                i++;
            }
        }
        ft_putstr_fd_noquotes(line, 1);
        free (line);
    }
    if (flag == 0)
        ft_putstr_fd("\n", 1); 
    return (0);
}
