/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:36:49 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/12 03:37:12 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

//Realloca el array env, omitiendo la línea que se desea eliminar.
//Retorna NULL en caso de fallo en la reserva de memoria, liberando lo alocado previamente en esta función.
char **realloc_unset(t_env *env, size_t pos)
{
    char **temp;
    size_t i;
    size_t j;

    if(!env)
        return (NULL);
    i = -1;
    j = 0;
    temp = (char **)malloc(env->env_elements * sizeof(char *));
    if (!temp)
        return(ft_free_env(env->array), NULL);
    while (++i < env->env_elements - 1)
    {
       if (i == pos)
            j++;
        temp[i] = ft_substr(env->array[j], 0, ft_strlen(env->array[j]));
        if (!temp[i])
            return(ft_free_error_arr(temp, i), ft_free_env(env->array), NULL);
        j++;
    }
    temp[i] = NULL;
    env->env_elements -= 1;
    ft_free_env(env->array);
    return (temp);
}

//Revisa si la posicion de la linea que quieres borrar existe. (line 53)
//Retorna 1 en caso de fallo en alguna reserva de memoria.  (line:58)
//Habría que liberar env struct si esta funcion retorna 1. (line:58)
int unset(t_env *env, char *del)
{
	long pos;

    if (env->array)
    {
        pos = search_env_pos(env->array, del, '\0');
	    if (pos >= 0)
        {
            env->array = realloc_unset(env, pos);
            if (!env->array)
                return (1);
        }
    }
    return (0);
}