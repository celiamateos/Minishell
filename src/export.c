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
#include "../include/minishell.h"
//Añade variables a char **env->pre_export_list para su posterior exportacion
//Ejemplo: VARIABLE1="hola" .... muchos otros comandos distintos... export VARIABLE1 (se incluye VARIABLE1 en el enviroment)
///segfault aquiiiiiiiiii
char **realloc_add_pre_export_list(t_env *env, char *line)
{
    char **temp;
    long    check;
    size_t i;

    if (!env || !line)
        return (NULL);
    check = env->pre_export_elements;
    temp = (char **)malloc(env->pre_export_elements + 2 * sizeof(char *));
    if (!temp)
        return(NULL);
    i = -1;
    while (++i < env->pre_export_elements + 1)
    {
        if (check > 0 && env->pre_export[i])
        {
            temp[i] = ft_strdup(env->pre_export[i]);
            if (!temp[i])
                return (ft_free_error_arr(temp, i), NULL); //Aqui habria que liberar pre_export en caso de q exista
            check--;
        }
        else
        {
            temp[i] = ft_strdup(line);
            if (!temp[i])
                return (ft_free_error_arr(temp, i), NULL); // Aqui igual
        }
    }
    temp[env->pre_export_elements + 1] = NULL;
    if (env->pre_export_elements > 0)
        ft_free_env(env->pre_export);
    env->pre_export_elements += 1;
    return (temp);
}


//Verificar si incluye la variable en enviroment, si no muestra un error.
//True si es valido para exportar: Ej export VARIABLE="contenido"
//False si no es valido. Ej export 13fabVAR = "hola"
//
int is_valid_to_export(char *s)
{
	int i;

    i = 0;
	if (!ft_isalpha(s[i]))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && !ft_isalnum(s[i]) && s[i] != '_')
			return (ft_putstr_fd("export: not a valid identifier", 2), 0);
		i++;
	}
	if (s[i] == '=')
    {
        if (s[i - 1] == ' ' || s[i + 1] == ' ')
		    return (ft_putstr_fd("export: not a valid identifier", 2), 0);
    }
    else if (s[i] == '\0')
    {
        return (0);
        //Funcion revisar si está en ***variables.
    }
	return (1);
}

//Añade una nueva variable al final del enviroment
char **realloc_export_add(t_env *env, char *new)
{
    char **temp;
    size_t i;

    i = -1;
    temp = (char **)malloc((env->env_elements + 2) * sizeof(char *));
    if (!temp)
       return (ft_free_env(env->env), NULL);
    while (env->env[++i])
    {
        temp[i] = ft_strdup(env->env[i]);
        if (!temp[i])
            return(ft_free_error_arr(temp, i), ft_free_env(env->env), NULL);
    }
    temp[i] = ft_strdup(new);
    if (!temp[i])
        return (ft_free_error_arr(temp, i), ft_free_env(env->env), NULL);
    temp[env->env_elements + 1] = NULL;
    env->env_elements++;
    ft_free_env(env->env);
    return (temp);
}


//Intercambia una variable existente por una nueva con el mismo nombre.
char **realloc_export_exchange(t_env *env, char *new, size_t pos)
{
    char **temp;
    size_t i;

    i = -1;
    temp = (char **)malloc((env->env_elements + 1) * sizeof(char *));
    if (!temp)
        return (ft_free_env(env->env), NULL);
    while (env->env[++i])
    {
		if (pos == i)
			temp[i] = ft_substr(new, 0, ft_strlen(new));
		else
			temp[i] = ft_strdup(env->env[i]);
        if (!temp[i])
            	return (ft_free_error_arr(temp, i), ft_free_env(env->env), NULL);
    }
    temp[i] = NULL;
    ft_free_env(env->env);
    return (temp);
}

int export(t_env *env, char *new)
{
	long pos;

	if (new == NULL)
    {
        print_export_list(env);
        return (0);
    }
	pos = search_env_pos(env->env, new, '=');
	if (!is_valid_to_export(new))
	{
        //Una funcion que busque en char ***variables si previamente ha sido añadida
		ft_putstr_fd("export: not a valid identifier", 2);
		return (ft_free_env(env->env), 1);
	}
	if (pos >= 0)
    {
		env->env = realloc_export_exchange(env, new, pos);
        if (!env->env)
            return (1);
    }
	else
    {
	    env->env = realloc_export_add(env, new);
        if (!env->env)
            return (1);
    }
	return (0);
}