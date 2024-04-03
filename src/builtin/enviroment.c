/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newiroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:41:52 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/09 03:41:53 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
//De donde saco el PATH con env -i ???
char	**create_env(t_env *env)
{
	char	**new;

	new = (char **)ft_calloc(6 * sizeof(char *), 1);
	if (!new)
		return (NULL);
	env->env_elements = 5;
	new[0] = ft_strjoin("PWD=", env->pwd);
	if (!new[0])
		return (ft_free_error_arr(new, 0), ft_free_env(new), NULL);
	new[1] = ft_strdup("SHLVL=");
	if (!new[1])
		return (ft_free_error_arr(new, 1), ft_free_env(new), NULL);
	new[2] = ft_strdup("PATH=/home/cmateos-/.local/bin/:"
			"/home/cmateos-/.local/bin/:/home/cmateos-/bin:/usr/local/bin:"
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:"
			"/usr/games:/usr/local/games:/snap/bin");
	if (!new[2])
		return (ft_free_error_arr(new, 2), ft_free_env(new), NULL);
	new[3] = ft_strdup("OLDPWD=");
	if (!new[3])
		return (ft_free_error_arr(new, 3), ft_free_env(new), NULL);
	new[4] = ft_strdup("_=/minishell");
	if (!new[4])
		return (ft_free_error_arr(new, 4), ft_free_env(new), NULL);
	return (new);
}

char	**alloc_first_envp(t_env *env, char **src)
{
	char	**r;
	size_t	i;

	env->env_elements = ft_sarrlen(src);
	i = -1;
	if (env->env_elements > 1)
	{
		r = (char **)malloc((env->env_elements + 1) * sizeof(char *));
		if (!r)
			return (NULL);
		while (++i < env->env_elements)
		{
			r[i] = ft_strdup(src[i]);
			if (!r[i])
				return (ft_free_error_arr(r, i), ft_free_env(r), NULL);
		}
	}
	else
		r = create_env(env);
	if (!r)
		return (NULL);
	r[ft_sarrlen(r)] = NULL;
	return (r);
}

int	init_pwd(t_env *env)
{
	char	*pwd;
	char	curr_dir[256];
	int		pos;

	pwd = getcwd(curr_dir, sizeof(curr_dir));
	if (!pwd)
		return (1);
	env->pwd = ft_strdup(pwd);
	if (!env->pwd)
		return (1);
	pos = search_env_pos(env->env, "OLDPWD=", '=');
	if (pos >= 0)
	{
		env->oldpwd = ft_strdup(env->env[pos]);
		if (!env->oldpwd)
			return (1);
	}
	return (0);
}

//@brief ALOCA MEMORIA char **env->env para hacer una copia del envp
int	env_init(t_shell_sack *sack, char **envp)
{
	sack->env = ft_calloc(1, sizeof(t_env));
	if (!sack->env)
		return (1);
	if (envp)
	{
		if (init_pwd(sack->env))
			return (1);
		sack->env->env = alloc_first_envp(sack->env, envp);
		if (!sack->env->env)
			return (1);
		sack->env->pre_export_elements = 0;
		if (init_shlvl(sack))
			return (1);
	}
	return (0);
}
