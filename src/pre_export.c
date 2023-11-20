/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pre_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:30:12 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/16 20:30:14 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*@brief sintaxis: export variabale. Busca en pre export si esa variable
ha sido añadidamete a la lista de pre_export.*/
void already_added_pre_export_list(t_env *env, char *new, long pos)
{
    pos = search_env_pos(env->pre_export, new, '\0');
    printf("\n\n\nPOS%ld", pos);
    if (pos >= 0)
    {
        env->env = realloc_export_add(env, env->pre_export[pos]);
        unset(env, new, 0);
    }
    else
        return (ft_putstr_fd("export: not a valid identifier", 2));
}



char **realloc_exchange_pre_export(t_env *env, char *new, size_t pos)
{
    char **temp;
    size_t i;

    i = -1;
    temp = (char **)malloc((env->env_elements + 1) * sizeof(char *));
    if (!temp)
        return (NULL);
    while (env->pre_export[++i])
    {
		if (pos == i)
			temp[i] = ft_substr(new, 0, ft_strlen(new));
		else
			temp[i] = ft_strdup(env->pre_export[i]);
        if (!temp[i])
            	return (ft_free_error_arr(temp, i), NULL);
    }
    temp[i] = NULL;
    // ft_free_env(env->pre_export);
    return (temp);
}

/*@brief Añade variables a char **env->pre_export_list para su posterior exportacion
Ejemplo: VARIABLE1="hola" .... muchos otros comandos distintos... export VARIABLE1 (se incluye VARIABLE1 en el enviroment)
*/
char **realloc_add_pre_export_list(t_env *env, char *line)
{
    char **temp;
    long    check;
    size_t i;

    check = env->pre_export_elements;
    temp = (char **)malloc((env->pre_export_elements + 2) * sizeof(char *));
    if (!temp)
        return(NULL);
    i = 0;
    while (i < env->pre_export_elements + 1)
    {
        if (check-- > 0 && env->pre_export[i])
        {
            temp[i] = ft_strdup(env->pre_export[i]);
            if (!temp[i])
                return (ft_free_error_arr(temp, i), NULL); //Aqui habria que liberar pre_export en caso de q exista
        }
        else
        {
            temp[i] = ft_strdup(line);
            if (!temp[i])
                return (ft_free_error_arr(temp, i), NULL); // Aqui igual
        }
        i++;
    }
    temp[i] = NULL;
    return (temp);
}

//@brief: sintaxis: VARIABLE=contenido //Si line no contiene '=' no llamar a esta funcion
void pre_export_new_variable(t_env *env, char *line)
{
    char **temp;
	size_t i;

    if (!env || !line)
        return ;
    i = 0;
    // printf("ffff");
	if (!ft_isalpha(line[i]) && !line[i] != '_')
		return (ft_putstr_fd(line, 2), ft_putstr_fd("command not found", 2));
	i++;
    while (line[i] && line[i] != '=')
	{
		if (!ft_isalpha(line[i]) && !ft_isalnum(line[i])
        && line[i] != '_' && line[i] != '=')
			return (ft_putstr_fd(line, 2), ft_putstr_fd("command not found", 2));
        i++;
    }
    i = search_env_pos(env->pre_export, line, '=');
    printf("%ld", i);
    if (i != -1)
    {
         temp = realloc_exchange_pre_export(env, line, i);
        if (!temp)
            return ;
    }

    else
    {
        temp = realloc_add_pre_export_list(env, line);
        if (temp == NULL)
            return ;
        env->pre_export_elements += 1;
    }
    if (env->pre_export_elements > 0)
        ft_free_env(env->pre_export);
    env->pre_export = temp;

}