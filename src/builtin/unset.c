/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:36:49 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/12 03:37:12 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// //@brief ALOCA MEMORIA!
// //Realloc array env and delete position line
char	**realloc_unset_env(t_env *env, size_t pos)
{
	char	**temp;
	size_t	i;
	size_t	j;

	if (!env)
		return (NULL);
	i = -1;
	j = 0;
	temp = (char **)malloc(env->env_elements * sizeof(char *));
	if (!temp)
		return (NULL);
	while (++i < env->env_elements - 1)
	{
		if (i == pos)
			j++;
		temp[i] = ft_substr(env->env[j], 0, ft_strlen(env->env[j]));
		if (!temp[i])
			return (ft_free_error_arr(temp, i), NULL);
		j++;
	}
	temp[i] = NULL;
	return (temp);
}

void	unset_env(t_env *env, char *del)
{
	long	pos;
	char	**temp;

	pos = search_env_pos(env->env, del, '\0');
	if (pos >= 0)
	{
		temp = realloc_unset_env(env, pos);
		if (temp)
		{
			ft_freematrix(&env->env);
			env->env = ft_sarrcpy(temp);
			ft_freematrix(&temp);
			env->env_elements -= 1;
		}
	}
}

//@brief ALOCATE MEMORY
//Realloc arr pre_export, delet position line.
char	**realloc_unset_pre_export_list(t_env *env, size_t pos)
{
	char	**temp;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!env)
		return (NULL);
	i = -1;
	j = 0;
	temp = (char **)malloc(env->pre_export_elements * sizeof(char *));
	if (!temp)
		return (NULL);
	while (++i < env->pre_export_elements - 1)
	{
		if (i == pos)
			j++;
		len = ft_strlen(env->pre_export[j]);
		temp[i] = ft_substr(env->pre_export[j], 0, len);
		if (!temp[i])
			return (ft_free_error_arr(temp, i), NULL);
		j++;
	}
	temp[i] = NULL;
	return (temp);
}

void	unset_pre_export_list(t_env *env, char *del)
{
	long	pos;
	char	**temp;

	pos = search_env_pos(env->pre_export, del, '\0');
	if (pos >= 0)
	{
		temp = realloc_unset_pre_export_list(env, pos);
		if (temp)
		{
			ft_freematrix(&env->pre_export);
			env->pre_export = ft_sarrcpy(temp);
			ft_freematrix(&temp);
			env->pre_export_elements -= 1;
		}
	}
}

// @brief Unset var "del" to enviroment and/or pre_export_list.
// Revisa si la posicion de la linea que quieres borrar existe.
int	unset(t_env *env, char *del, int check)
{
	if (env->env && (check == 2 || check == 1))
		unset_env(env, del);
	if (env->pre_export && (check == 2 || check == 0))
		unset_pre_export_list(env, del);
	return (0);
}
