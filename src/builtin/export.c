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

/*@brief Verifica si incluye la variable en enviroment, si no muestra un error.
//True si es valido para exportar: Ej export VARIABLE="contenido"
//False si no es valido. Ej export 13fabVAR = "hola"
*/
int is_valid_to_export(char *s)
{
	int i;
    // int check = 0;

    i = 0;
    // if (ft_strposchr(s, '=') == -1)
    //     return (0);
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (ft_putstr_fd("minishell: export: not a valid identifier\n", 2), 1);
	while (s[i] && s[i] != '=')
	{
		if ((!ft_isalnum(s[i])) && (s[i] != '_'))
			return (ft_putstr_fd("minishell: export: not a valid identifier\n", 2), 1);
		i++;
	}
    // if (s[i] == '\0' && check == 1)
    //     return (0);
	if (s[i] == '=')
    {
        if (s[i - 1] == ' ' || s[i + 1] == ' ')
		    return (ft_putstr_fd("minishell: export: not a valid identifier\n", 2), 1);
    }
	return (0);
}

//@brief Añade una nueva variable al final del enviroment
//@param new la nueva variable
//@return NULL en caso de error, liberando lo previamente alocado y env.
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
    // ft_print_strarray(env->env);
    return (temp);
}


//@brief Intercambia una variable existente por una nueva con el mismo nombre.
//@param new la nueva variable
//@param pos la posicion en la que se encuentra la variable en el enviroment
//@return NULL en caso de error, liberando lo previamente alocado y env.
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

/*
@brief ALOCA MEMORIA.
@param new la nueva variable a añadir al enviroment pre->export
// (export variable_nueva=contenido / export variable_existente)
//
//(variable=contenido) -> llamar a funcion realloc_add_pre_export();
*/
int export(t_env *env, char *new)
{
	long pos;

    pos = -1;
    if (new == NULL)
    {
        print_export_list(env);
        return 0;
    }
    pos = search_env_pos(env->env, new, '=');
    if (is_valid_to_export(new) == 1)
    {
        printf("no es valido %s", new); //Error in english?
        return (1);
    }
    if (!ft_strchr(new, '='))
    {
        already_added_pre_export_list(env, new);
        return (0);
    }
    if (pos >= 0)
    {
        // printf("\n k koño");
        // printf("\npos o ke:%ld", pos);
        env->env = realloc_export_exchange(env, new, pos);
        if (!env->env)
            return (1); //ft_error malloc en realloc_export_exchange // liberar t_env
    }
    else
    {
        // printf("\n k koño2");
        env->env = realloc_export_add(env, new);
        if (!env->env)
            return (1); //ft_error malloc en realloc_export_add // liberar t_env
    }
    // free (new);
    // print_env(env->env);
    return (0);
}