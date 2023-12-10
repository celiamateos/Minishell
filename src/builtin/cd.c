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

void    clean_cd(t_shell_sack *sack)
{
    if (sack->env->pwd)
        free(sack->env->pwd);
    if (sack->env->oldpwd)
        free(sack->env->oldpwd);
}

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
// cd sin argumentos busca $HOME y si no existe 
// da el error:    bash: cd: HOME not set
// Cada vez que se usa cd, hay que actualizar PWD Y OLDPWD en el enviroment
// Tambien hay que actualizar SHLVL en el enviroment cada vvez q se ejecuta minishell
int    cd(t_shell_sack *sack, char *pathname)
{
    int ret;
    char *temp;
    char *line;

    clean_cd(sack);
    if (!pathname)
    {
        chdir("/"); //Aqui falta algo jeje
        // ft_putstr_fd("a la raiz\n", 1);
        sack->env->oldpwd = ft_strdup(sack->env->pwd);
        if (!sack->env->oldpwd)
            return (1);
        sack->env->pwd = ft_strdup("PWD=/");
        if (!sack->env->pwd)
            return (1);
        export(sack->env, sack->env->pwd);
         return (0);
    }
    ret = chdir(pathname);
    if (ret == -1)
        return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
    else
    {
        sack->env->oldpwd = ft_strdup(sack->env->pwd);
        if (!sack->env->oldpwd)
            return (1);
        sack->env->pwd = ft_strjoin("PWD=", pathname);
        if (!sack->env->pwd);
            return (1);
        export(sack->env, sack->env->pwd);
    }
}
