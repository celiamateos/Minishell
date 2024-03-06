/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:56:10 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/07 14:56:12 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void    cd_mserror(char *cmd)
{
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(strerror(errno), 2);
    // ft_putstr_fd("cd: ", 2);
    if (!cmd)
        ft_putstr_fd("chdir: error retrieving current directory: getcwd:"  
        "cannot access parent directories: No such file or directory", 2);

    ft_putstr_fd("\n", 2);
}

/*@brief ALOCA MEMORIA*/
char *remove_slash(char *path)
{
    char    *pathname;

    if (path[ft_strlen(path) - 1] != '/')
        pathname = ft_strdup(path);
    else
        pathname = ft_strtrim(path, "/");
    if (!pathname)
        return (NULL); //SALIDA DE ERRORES? 
    return (pathname);
}

int check_pathroot(char *path)
{
    int i;

    i = 0;
    while (path[i])
    {
        if (path[i] != '/')
            return (1);
        i++;
    }
    return (0);
}