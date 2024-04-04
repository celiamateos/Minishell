/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:36:15 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/12 03:36:17 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

//@brief Checks includes var in the enviroment, otherwise it display an error 
//True if its valid to export. Ej export VARIABLE="contenido"
//False if it isn't to export. Ej export 13fabVAR = "hola"
int	is_valid_to_export(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (1);
	while (s[i] && s[i] != '=')
	{
		if ((!ft_isalnum(s[i])) && (s[i] != '_'))
			return (1);
		i++;
	}
	if (s[i] == '=')
	{
		if (s[i - 1] == ' ' || s[i + 1] == ' ')
			return (1);
	}
	return (0);
}

//@brief Add a new var to the end of the enviroment
//@param new new var
//@return NULL if found error, free it previous allocated and free env.
char	**realloc_export_add(t_env *env, char *new)
{
	char	**temp;
	size_t	i;

	i = -1;
	temp = (char **)malloc((env->env_elements + 2) * sizeof(char *));
	if (!temp)
		return (NULL);
	while (env->env[++i])
	{
		temp[i] = ft_strdup(env->env[i]);
		if (!temp[i])
			return (ft_free_error_arr(temp, i), NULL);
	}
	temp[i] = ft_strdup(new);
	if (!temp[i])
		return (ft_free_error_arr(temp, i), NULL);
	temp[env->env_elements + 1] = NULL;
	env->env_elements++;
	return (temp);
}

//@brief Exchanges an wxisting variable for a new one with the same name
//@param new new var
//@param the position in which the variable is located within the enviroment.
//@return NULL if found error, free env.
char	**realloc_export_exchange(t_env *env, char *new, size_t pos)
{
	char	**temp;
	size_t	i;

	i = -1;
	temp = (char **)malloc((env->env_elements + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	while (env->env[++i])
	{
		if (pos == i)
		{
			temp[i] = ft_substr(new, 0, ft_strlen(new));
			if (!temp[i])
				return (ft_free_error_arr(temp, i), NULL);
		}
		else
		{
			temp[i] = ft_strdup(env->env[i]);
			if (!temp[i])
				return (ft_free_error_arr(temp, i), NULL);
		}
	}
	temp[i] = NULL;
	return (temp);
}

// @BRIEF Continuation of fuction export() to complying with norminette
int	export_add_or_exchange(t_env *env, char *new, long pos)
{
	char	**temp;

	if (pos >= 0)
	{
		temp = realloc_export_exchange(env, new, pos);
		if (!temp)
			return (1);
	}
	else
	{
		temp = realloc_export_add(env, new);
		if (!temp)
			return (1);
	}
	ft_free_env(env->env);
	env->env = temp;
	return (0);
}

//@brief ALLOC MEMORY.
//@param new new var to add into pre_export_list
// add or echange the variable.
//(variable=contenido)-> call to function realloc_add_pre_export();
int	export(t_env *env, char *new)
{
	long	pos;

	pos = -1;
	if (new == NULL)
		return (print_export_list(env), 0);
	pos = search_env_pos(env->env, new, '=');
	if (is_valid_to_export(new) == 1)
		return (ft_putstr_fd(MSERROR1, 2), 1);
	if (!ft_strchr(new, '='))
		return (already_added_pre_export_list(env, new), 0);
	return (export_add_or_exchange(env, new, pos));
	return (0);
}
