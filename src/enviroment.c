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

//Recibe el envp, alloca memoria exacta para su copia.
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




int	init_env(char **envp, t_env *env)
{
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (1);
	if (envp)
	{
		printf("\nENV ORIGINAL:\n");
		print_env(envp);
		env->env = alloc_first_envp(env, envp);
		if (!env->env)
			return (1);
		env->pre_export_elements = 0;
		print_env(env->env);
	}

	printf("\nenv_elements: %ld\n", env->env_elements);


	print_export_list(env);
	// env->pre_export = NULL;
	// env->pre_export = ft_calloc(1, sizeof(char **));
	// env->pre_export[0] = NULL;
	// env->pre_export = realloc_add_pre_export_list(env, "VARIABLE3=eeeei");
	// env->pre_export = realloc_add_pre_export_list(env, "VARIABLE2=hola que tal");
	// env->pre_export = realloc_add_pre_export_list(env, "VARIABLE3=ke coño pasa??");
	// // unset(env, "VARIABLE1");
	// printf("\n\nENV despues pre export add list:\n\n\n");
	// print_env(env->pre_export);
	// printf("\nenv_elements: %ld\n", env->pre_export_elements);
	ft_free_env(env->env);
	// ft_free_env(env->pre_export);
	free(env);
	return (0);
}
