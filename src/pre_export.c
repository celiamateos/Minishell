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

//FUNCION PARA REALLOC_PRE_EXPORT_LIST_EXCHANGE

/*@brief PENDIENTE DE CORREGIR segfault aquiiiiiiiiii al llamar a la funcion mas de una vez
Añade variables a char **env->pre_export_list para su posterior exportacion
Ejemplo: VARIABLE1="hola" .... muchos otros comandos distintos... export VARIABLE1 (se incluye VARIABLE1 en el enviroment)
*/
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
    }
    temp[env->pre_export_elements + 1] = NULL;
    if (env->pre_export_elements > 0)
        ft_free_env(env->pre_export);
    env->pre_export_elements += 1;
    return (temp);
}

void is_valid_to_pre_export(t_env *env, char *new, long pos)
{
	int i;

    i = 0;

	if (!ft_isalpha(new[i]) && !new[i] != '_')
		return (ft_putstr_fd(new, 2), ft_putstr_fd("command not found", 2));
	while (new[i])
	{
		if (!ft_isalpha(new[i]) && !ft_isalnum(new[i]) && new[i] != '_')
			return (ft_putstr_fd(new, 2), ft_putstr_fd("command not found", 2));
		i++;
	}
    pos = search_env_pos(env->pre_export, new, '\0');
    if (pos >= 0)
    {
        env->env = realloc_export_add(env, env->pre_export[pos]);
        unset(env, new, 0);
    }
    else
        return (ft_putstr_fd("export: not a valid identifier", 2), ft_free_env(env->env));
}