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

void    free_cd(char *s1, char*s2, char *s3)
{
    if (s1)
        free(s1);
    if (s2)
        free (s2);
    if (s3)
        free(s3);
}

int cd_path(t_shell_sack *sack,  char *pathname, char *pwd, char *old_pwd)
{

    char *temp;

        temp = get_varcontent(pwd);
        if (!temp)
            return (free_cd(pwd, old_pwd, temp), 1);
        sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
        free (temp);
        if (!sack->env->oldpwd)
            return (free_cd(pwd, old_pwd, temp), 1);
        temp = get_varcontent(pwd);
        if (!temp)
            return (free_cd(pwd, old_pwd, temp), 1);
        sack->env->pwd = ft_strjoin(temp, pathname);
        free (temp);
        if (!sack->env->pwd)
            return (free_cd(pwd, old_pwd, temp), 1);
        temp = ft_strjoin("/", sack->env->pwd);
        if (!temp)
            return (free_cd(pwd, old_pwd, temp), 1);
        free (sack->env->pwd);
        sack->env->pwd = temp;
        // free (temp);
        return (0);
}

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
// cd sin argumentos busca $HOME y si no existe 
// da el error:    bash: cd: HOME not set
// Cada vez que se usa cd, hay que actualizar PWD Y OLDPWD en el enviroment
// Tambien hay que actualizar SHLVL en el enviroment cada vvez q se ejecuta minishell
int    cd(t_shell_sack *sack, char *pathname)
{
    int ret;
    // char *temp;
    // char *line;
    // int     len_pwd = ;
    // int     len_oldpwd;


    clean_cd(sack);
    char *pwd = ft_strdup(sack->env->pwd);
    char *old_pwd = ft_strdup(sack->env->oldpwd);
    if (!pathname)
    {
        chdir("/"); //Aqui falta algo jeje
        // ft_putstr_fd("a la raiz\n", 1);
        // temp = get_varcontent(pwd);
        // if (!temp)
        //     return (free_cd(pwd, old_pwd, temp), 1);
        // sack->env->oldpwd = ft_strjoin("OLDPWD=", temp); 
        // if (!sack->env->oldpwd)
        //     return (free_cd(pwd, old_pwd, temp), 1);
        // sack->env->pwd = ft_strdup("PWD=/");
        // if (!sack->env->pwd)
        //     return (free_cd(pwd, old_pwd, temp), 1);

    }
    else
    {   
        ret = chdir(pathname);
        if (ret == -1)
            return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
        cd_path(sack, pathname, &pwd, &old_pwd);

    }

    printf("PWD: %s\n", sack->env->pwd);
    printf("OLDPWD: %s\n", sack->env->oldpwd);
    export(sack->env, sack->env->pwd);
    export(sack->env, sack->env->oldpwd);
    return (0);

}
