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
#include "../../include/minishell.h"

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
// cd sin argumentos busca $HOME y si no existe 
// da el error:    bash: cd: HOME not set
// Cada vez que se usa cd, hay que actualizar PWD Y OLDPWD en el enviroment
// Tambien hay que actualizar SHLVL en el enviroment cada vvez q se ejecuta minishell
void    cd(char *pathname)
{
    int ret;

    if (!pathname)
    {
        chdir("/"); //Aqui falta algo jeje
        ft_putstr_fd("a la raiz\n", 1);
        return ;
    }
    ret = chdir(pathname);
    if (ret == -1)
        ft_putstr_fd("cd: No such file or directory\n", 2);
}
