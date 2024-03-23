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

int	cd_home(t_shell_sack *sack)
{
	char	*temp;
	int		pos;

	update_oldpwd(sack);
	pos = search_env_pos(sack->env->env, "HOME", '\0');
	if (pos < 0)
		return (ft_putstr_fd("cd: HOME not set", 2), 1);
	temp = get_varcontent(sack->env->env[pos]);
	if (chdir(temp) == -1)
		return (cd_mserror(temp), 1);
	free (sack->env->pwd);
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

// int	cd_back(t_shell_sack *sack)
// {
// 	char	*temp;
// 	char	curr_dir[256];

// 	temp = NULL;
// 	chdir("..");
// 	temp = getcwd(curr_dir, sizeof(curr_dir));
// 	if (!temp)
// 	{
// 		cd_mserror(temp);
// 		temp = ft_strdup("..");
// 		if (!temp)
// 			return (1);
// 	}
// 	free (sack->env->pwd);
// 	sack->env->pwd = ft_strjoin("PWD=", temp);
// 	if (!sack->env->pwd)
// 		return (free(temp), 1);
// 	export(sack->env, sack->env->pwd);
// 	export(sack->env, sack->env->oldpwd);
// 	return (0);
// }


int	cd_path(t_shell_sack *sack)
{
	char	*pathname;

	char	curr_dir[256];
	char *path = getcwd(curr_dir, sizeof(curr_dir));
	if (path == NULL)
	{
		cd_mserror(path);
		path = ft_strdup("..");
		if (!path)
			return (1);
	}
	// if (path[ft_strlen(path)] == '/')
	// {
	// 	free (sack->env->pwd);
	// 	sack->env->pwd = ft_strdup(path);
	// 	if (sack->env->pwd == NULL)
	// 		return (1);
	// 	return (0);
	// }
	pathname = remove_slash(path); 
	if (!pathname)
		return (1);
	free (sack->env->pwd);
	sack->env->pwd = ft_strjoin("PWD=", pathname);
	free (pathname);
	if (!sack->env->pwd)
		return (1);
	return (0);
}


int	update_oldpwd(t_shell_sack *sack)
{
	char	*temp;

	temp = get_varcontent(sack->env->pwd);
	if (!temp)
		return (1);
	free (sack->env->oldpwd);
	sack->env->oldpwd = ft_strjoin("OLDPWD=", temp);
	if (!sack->env->oldpwd)
		return (free(temp), 1);
	free (temp);
	return (0);
}

//@brief Intenta acceder a la ruta pasada como parametro, en caso de error muestra un mensaje y no hace nada mas.
int    cd(t_shell_sack *sack, char **cmds)
{
	char    *path = cmds[1];
	int     ret;

	if (ft_arraylen(cmds) > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!path)
		return (cd_home(sack));
	ret = chdir(path);
	if (ret == -1 && check_pathroot(path) == 1)
		return (cd_mserror(path), 1);
	if (update_oldpwd(sack) == 1)
		return (1);
	if (cd_path(sack) == 1)
		return (1);
	export(sack->env, sack->env->pwd);
	export(sack->env, sack->env->oldpwd);
	return (0);
}
