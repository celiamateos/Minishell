/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:50:28 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/16 10:51:01 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	init_values(int *tab, t_env *env)
{
	env->index = -1;
	while (++env->index != env->env_elements)
		tab[(int)env->index] = 0;
	env->index = 0;
	env->i = 1;
	env->count = 0;
}

//Retorna el indice de la string guardada en char *order
//Para ser printeada y marcada como tal en int *tab
int	search_equal(char *order, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (strcmp(order, env[i]) == 0)
			break ;
	}
	return (i);
}

void	search_lower_alpha(t_env *env, int *tab)
{
	while (env->env[env->i])
	{
		if (ft_strncmp(env->order, env->env[env->i], ft_strlen(env->order)) > 0
			&& tab[(int)env->i] == 0)
			env->order = env->env[env->i];
		env->i++;
	}
}

void	ft_putstr_fd_export(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	ft_putstr_fd("\ndeclare -x ", 1);
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		if (s[i] == '=')
			ft_putstr_fd("\"", 1);
		i++;
	}
	ft_putstr_fd("\"", 1);
}

void	print_export_list(t_env *env)
{
	int	*tab;

	tab = malloc(env->env_elements * sizeof(int));
	if (!tab)
		return ;
	init_values(tab, env);
	env->order = env->env[0];
	while (env->count < env->env_elements)
	{
		search_lower_alpha(env, tab);
		env->i = 0;
		env->index = search_equal(env->order, env->env);
		while (tab[(int)env->i] == 1)
			env->i++;
		if (tab[(int)env->index] == 0)
		{
			ft_putstr_fd_export(env->env[env->index], 1);
			tab[(int)env->index] = 1;
			env->count++;
		}
		env->order = env->env[env->i++];
	}
	ft_putstr_fd("\n", 1);
	free (tab);
}
