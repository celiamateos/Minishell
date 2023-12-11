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

int cd_root(t_shell_sack *sack, char *pwd, char *old_pwd)
{
    char *temp;

    temp = get_varcontent(pwd);
    if (!temp)
        return (free_cd(pwd, old_pwd, temp), 1);
    sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    if (!sack->env->oldpwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    free (temp);
    sack->env->pwd = ft_strjoin("PWD=", "/");
    if (!sack->env->pwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    return (0);
}

int cd_path(t_shell_sack *sack,  char *pathname, char *pwd, char *old_pwd)
{
    char *temp;

    temp = get_varcontent(pwd);
    if (!temp)
        return (free_cd(pwd, old_pwd, temp), 1);
    sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    if (!sack->env->oldpwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    free (temp);
    sack->env->pwd = ft_strjoin(pwd, "/");
    if (!sack->env->pwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    temp = ft_strjoin(sack->env->pwd, pathname);
    if (!temp)
        return (free_cd(pwd, old_pwd, temp), free(sack->env->pwd), 1);
    free (sack->env->pwd);
    sack->env->pwd = ft_strdup(temp);
    if (!sack->env->pwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    free (temp);
    return (0);
}

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
// SOLO FUNCIONA AL LLAMAR A CD LA PRIMERA VEZ DESPUES DE EJECUTAR MINISHELL, NO SE SI ESPROBLEMA DE ESTO O DEL EXECUTE
int    cd(t_shell_sack *sack, char *pathname)
{
    int ret;
    // char *temp;
    // char *line;
    // int     len_pwd = ;
    // int     len_oldpwd;

    char *pwd = ft_strdup(sack->env->pwd);
    char *old_pwd = ft_strdup(sack->env->oldpwd);
    clean_cd(sack);
    if (!pathname)
        cd_root(sack, pwd, old_pwd);
    else
    {   
        ret = chdir(pathname);
        if (ret == -1)
            return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
        cd_path(sack, pathname, pwd, old_pwd);

    }

    printf("PWD: %s\n", sack->env->pwd);
    printf("OLDPWD: %s\n", sack->env->oldpwd);
    export(sack->env, sack->env->pwd);
    export(sack->env, sack->env->oldpwd);
    free (pwd);
    free (old_pwd);
    return (0);

}
