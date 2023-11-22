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
// No tengo muy claro si hay que guardar la ruta de la raiz al inicio de la ejecucion para indicar que vaya a la raiz cuando pathname sea null
//Probar cuando el arbol ya esté okey
void    cd(char *pathname)
{
    int ret;

    ret = chdir(pathname);
    if (ret == -1)
        ft_putstr_fd("cd: No such file or directory", 2);
}
