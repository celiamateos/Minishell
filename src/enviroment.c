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
#include "../include/minishell.h"

//@brief Recibe el envp, alloca memoria exacta para su copia.
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
		result = (char **)malloc(2 * sizeof(char *));
		if (!result)
			return (NULL);
		result[i + 1] = '\0';
		i += 2;
	}
	result[i] = NULL;
	return (result);
}

//@brief ALOCA MEMORIA para t_env y char **env->env para hacer una copia del envp
//Liberar char **env->env y t_env en main o salida de errores.
//@return 1 en caso de error
int	init_env(char **envp, t_env *env)
{
	if (!env)
		return (1);
	if (envp)
	{
		// printf("\nENV ORIGINAL:\n");
		// print_env(envp);
		env->env = alloc_first_envp(env, envp);
		if (!env->env)
			return (1);
		env->pre_export_elements = 0;
		// print_env(env->env);
	}
	return (0);
}
