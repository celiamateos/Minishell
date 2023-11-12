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
		while (++i < ft_arraylen(src))
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


//Libera las lineas previas malokeadas en caso de error.
void	ft_free_error_arr(char **mem, long i)
{
    while (i > 0)
        free(mem[--i]);
    free(mem);
}

// Alloca memoria para struct t_env.
//Toma el tamaño del env (número de lineas)
// Alloca memoria para env->array
// Retorna 1 en caso de error. 
int	init_env(char **envp, t_env *env)
{
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (1);
	if (envp)
	{
		printf("\nENV ORIGINAL:\n");
		print_env(envp);
		env->array = alloc_first_envp(env, envp);
		if (!env->array)
			return (1);
		print_env(env->array);
	}

	printf("\nenv_elements: %ld\n", env->env_elements);


	if (export(env, "PATtrH="))
	{
		free(env);
		return (1);
	}

	printf("\n\nENV despues de unset_change:\n\n\n");
	print_env(env->array);
	printf("\nenv_elements: %ld\n", env->env_elements);
	ft_free_env(env->array);
	free(env);
	return (0);
}
