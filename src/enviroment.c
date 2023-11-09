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

void print_env(char **env)
{
	int i = 0;

	printf("\n");
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}


void export(t_env *env, char *new)
{
	char **tmp;
	(void)new;
	tmp = env->array;
	//free (env->array);
	env->env_size++;
	env->array = ft_calloc(1, sizeof(env->env_size));
	if (!env->array)
		exit(1); //Salida de errores que libere env.
	env->array = tmp;
	// env->array[env->env_size - 1] = new;
}

int	init_env(char **envp, t_env *env)
{
	int i;

	i = -1;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (1);
	if (envp)
	{
		print_env(envp);
		env->array = ft_calloc(1, sizeof(env->env_size));
		if (!env->array)
			return (1);
		printf("\n\nENV:\n\n\n");
		env->array = envp;
		print_env(env->array);
	}
	printf("env_size: %ld\n", env->env_size);
	printf("env_elements: %ld\n", env->env_elements);

	// //export(env, "HOLAAAAAAAAAAAAAA=ey----------------------");
	// printf("\n\nENV:\n\n\n");
	// print_env(env->array);
	if (env->array)
		free (env->array);
	if (env)
		free(env); //quitar despues de las pruebas
	return (0);
}
