/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:55:16 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/21 20:55:18 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"


//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
void    cd(char *pathname)
{
    int ret;

    ret = chdir(pathname);
    if (ret == -1)
        ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
}
