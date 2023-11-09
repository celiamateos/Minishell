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
// Funcion auxiliar para printear el enviroment.
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

//Return len array.
size_t ft_arraylen(char **array)
{
	size_t i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

//ft_substr de David. 
char	*ft_suubstr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	c;

	c = 0;
	if (len > ft_strlen(s))
		sub = (char *) malloc (ft_strlen(s) + 1);
	else
		sub = (char *) malloc (len + 1);
	if (!sub)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[start + c] != '\0' && c < len)
		{
			sub[c] = s[start + c];
			c++;
		}
	}
	sub[c] = '\0';
	return (sub);
}

//Recibe un array, alloca memoria y retorna una memoria.
char **alloc_array(char **src)
{
	char **result = NULL;
	size_t i;

	i = 0;
	if (src)
	{
		// printf("%ld", ft_arraylen(src + 1));
		result = (char **)malloc((ft_arraylen(src + 1)) * sizeof(char *));
		if (!result)
			return (NULL);
		while (i < ft_arraylen(src))
		{
			result[i] = ft_suubstr(src[i], 0, ft_strlen(src[i])); //Heap buffer overflow aqui. probé con ft_substr de david tb da problemas, luego lo miro
			i++;
		}
	}
	result[i + 1] = NULL;
	return (result);
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
		print_env(envp);
		printf("\n\nENV:\n\n\n");
		env->array = alloc_array(envp);
		if (!env->array)
			return (1);
		print_env(env->array);
	}
	printf("\nenv_size: %ld\n", env->env_size);
	printf("\nenv_elements: %ld\n", env->env_elements);

	// export(env, "HOLAAAAAAAAAAAAAA=ey----------------------");
	// printf("\n\nENV:\n\n\n");
	// print_env(env->array);
	if (env->array)
		free (env->array);
	if (env)
		free(env); //quitar despues de las pruebas
	return (0);
}

// int export(t_env *env, char *new)
// {
// 	char **tmp;
// 	int		i;
// 	i = -1;
// 	(void)new;

// 	tmp = env->array;
// 	free (env->array);
// 	env->env_size++;
// 	env->array = ft_calloc(env->env_size, sizeof(char **));
// 	if (!env->array)
// 		return (1);
// 	while (++i < env->env_size - 1)
// 	{
// 		env->array[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
// 		if (!env->array[i])
// 			return (1);
// 	}
// 	env->array[++i] = ft_substr(new, 0, ft_strlen(new));
// 	return (0);
// }
