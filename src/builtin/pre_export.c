/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pre_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:30:12 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/16 20:30:14 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// @brief shearch new has been added into pre_export_list
int	already_added_pre_export_list(t_env *env, char *new)
{
	long	pos;
	int		check;

	check = 0;
	pos = search_env_pos(env->pre_export, new, '\0');
	if (pos >= 0)
	{
		if (search_env_pos(env->env, new, '\0') > -1)
			check = 2;
		env->env = realloc_export_add(env, env->pre_export[pos]);
		if (!env->env)
			return (1);
		unset(env, new, check);
		return (0);
	}
	else
		return (1);
	return (0);
}

char	**realloc_exchange_pre_export(t_env *env, char *new, size_t pos)
{
	char	**temp;
	size_t	i;

	i = -1;
	temp = (char **)malloc((env->env_elements + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	while (env->pre_export[++i])
	{
		if (pos == i)
			temp[i] = ft_substr(new, 0, ft_strlen(new));
		else
			temp[i] = ft_strdup(env->pre_export[i]);
		if (!temp[i])
			return (ft_free_error_arr(temp, i), NULL);
	}
	temp[i] = NULL;
	return (temp);
}

//@brief Add var into env->pre_export_list to be export
//Ej: name=minishell export minishell
char	**realloc_add_pre_export_list(t_env *env, char *line)
{
	char	**temp;
	long	check;
	size_t	i;

	check = env->pre_export_elements;
	temp = (char **)malloc((env->pre_export_elements + 2) * sizeof(char *));
	if (!temp)
		return (NULL);
	i = -1;
	while (++i < env->pre_export_elements + 1)
	{
		if (check-- > 0 && env->pre_export[i])
			temp[i] = ft_strdup(env->pre_export[i]);
		else
			temp[i] = ft_strdup(line);
		if (!temp[i])
			return (ft_free_error_arr(temp, i), NULL);
	}
	temp[i] = NULL;
	return (temp);
}

//@brief: sintax: var=content
//line new var to add or exchange pre_export_list
int	pre_export_new_variable(t_env *env, char *line)
{
	char	**temp;
	int		i;

	i = 0;
	if (!env || !line)
		return (1);
	i = search_env_pos(env->pre_export, line, '=');
	if (i != -1)
	{
		temp = realloc_exchange_pre_export(env, line, i);
		if (!temp)
			return (1);
	}
	else
	{
		temp = realloc_add_pre_export_list(env, line);
		if (!temp)
			return (1);
		env->pre_export_elements += 1;
	}
	if (env->pre_export_elements > 0)
		ft_free_env(env->pre_export);
	env->pre_export = temp;
	return (0);
}
