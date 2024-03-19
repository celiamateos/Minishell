/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:41:52 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/09 03:41:53 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
//@brief  ????? Recibe el envp, alloca memoria exacta para su copia.
//Si el envp no existe (env -i ./minishell), aloca
//un char** de size 2, uno para '\0' y otro para el NULL, hay que hacer eso?
char **alloc_first_envp(t_env *env, char **src)
{
	char **result = NULL;
	size_t i;

	env->env_elements = ft_arraylen(src);
	i = -1;
	if (src)
	{
		result = (char **)malloc((env->env_elements + 1) * sizeof(char *));
		if (!result)
			return (NULL);
		while (++i < env->env_elements)
		{
			result[i] = ft_strdup(src[i]);
			if (!result)
				return (NULL);
		}
	}
	else
	{
		result = (char **)malloc(2 * sizeof(char *)); //Aqui hay que crear un enviroment si no existiera envp, al menos con: shlvl, pwd, oldpwd, 
		if (!result)
			return (NULL);
		result[i + 1] = NULL;
		i += 2;
	}
	result[i] = NULL;
	return (result);
}

int	init_pwd(t_env *env)
{
	int pos;

	pos = search_env_pos(env->env, "PWD=", '=');
	if (pos >= 0)
	{
		env->pwd = ft_strdup(env->env[pos]);
		if (!env->pwd)
			return (1);
	}
	pos = search_env_pos(env->env, "OLDPWD=", '=');
	if (pos >= 0)
	{
		env->oldpwd = ft_strdup(env->env[pos]);
		if (!env->oldpwd)
			return (1);
	}
	return (0);
}

int insert_shlvlenv(t_shell_sack *sack, char *new)
{
	char *aux;
	aux = ft_strjoin("SHLVL=", new);
	if (!aux)
		return (1);
	export(sack->env, aux);
	free (aux);
	return (0);
}

int init_shlvl(t_shell_sack *sack)
{
	char	*shlvl;
	int		n;

	shlvl = get_varname(sack, "SHLVL");
	// if (shlvl && shlvl[0] == '\0')
	// 	free (shlvl);
	if (shlvl)
	{
		n = ft_atoi(shlvl);
		if (n < 0)
			n = -1;
		else if (n >= 999)
		{
			ft_putstr_fd("minishell: warning: shell level (1000) too high, resetting to 1\n", 2);
			n = 0;
		}
		n++;
		free (shlvl);
		shlvl = ft_itoa(n);
		if (!shlvl)
			return (1);
		// printf("\nshlvl:%s\n", shlvl);
	}
	else
	{
		shlvl = ft_strdup("1");
		if (!shlvl)
			return (1);
	}
	insert_shlvlenv(sack, shlvl);
	sack->env->shlvl = ft_strdup(shlvl);
	free (shlvl);
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
		sack->env->env = alloc_first_envp(sack->env, envp);
		if (!sack->env->env)
			return (1);
		sack->env->pre_export_elements = 0;
		if (init_pwd(sack->env))
			return (1);
		if (init_shlvl(sack))
			return (1);
	}
	return (0);
}

