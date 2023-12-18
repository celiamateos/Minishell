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
    char    *temp;
    char    *aux;

    temp = get_varcontent(pwd);
    if (!temp)
        return (free_cd(pwd, old_pwd, temp), 1);
    sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    if (!sack->env->oldpwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    free (temp);
    aux = sack->env->pwd;
    sack->env->pwd = ft_strjoin("PWD=", "/");
    free (aux);
    if (!sack->env->pwd)
        return (free_cd(pwd, old_pwd, temp), 1);
    return (0);
}

int cd_path(t_shell_sack **sack,  char *pathname, char *pwd, char **old_pwd)
{
    char    *temp;
    char    *aux;

    temp = get_varcontent(pwd);
    if (!temp)
        return (free_cd(pwd, *old_pwd, temp), 1);
    // aux = (*sack)->env->oldpwd;
    (*sack)->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    // free(aux);
    if (!(*sack)->env->oldpwd)
        return (free_cd(pwd, *old_pwd, temp), 1);
    free (temp);
    aux = (*sack)->env->pwd;
    (*sack)->env->pwd = ft_strjoin(pwd, "/");
    free(aux);
    if (!(*sack)->env->pwd)
        return (free_cd(pwd, *old_pwd, temp), 1);
    temp = ft_strjoin((*sack)->env->pwd, pathname);
    if (!temp)
        return (free_cd(pwd, *old_pwd, temp), free((*sack)->env->pwd), 1);
    free ((*sack)->env->pwd);
    (*sack)->env->pwd = ft_strdup(temp);
    if (!(*sack)->env->pwd)
        return (free_cd(pwd, *old_pwd, temp), 1);
    free (temp);
    // free (*old_pwd);
    return (0);
}

int cd_back(t_shell_sack *sack, char *pwd, char **old_pwd)
{
    char    *temp;
    int     pos;
    int     i;

    temp = get_varcontent(pwd);
    if (!temp)
        return (free_cd(pwd, *old_pwd, temp), 1);
    sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    if (!sack->env->oldpwd)
        return (free_cd(pwd, *old_pwd, temp), 1);
    free (temp);
    pos = ft_strlen(pwd);
    while (pwd[pos] != '/' && pwd[pos]);
        pos--;
    pos--;
    temp = ft_substr(pwd, 0, pos);
    if (!temp) 
        return(1); //SALIDA DE ERRORES-.-
    //  sack->env->pwd = temp;
    pwd = temp;
    free (temp);
    free (*old_pwd);
    return (0);
}

/*@brief ALOCA MEMORIA*/
char *remove_slash(char *path)
{
    char    *temp;
    char    *pathname;

    if (path[ft_strlen(path) - 1] != '/')
        return (0);
    pathname = ft_strtrim(path, "/");
    if (!pathname)
        return (NULL); //SALIDA DE ERRORES? 
    return (pathname);
}

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
// SOLO FUNCIONA AL LLAMAR A CD LA PRIMERA VEZ DESPUES DE EJECUTAR MINISHELL, NO SE SI ESPROBLEMA DE ESTO O DEL EXECUTE
int    cd(t_shell_sack *sack, char *path)
{
    int     ret;
    char    *pwd;
    char    *old_pwd;
    char    *pathname;

    if (chdir(path) == -1)
        return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
    pwd = ft_strdup(sack->env->pwd);
    if (sack->env->oldpwd)
        old_pwd = ft_strdup(sack->env->oldpwd);
    if (!path)
        cd_root(sack, pwd, old_pwd);
    else if (!ft_strncmp(path, "..", 1))
        cd_back(sack, pwd, &old_pwd);
    else
    {   
        pathname = remove_slash(path); 
        cd_path(&sack, pathname, pwd, &old_pwd);
        free(pathname);
    }
    //  printf("PWD: %s\n", sack->env->pwd);
    // printf("OLDPWD: %s\n", sack->env->oldpwd);
    export(sack->env, sack->env->pwd);
    export(sack->env, sack->env->oldpwd);
    free (pwd);
    return (0);
}