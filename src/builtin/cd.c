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

int cd_root(t_shell_sack *sack)
{
    char    *temp;
    int     pos;

    temp = get_varcontent(sack->env->pwd);
    if (!temp)
        return (1);
    free (sack->env->oldpwd);
    sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    if (!sack->env->oldpwd)
        return (free(temp), 1);
    free (temp);
    pos = search_env_pos(sack->env->env, "HOME", '\0');
    if (pos < 0)
        return (ft_putstr_fd("cd: HOME not set", 2), 1);
    temp = get_varcontent(sack->env->env[pos]);
    if (chdir(temp) == -1)
        return (cd_mserror(temp), 1);    free (sack->env->pwd);
    sack->env->pwd = ft_strdup(temp);
    if (!sack->env->pwd)
        return (free(temp), 1);
    free (temp);
    temp = ft_strjoin("PWD=", sack->env->pwd);
      free (sack->env->pwd);
    sack->env->pwd = ft_strdup(temp);
    free (temp);
    export(sack->env, sack->env->pwd);
    export(sack->env, sack->env->oldpwd);
    return (0);
}

int cd_path(t_shell_sack **sack,  char *pathname, char *pwd)
{
    char    *temp;

    temp = ft_strjoin(pwd, "/");
    if (!temp)
        return (1);
    free ((*sack)->env->pwd);
    (*sack)->env->pwd = ft_strjoin(temp, pathname);
    if (!(*sack)->env->pwd)
        return (free(temp), 1);
    free (temp);
    return (0);
}

int cd_back(t_shell_sack *sack)
{
    char    *temp;
    char    curr_dir[256];

    temp = getcwd(curr_dir, sizeof(curr_dir));
    if (chdir(temp) == -1)
        return (cd_mserror(temp), 1);
    free (sack->env->pwd);
    sack->env->pwd = ft_strjoin("PWD=", temp);
    if (!sack->env->pwd)
        return(free(temp), 1);
    return (0);
}

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje.
int    cd(t_shell_sack *sack, char *path)
{
    char    *pwd;
    char    *temp;

    if (!path)
        if (!cd_root(sack))
            return (0); // Aqui no estoy protegiendo malloc
    if (chdir(path) == -1)
        return (cd_mserror(path), 1);
    temp = get_varcontent(sack->env->pwd);
    if (!temp)
        return (1);
    free (sack->env->oldpwd);
    sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
    if (!sack->env->oldpwd)
        return (free(temp), 1);
    free (temp);
    pwd = ft_strdup(sack->env->pwd);
    if (!ft_strncmp(path, "..", 1))
    {
        cd_back(sack);
        // if (!cd_back(sack))
        // {
        //     printf("sack->env->pwd:%s", sack->env->pwd);
        //     temp = ft_strjoin("PWD=", sack->env->pwd);
        //     if (!temp)
        //         return (1);
        //     free (sack->env->pwd);
        //     sack->env->pwd = ft_strjoin(temp, "/..");
        //     if (!sack->env->pwd)
        //         return (1);
        // }
    }
    else
    {
        temp = remove_slash(path); 
        if (!temp)
            return (free(pwd), 1);
        cd_path(&sack, temp, pwd);
        free(temp);
    }
    export(sack->env, sack->env->pwd);
    export(sack->env, sack->env->oldpwd);
    return (free (pwd), 0);
}