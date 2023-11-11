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
char **alloc_first_envp(char **src)
{
	char **result = NULL;
	size_t i;

	i = -1;
	if (src)
	{
		result = (char **)malloc((ft_arraylen(src) + 1) * sizeof(char *));
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

//Añade una nueva variable al final del enviroment
char **realloc_export_add(t_env *env, char *new)
{
    if (!new)
        return NULL;
    char **temp;
    size_t i;
    size_t len = ft_arraylen(env->array);

    i = -1;
    temp = (char **)malloc((len + 2) * sizeof(char *));
    if (!temp)
        exit(1);
    while (env->array[++i])
    {
        temp[i] = ft_strdup(env->array[i]);
        if (!temp[i])
            ft_free_error_arr(temp, i);
    }
    temp[i] = ft_strdup(new);
    if (!temp[i])
        ft_free_error_arr(temp, i);
    temp[len + 1] = NULL;
    ft_free_env(env->array);
    return (temp);
}


//Intercambia una variable existente por una nueva con el mismo nombre.
char **realloc_export_exchange(t_env *env, char *new, size_t pos)
{
    char **temp;
    size_t i;

    i = -1;
    temp = (char **)malloc((ft_arraylen(env->array) + 1) * sizeof(char *));
    if (!temp)
        exit(1);
    while (env->array[++i])
    {
		if (pos == i)
			temp[i] = ft_substr(new, 0, ft_strlen(new));
		else
			temp[i] = ft_strdup(env->array[i]);
        if (!temp[i])
            	ft_free_error_arr(temp, i);
    }
    temp[i] = NULL;
    ft_free_env(env->array);
    return (temp);
}

int export(t_env *env, char *new)
{
	long pos;
	/*if (new == NULL)
	 una funcion para mostrar lo que muestra export asecas*/
	if (!is_valid_to_export(new))
		ft_putstr_fd("export: not a valid identifier", 2);
	pos = search_env(env->array, new);
	if (pos >= 0)
		env->array = realloc_export_exchange(env, new, pos);
	else
		env->array = realloc_export_add(env, new);
	return (0);
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
		env->array = alloc_first_envp(envp);
		if (!env->array)
			return (1);
		print_env(env->array);
	}
	// printf("\nenv_size: %ld\n", env->env_size);
	// printf("\nenv_elements: %ld\n", env->env_elements);

	export(env, "UaaaaSER=UNICORNIOOOOOOOOOOOOOOOOOOOO");
	printf("\n\nENV despues de export_change:\n\n\n");
	print_env(env->array);
	ft_free_env(env->array);
	free(env);
	return (0);
}
